#include <Arduino.h>
#include <SoftwareSerial.h>

#define WINDOW_SIZE 35
#define PHOTORESISTOR_PIN A0
#define VALVE_PIN A7
#define VALVE_PIN_LIMIT 1000
#define RELAY_PIN 6

float value_avg_buffer[WINDOW_SIZE];
float time_buffer[WINDOW_SIZE];
int index = 0;

float value_avg_running = 0;
float biggest_slope = 0;
float time_of_biggest_slope = 0;
float valve_open_time = 0;
float car_start_time = 0;

float slope_limit = 120;

float min_KI = 1.0;  // mL
float max_KI = 3.0;  // mL
float speed = 0.45;  // m/s
float x = 44.828;  // x = exp(-b/a)
float y = -1.4342;  // y = 1/a

bool car_timed = false;
float car_start_delay = 2;

void real_setup();
void real_loop();
void data_setup();
void data_loop();
void time_car(float time_of_biggest_slope);

void setup() {
    real_setup();
}

void loop() {
    real_loop();
}

void real_setup() {
    Serial.begin(9600);
    pinMode(VALVE_PIN, INPUT);
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW);

    // fill array with values
    while (index < WINDOW_SIZE) {
        value_avg_buffer[index] = analogRead(PHOTORESISTOR_PIN);
        value_avg_running += value_avg_buffer[index];
        time_buffer[index] = float(millis()) / 1000;
        index++;
        delay(10);
    }
    index = 0;
    value_avg_running /= float(WINDOW_SIZE);

    Serial.println("Starting recording data");
}

void real_loop() {
    // digitalWrite(RELAY_PIN, HIGH);
    // delay(999999);

    if (valve_open_time == 0) {
        if (analogRead(VALVE_PIN) < VALVE_PIN_LIMIT) {
            return;
        } else {
            delay(5);
            if (analogRead(VALVE_PIN) < VALVE_PIN_LIMIT) {
                return;
            }
            valve_open_time = float(millis()) / 1000;
            Serial.println("Valve Opened");
        }
    }

    float time = float(millis()) / 1000;
    float value = float(analogRead(PHOTORESISTOR_PIN));
    value_avg_running += (value - value_avg_buffer[index]) / WINDOW_SIZE;
    // Serial.println("Time: " + String(time) + ", Rem Time: " + String(time_buffer[index]) + ", Value Avg: " + String(value_avg_running) + ", Rem Value Avg " + String(value_avg_buffer[index]));
    float slope = (value_avg_running - value_avg_buffer[index]) / (time - time_buffer[index]);
    value_avg_buffer[index] = value_avg_running;
    time_buffer[index] = time;
    index = (index + 1) % WINDOW_SIZE;

    Serial.println(String(time) + ", " + String(value) + ", " + String(slope));

    if (car_timed) {
        return;
    }

    if (car_start_time == 0) {
        if (float(millis()) / 1000 - valve_open_time < car_start_delay) {
            return;
        }
        car_start_time = float(millis()) / 1000;
        digitalWrite(RELAY_PIN, HIGH);
    }

    if (abs(slope) > biggest_slope) {
        biggest_slope = abs(slope);
        time_of_biggest_slope = time;
    }

    if (abs(slope) > slope_limit && slope < biggest_slope) {
        Serial.println("Stopped recording data");
        time_car(time_of_biggest_slope);
    }
}

void time_car(float time_of_biggest_slope) {
    float time_from_valve = time_of_biggest_slope - valve_open_time;
    float KI = x * pow(time_from_valve, y);
    float distance = 15 + (KI - min_KI) / (max_KI - min_KI) * 15;
    float time = (distance / speed);  // ms
    Serial.println("Biggest Slope: " + String(biggest_slope));
    Serial.println("Time of Biggest Slope: " + String(time_from_valve));
    Serial.println("KI: " + String(KI));
    Serial.println("Distance: " + String(distance));
    Serial.println("Wait Time: " + String(time));

    car_timed = true;
    float curr_time = float(millis()) / 1000;
    float time_left = time - (curr_time - valve_open_time) + car_start_delay;
    Serial.println("Time Left: " + String(time_left));
    delay(time_left * 1000);
    digitalWrite(RELAY_PIN, LOW);
    delay(999999);
}

void data_setup() {
    Serial.begin(9600);
    pinMode(VALVE_PIN, INPUT);
    Serial.println("Starting recording data");
}

void data_loop() {
    if (digitalRead(VALVE_PIN) != HIGH && valve_open_time == 0) {
        return;
    }

    if (valve_open_time == 0) {
        valve_open_time = millis();
        Serial.println("Valve Opened");
    }

    long time = float(millis() - valve_open_time);
    int value = analogRead(PHOTORESISTOR_PIN);
    Serial.println(String(time) + ", " + String(value));
    delay(10);
}