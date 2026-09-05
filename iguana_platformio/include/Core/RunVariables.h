#pragma once

#include <Arduino.h>

struct RunData {
    enum Stage{
        WAITING_FOR_VALVE_OPEN, RECORDING_DATA, CALCULATING_DISTANCE, MOVING_CAR, PROGRAM_DONE
    } stage;

    float valve_open_time;
    float time_to_run;

    float init_reaction_value;
    float time_reaction_end;
    float reaction_value;

    int triggers_hit;

    float currentTime(){
        return millis() - valve_open_time;
    }

    float timeLeftToRun(){
        return millis() - time_to_run;
    }

    RunData() : 
        stage(WAITING_FOR_VALVE_OPEN), 
        valve_open_time(-1), 
        time_to_run(-1),
        init_reaction_value(-1),
        time_reaction_end(-1),
        reaction_value(-1),
        triggers_hit(0){}


};

//extern RunData RUN_DATA;

