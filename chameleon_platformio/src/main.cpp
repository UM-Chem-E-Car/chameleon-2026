#include "main.hpp"

// ------- Objects -------
ReactionOut reaction;
Filter valueFilter(WINDOW_SIZE);
Filter derFilter(WINDOW_SIZE);
DDx derivative(DT);
Color_Sensor sensor;
Car car;
// -----------------------

void setup(){
    Serial.begin(9600);
    init_variables();
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(VALVE_PIN_IN, INPUT);     


    // Color_Sensor.setASTEP((dt/2.78e-6 - 1)*1000);
    Serial.println("Program Started");

}

void loop(){

    // Serial.println("RUNNING CAR");
    // digitalWrite(RELAY_PIN, HIGH);
    // return;
    // //REPLACE

    sensor.gatherData();
    delay(DT);


    waitForValveOpen();
    
    if (car.time_valve_open == -1){
        return;
    }
    
    
    if (!sensor.ready_to_read){
        return;
    }
    
    Color_Sensor::Data data = sensor.getReadings();



    //TEMP SHIT TO TEST IF READING WORKS
    Serial.println("TIME: " + String(millis() - car.time_valve_open) + " " + data.toString());

    if (SLOPE_GRACE_PERIOD < millis() - car.time_valve_open && !car.reaction_done){
        Serial.println("INIT VALUE: " + String(reaction.init_reaction_value) + " Final: " + String(data.r) + " TIME: " + String(millis() - car.time_valve_open));
        Serial.println("DIFF " + String(data.r - reaction.init_reaction_value));
        calcMotorRuntime();
    }

    return;

    // MEASUREDATA
    // analyze(data);

    if (!car.reaction_done){
        return;
    }
    
    calcMotorRuntime();
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
    sensor.init(29, 599);

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
    
    Serial.println("VALVE IS ON");
    sensor.gatherData();
    if (sensor.ready_to_read){
        reaction.init_reaction_value = sensor.getReadings().r;
    }

}

// void collectData(float* data){
//     if (car.reaction_done){
//         return;
//     }
//     int b = 16;
//     data[0] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_680nm_F8) / pow(2,b) * 100;
//     data[1] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_CLEAR) / pow(2,b) * 100;
// }

void analyze(const Color_Sensor::Data &data) { 
    if (car.reaction_done){
        return;
    }
    //float_pair red_values = analyze_number(data[0]);
    // float_pair clear_values = analyze_number(data[1]);

    // TODO: USE BOTH RED AND CLEAR VALUES AND DETECT CHANGE
    // detect if done

    // if ((millis() - car.time_valve_open) > SLOPE_GRACE_PERIOD && abs(red_values.first - reaction.init_reaction_value) > SLOPE_TRIGGER_VALUE){
    //     reaction.time_reaction_end = millis() - car.time_valve_open;
    //     car.reaction_done = true;
    //     reaction.reaction_value = red_values.first;
    //     Serial.println("reaction time end: " + String(reaction.time_reaction_end));
    // }
}

float_pair analyze_number(float num) {
    double time = millis();
    double value = VALUE_GAIN * num;
    double avg_value = valueFilter.average(value);
    double delta_value = derivative.change(value);
    double avg_delta_value = derFilter.average(delta_value);

    Serial.println("DATA: " + String(time, 3) + " Value: " + String(value, 4) + " Average Value: " + String(avg_value, 4) + " Delta: " + String(delta_value, 4) + " Average Delta: " + String(avg_delta_value));

    float_pair avg_values;
    avg_values.first = value;
    avg_values.second = avg_delta_value;
    return avg_values;
}

void calcMotorRuntime(){
    car.reaction_done = true;
    return;
    //TEMP

    if (car.calculated_distance_bool){
        return;
    }

    float distance = CURVE_A * car.reaction_done + CURVE_B;
    car.time_to_run = distance * 100 / SPEED;
    Serial.println("Calculated Distance: " + String(distance));
    Serial.println("TIMETORUN: " + String(car.time_to_run));
    car.calculated_distance_bool = true;

   // car.time_to_run = CURVE_A * car.reaction_done + CURVE_B;

    Serial.println("Calculated runtime: " + String(car.time_to_run));
    Serial.println("time car move" + String(car.time_car_move));
    Serial.println("TIMETORUN: " + String(car.time_to_run));
    car.calculated_distance_bool = true;
}

void moveCar(){
    //Serial.println("TIME LEFT: " + String(millis() - car.time_car_move - car.time_to_run));
    if (car.time_car_move == -1) {
        car.time_car_move = millis();
        //Serial.println("new time car move " + String(car.time_car_move));
        digitalWrite(RELAY_PIN, HIGH);
    }
    Serial.println("difference: " + String(millis() - car.time_car_move - car.time_to_run));

    if (millis() - car.time_car_move - car.time_to_run  >= 0){
        Serial.println("MILILIW " + String(millis()));
        digitalWrite(RELAY_PIN, LOW);
        Serial.println("DONE MOVING CAR");
        delay(1000);
        exit(0);
    }

}
