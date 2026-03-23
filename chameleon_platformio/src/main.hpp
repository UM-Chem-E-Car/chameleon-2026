#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Filter.cpp>
#include <Adafruit_AS7341.h>

#define VALVE_PIN_IN A0
#define VALVE_PIN_INPUT_LIMIT 500
#define RELAY_PIN 6


#define DT 250
#define WINDOW_SIZE 15
#define VALUE_GAIN 100
#define SLOPE_GRACE_PERIOD 15000
#define SLOPE_TRIGGER_VALUE 250

#define SPEED 0.15
#define CURVE_A -.25
#define CURVE_B 33.75

struct Car {
    float time_valve_open;
    bool reaction_done;
    bool calculated_distance_bool;
    
    float time_to_run;

    float time_car_move;
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