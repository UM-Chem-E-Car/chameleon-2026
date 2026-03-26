#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Filter.cpp>
#include <Adafruit_AS7341.h>
#include <Sensor.cpp>

#define VALVE_PIN_IN A0
#define VALVE_PIN_INPUT_LIMIT 500
#define RELAY_PIN 6


#define DT 250
#define WINDOW_SIZE 3
#define VALUE_GAIN 100
#define SLOPE_GRACE_PERIOD 10000
#define TRIGGER_VALUE 0.0005


//15-75
#define SPEED 0.416
#define CURVE_A -0.00025
#define CURVE_B 33.75

struct Car {
    enum Stage{
        WAITING_FOR_VALVE_OPEN, RECORDING_DATA, CALCULATING_DISTANCE, MOVING_CAR, PROGRAM_DONE
    };

    Stage stage;
       
    float time_valve_open;
    float time_to_run;
    float time_car_move;

    bool first_delta_hit;

    float currentTime(){
        return millis() - time_valve_open;
    }

    float timeLeftToRun(){
        return millis() - time_to_run;
    }


};

struct ReactionOut {
    float time_reaction_end;
    float init_reaction_value;
    float reaction_value;
};

struct float_pair {
    float first;
    float second;
};

void init_variables();
void collectData(float* data);
void analyze(float* data);
float_pair analyze_number(float num);
void waitForValveOpen();
void calcMotorRuntime();
void moveCar();