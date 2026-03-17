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

struct Car {
    float time_valve_open;
    bool reaction_done;
    bool calculated_distance_bool;
    
    float time_to_run;

    float time_car_move;
};

struct ReactionOut {
    float time_reaction_end;
    float reaction_value;
};

void init_variables();
void collectData(float* data);
void analyze(float* data);
void waitForValveOpen();
void calcDistance();
void moveCar();