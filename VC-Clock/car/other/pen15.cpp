// #include <Arduino.h>
// #include <SoftwareSerial.h>

// #define WINDOW_SIZE 20
// #define PHOTORESISTOR_PIN A0
// #define VALVE_PIN 2
// #define RELAY_PIN 3

// int value_avg_running = 0;
// int value_avg_buffer[WINDOW_SIZE];
// float time_buffer[WINDOW_SIZE];
// float slope_buffer[WINDOW_SIZE];
// int index = 0;
// float biggest_slope = 0;
// int time_of_biggest_slope = 0;
// int valve_open_time = 0;

// float slope_limit = 50;

// float min_KI;
// float max_KI;
// float speed;
// float x;  // x = exp(-b/a)
// float y;  // y = 1/a

// void real_setup();
// void real_loop();
// void data_setup();
// void data_loop();
// void time_car();

// void setup() {
//     real_setup();
// }

// void loop() {
//     real_loop();
// }

// void real_setup() {
//     Serial.begin(9600);
//     pinMode(VALVE_PIN, INPUT);
//     pinMode(RELAY_PIN, OUTPUT);
//     digitalWrite(RELAY_PIN, LOW);

//     // fill array with values
//     while (index < WINDOW_SIZE) {
//         value_avg_buffer[index] = analogRead(PHOTORESISTOR_PIN);
//         time_buffer[index] = millis() / 1000;
//         slope_buffer[index] = 0;
//         index++;
//         delay(10);
//         value_avg_running += value_avg_buffer[index];
//     }
//     index = 0;
//     value_avg_running /= WINDOW_SIZE;

//     Serial.println("Starting recording data");
// }

// void real_loop() {
//     if (digitalRead(VALVE_PIN) != HIGH && valve_open_time == 0) {
//         return;
//     }

//     if (valve_open_time == 0) {
//         valve_open_time = millis();
//         Serial.println("Valve Opened");
//     }

//     float time = float(millis()) / 1000;
//     int value = analogRead(PHOTORESISTOR_PIN);
//     value_avg_running += (float(value) - value_avg_buffer[index]) / WINDOW_SIZE;
//     Serial.println(String(value_avg_running) + " " + String(value_avg_buffer[index]) + " " + String(time) + " " + String(time_buffer[index]));
//     float slope = (float(value_avg_running) - float(value_avg_buffer[index])) / (float(time) - float(time_buffer[index]));
//     value_avg_buffer[index] = value_avg_running;
//     time_buffer[index] = time;
//     slope_buffer[index] = slope;
//     index = (index + 1) % WINDOW_SIZE;

//     Serial.println(String(time) + ", " + String(value) + ", " + String(slope));

//     if (time < 2) {
//         return;
//     }

//     if (abs(slope) > biggest_slope) {
//         biggest_slope = abs(slope);
//         time_of_biggest_slope = time;
//     }

//     if (abs(slope) > slope_limit && slope < biggest_slope) {
//         Serial.println("Stopped recording data");
//         time_car();
//     }
// }

// void time_car() {
//     float time_from_valve = float(millis() - valve_open_time) / 1000;
//     float KI = x * pow(time_from_valve, y);
//     float distance = 15 + (KI - min_KI) / (max_KI - min_KI) * 15;
//     long time = long(distance / speed * 1000);  // ms
//     Serial.println("Biggest Slope: " + String(biggest_slope));
//     Serial.println("Time of Biggest Slope: " + String(time_from_valve));
//     Serial.println("KI: " + String(KI));
//     Serial.println("Distance: " + String(distance));

//     digitalWrite(RELAY_PIN, HIGH);
//     delay(time);
//     digitalWrite(RELAY_PIN, LOW);
//     delay(999999);
// }

// void data_setup() {
//     Serial.begin(9600);
//     pinMode(VALVE_PIN, INPUT);
//     Serial.println("Starting recording data");
// }

// void data_loop() {
//     if (digitalRead(VALVE_PIN) != HIGH && valve_open_time == 0) {
//         return;
//     }

//     if (valve_open_time == 0) {
//         valve_open_time = millis();
//         Serial.println("Valve Opened");
//     }

//     long time = float(millis() - valve_open_time);
//     int value = analogRead(PHOTORESISTOR_PIN);
//     Serial.println(String(time) + ", " + String(value));
//     delay(10);
// }