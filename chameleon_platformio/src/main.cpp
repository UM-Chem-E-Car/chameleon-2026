#include "main.hpp"

// ------- Objects -------
ReactionOut reaction;
Filter valueFilter(WINDOW_SIZE);
Filter derFilter(WINDOW_SIZE);

RunningMedian valueMedian;
RunningMedian derMedian;

DDx derivative(DT);
Color_Sensor sensor(25, 99, 10000);
Car car;
// -----------------------

void setup(){
    Serial.begin(9600);
    init_variables();
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(VALVE_PIN_IN, INPUT);     

    Serial.println("Program Started");

}

void loop(){

    // //REPLACE

    sensor.gatherData();



    waitForValveOpen();
    
    if (car.stage == Car::Stage::WAITING_FOR_VALVE_OPEN){
        return;
    }
    
    if (car.status == Car::Status::BEFORE_RUN) {
        if (car.currentTime() > 10000) {
            car.status = Car::Status::RUN_BEFORE_RXN;
        }
    }
    
    if (sensor.ready_to_read){

        //MEASURING DATA
        Color_Sensor::Data data = sensor.getReadings();


        //ANALYSE DATA

        double time = millis();
        //PLACE VARIABLE HERE
        double value = data.r/data.o;
        //valueMedian.add(value);
        double avg_value = valueFilter.average(value);
        double delta_value = derivative.change(value);

        //derMedian.add(delta_value);
        double avg_delta_value = derFilter.average(delta_value);


        //PRINTING DATA
        //Serial.println("TIME: " + String(millis() - car.time_valve_open) + " " + data.tostring());
        
        double printarr[] = {millis() - car.time_valve_open, data.v, data.b, data.c, data.g, data.gy, data.y, data.o, data.r, data.cl, data.nir, value, avg_value, delta_value, avg_delta_value};
        printData(printarr, 16);

        //Serial.println(String(car.currentTime(), 3) + ", " + String(value, 4) + ", " + String(avg_value, 4) + ", " + String(delta_value, 4) + ", " + String(avg_delta_value, 6));
        
        
        //MY CODE
        if (car.stage == Car::Stage::RECORDING_DATA && SLOPE_GRACE_PERIOD < car.currentTime() && abs(avg_delta_value) < TRIGGER_VALUE){
            if (!car.first_delta_hit) {
                Serial.println("FIRST DELTA HIT");
                car.first_delta_hit = true;
            } else {
                Serial.println("RXN DONE");
                car.stage = Car::Stage::CALCULATING_DISTANCE;
                reaction.time_reaction_end = car.currentTime();
                reaction.reaction_value = avg_delta_value;
            }
        }
    }


    if (car.stage == Car::Stage::CALCULATING_DISTANCE){
        calcMotorRuntime();
    }
    
    
    if (car.status == Car::Status::RUN_BEFORE_RXN){
        //moveCarBeforeRXN(); // currently just digitalWrite(RELAY_PIN, HIGH);
        // car.status = Car::Status::RUN_AFTER_RXN;
    }
    
}

// inits car and reaction time variables; makes sure relay is off
void init_variables(){
    car.time_valve_open = -1;
    car.stage = Car::Stage::WAITING_FOR_VALVE_OPEN;
    car.status = Car::Status::BEFORE_RUN;
    reaction.time_reaction_end = -1;
    car.time_to_run = -1;
    car.time_car_move = -1;
    reaction.reaction_value = -1;
    car.first_delta_hit = false;
    sensor.init();


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
    car.stage = Car::Stage::RECORDING_DATA;
    Serial.println("VALVE IS ON");
    sensor.gatherData();

    Serial.println("Integration Time: " + String(sensor.getIntegrationTimeInMiliseconds()));
    Serial.println("Time, v, b, c, g, gy, y, o, r, cl, nir, Value, Average Value, Delta, Average Delta");

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

void printData(double args[], size_t size){
    String e = "";
    for (size_t x = 0; x < size-1; x++){
        e += String(args[x], 6) + ", ";
    }
    e += String(args[size-1], 6);
    Serial.println(e);
}


void analyze(const Color_Sensor::Data &data) { 
    // if (car.reaction_done){
    //     return;
    // }
    //float_pair red_values = analyze_number(data[0]);
    // float_pair clear_values = analyze_number(data[1]);

    // TODO: USE BOTH RED AND CLEAR VALUES AND DETECT CHANGE
    // detect if done

    // if ((millis() - car.time_valve_open) > SLOPE_GRACE_PERIOD && abs(red_values.first - reaction.init_reaction_value) > TRIGGER_VALUE){
    //     reaction.time_reaction_end = millis() - car.time_valve_open;
    //     car.reaction_done = true;
    //     reaction.reaction_value = red_values.first;
    //     Serial.println("reaction time end: " + String(reaction.time_reaction_end));
    // }
}

// float_pair analyze_number(float num) {
//     double time = millis();
//     double value = VALUE_GAIN * num;
//     double avg_value = valueFilter.average(value);
//     double delta_value = derivative.change(value);
//     double avg_delta_value = derFilter.average(delta_value);

//     Serial.println("DATA: " + String(time, 3) + " Value: " + String(value, 4) + " Average Value: " + String(avg_value, 4) + " Delta: " + String(delta_value, 4) + " Average Delta: " + String(avg_delta_value));

//     float_pair avg_values;
//     avg_values.first = value;
//     avg_values.second = avg_delta_value;
//     return avg_values;
// }

void calcMotorRuntime(){

    float estimated_distance = CURVE_A * reaction.time_reaction_end + CURVE_B;
    car.time_to_run = (estimated_distance / CAR_A + CAR_B)*1000;
    car.time_car_move = millis();
    Serial.println("Calculated Distance: " + String(estimated_distance));
    Serial.println("TIMETORUN: " + String(car.time_to_run));
    car.stage = Car::Stage::MOVING_CAR;

}

void moveCarBeforeRXN() {
    digitalWrite(RELAY_PIN, HIGH);
}

void moveCar(){
    //Serial.println("TIME LEFT: " + String((car.time_car_move + car.time_to_run - millis())/1000));

    if (millis() < car.time_car_move + car.time_to_run){
        digitalWrite(RELAY_PIN, HIGH);
    } else {
        digitalWrite(RELAY_PIN, LOW);
        Serial.println("Done Moving Car");
        car.stage = Car::Stage::PROGRAM_DONE;
        car.status = Car::Status::AFTER_RUN;
        // delay(100);
        // exit(0);
    }

}
