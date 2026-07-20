#pragma once

#define VALVE_PIN A2
#define RELAY_PIN A0
#define VALVE_PIN_INPUT_LIMIT 50

struct Config {

    struct Runtime {
        int DT;
        int SLOPE_GRACE_PERIOD;
    } RUNTIME;

    struct Filter {
        int WINDOW_SIZE;
    } FILTER;

    struct Sensor {
        int ATIME;
        int ASTEP;
        double VALUE_GAIN;

    } SENSOR;
    
    struct Reaction {
        double TRIGGER_VALUE;
        int TRIGGER_COUNT;
    } REACTION;

    struct Car {
        double CAR_A;
        double CAR_B;
        double CURVE_A;
        double CURVE_B;
    } CAR;

    struct Logging {
        enum LogMode{
            MAIN,
            CSV
        } LOGMODE;
        int SERIAL_PORT;

        double PRINT_END_CHAR;
        const char* FIELDS;
    } LOGGING;

};

extern Config CONFIG;
