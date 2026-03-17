#include "main.hpp"

// ------- Objects -------
ReactionOut reaction;
Filter valueFilter(WINDOW_SIZE);
Filter derFilter(WINDOW_SIZE);
DDx derivative(DT);
Adafruit_AS7341 Color_Sensor;
Car car;
// -----------------------

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

// inits car and reaction time variables; makes sure relay is off
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

void collectData(float* data){
    if (car.reaction_done){
        return;
    }
    int b = 16;
    // data[0] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_415nm_F1) / pow(2,b) * 100;
    // data[1] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_445nm_F2) / pow(2,b) * 100;
    // data[2] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_480nm_F3) / pow(2,b) * 100;
    // data[3] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_515nm_F4) / pow(2,b) * 100;
    // data[4] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_555nm_F5) / pow(2,b) * 100;
    // data[5] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_590nm_F6) / pow(2,b) * 100;
    // data[6] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_630nm_F7) / pow(2,b) * 100;
    data[0] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_680nm_F8) / pow(2,b) * 100;
    data[1] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_CLEAR) / pow(2,b) * 100;
}

void analyze(float* data){
    if (car.reaction_done){
        return;
    }
    float_pair red_values = analyze_number(data[0]);
    float_pair clear_values = analyze_number(data[1]);

    // detect if done
    if ((millis() - car.time_valve_open) > SLOPE_GRACE_PERIOD && abs(red_values.second) < SLOPE_TRIGGER_VALUE){
        reaction.time_reaction_end = millis() - car.time_valve_open;
        car.reaction_done = true;
        reaction.reaction_value = red_values.first;
        Serial.println("reaction time end: " + String(reaction.time_reaction_end));
    }
}

float_pair analyze_number(float num) {
    double time = millis();
    double value = VALUE_GAIN * num;
    double avg_value = valueFilter.average(value);
    double delta_value = derivative.change(value);
    double avg_delta_value = derFilter.average(delta_value);

    Serial.println("DATA: " + String(time, 3) + " Value: " + String(value, 4) + " Average Value: " + String(avg_value, 4) + " Delta: " + String(delta_value, 4) + " Average Delta: " + String(avg_delta_value));

    float_pair avg_values;
    avg_values.first = avg_value;
    avg_values.second = avg_delta_value;
    return avg_values;
}

void calcDistance(){
    if (car.calculated_distance_bool){
        return;
    }

    float distance = CURVE_A * car.reaction_done + CURVE_B;
    if (reaction.reaction_value < 3.5){
        distance += 15;
    }
    // distance = 19.9; // testing purposes; runs with predetermined distance

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
