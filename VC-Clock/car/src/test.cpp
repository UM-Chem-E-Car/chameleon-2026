#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Filter.cpp>
#include <Adafruit_AS7341.h>

#define VALVE_PIN_IN A3
#define VALVE_PIN_INPUT_LIMIT 500
#define RELAY_PIN 6


#define DT 100
#define WINDOW_SIZE 5
#define VALUE_GAIN 100
#define SLOPE_GRACE_PERIOD 3000
#define SLOPE_TRIGGER_VALUE 1


#define SPEED .05
#define CURVE_A -.15
#define CURVE_B 24.75

Adafruit_AS7341 Color_Sensor;

struct Car{
    float time_valve_open;
    bool reaction_done;
    bool calculated_distance_bool;
    
    float time_to_run;


    float time_car_move;
};
Car car;

struct ReactionOut{
    float time_reaction_end;
    float reaction_value;

};
ReactionOut reaction;

Filter valueFilter(WINDOW_SIZE);
Filter derFilter(WINDOW_SIZE);
DDx derivative(DT);



void init_variables(){
    car.time_valve_open = -1;
    car.reaction_done = false;
    reaction.time_reaction_end = -1;
    car.time_to_run = -1;
    car.calculated_distance_bool = false;
    car.time_car_move = -1;
    reaction.reaction_value = -1;

    digitalWrite(RELAY_PIN, LOW);

}



void collectData(float* data){
    if (car.reaction_done){
        return;
    }
    int b = 16;
    data[0] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_415nm_F1) / pow(2,b) * 100;
    data[1] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_445nm_F2) / pow(2,b) * 100;
    data[2] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_480nm_F3) / pow(2,b) * 100;
    data[3] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_515nm_F4) / pow(2,b) * 100;
    data[4] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_555nm_F5) / pow(2,b) * 100;
    data[5] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_590nm_F6) / pow(2,b) * 100;
    data[6] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_630nm_F7) / pow(2,b) * 100;
    data[7] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_680nm_F8) / pow(2,b) * 100;
}

void analyze(float* data){
    if (car.reaction_done){
        return;
    }
    double time = millis();
    double value = VALUE_GAIN * data[7];
    double average_value = valueFilter.average(value);
    double delta_value = derivative.change(value);
    double average_delta_value = derFilter.average(delta_value);

    Serial.println("DATA: " + String(time, 3) + " Value: " + String(value, 4) + " Average Value: " + String(average_value, 4) + " Delta: " + String(delta_value, 4) + " Average Delta: " + String(average_delta_value, 4));

    //detect if done

    if ((millis() - car.time_valve_open) > SLOPE_GRACE_PERIOD && abs(average_delta_value) < SLOPE_TRIGGER_VALUE){
        reaction.time_reaction_end = millis() - car.time_valve_open;
        car.reaction_done = true;
        reaction.reaction_value = average_value;
        Serial.println("TLKSDJF: " + String(reaction.time_reaction_end));
    }

}

void waitForValveOpen(){
    if (car.time_valve_open > 0){
        return;
    }

    if (analogRead(VALVE_PIN_IN) <= VALVE_PIN_INPUT_LIMIT) {
        Serial.println("Waiting For Valve On");
        
    } 
    delay(5);
    if (analogRead(VALVE_PIN_IN) <= VALVE_PIN_INPUT_LIMIT) {
        return;
    }

    car.time_valve_open = millis();
    car.reaction_done = true;
    
}

void calcDistance(){
    if (car.calculated_distance_bool){

        return;
    }

    float distance = CURVE_A * car.reaction_done + CURVE_B;
    if (reaction.reaction_value < 3.5){
        distance += 15;
    }
    distance = 19.9;


    car.time_to_run = distance * 100 / SPEED;
    Serial.println("Calculated Distance: " + String(distance));
    Serial.println("TIMETORUN: " + String(car.time_to_run));
    car.calculated_distance_bool = true;



}

void moveCar(){
    //Serial.println("TIME LEFT: " + String(millis() - car.time_car_move - car.time_to_run));
    if (car.time_car_move == -1){
        car.time_car_move = millis();
        digitalWrite(RELAY_PIN, HIGH);
    }

    if (millis() - car.time_car_move - car.time_to_run >= 0){
        digitalWrite(RELAY_PIN, LOW);
        Serial.println("DONE MOVING CAR");
        exit(0);
    }

}


void setup(){
    Serial.begin(9600);
    init_variables();
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(VALVE_PIN_IN, INPUT);     

    if (!Color_Sensor.begin()){
        Serial.println("Could not find AS7341");
        while (1) {
            delay(10); 
        }
    }
    Color_Sensor.setATIME(30);
    Color_Sensor.setASTEP(200);
    // Color_Sensor.setASTEP((dt/2.78e-6 - 1)*1000);
    Color_Sensor.setGain(AS7341_GAIN_256X);
    Serial.println("Program Started");

}

void loop(){


    delay(DT);
    if (!Color_Sensor.readAllChannels()){
        Serial.println("Cannot Read Channels");
        return;
    }

    waitForValveOpen();

    // if (car.time_valve_open == -1){
    //     return;
    // }

    // float data[8];
    // collectData((float*)&data);


    //MEASUREDATA
    // analyze(data);

    if (!car.reaction_done){
        return;
    }
    
    calcDistance();
    
    moveCar();
    



}