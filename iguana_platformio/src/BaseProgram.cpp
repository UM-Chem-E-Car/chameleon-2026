#include "BaseProgram.h"
#include "ConfigVariables.h"

RunData RUN_DATA;

BaseProgram::BaseProgram() : BaseProgram(Logger::instance()) {}

BaseProgram::BaseProgram(Logger& logger_in) : logger(logger_in) {}

void BaseProgram::hardware_setup_impl(){
    logger.log("Program Start");
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(VALVE_PIN, INPUT);     
    logger.log("Hardware Setup Finished");
}

void BaseProgram::finish(){
    logger.log("Program Finished");
    exit(0);
}

bool BaseProgram::wait_for_valve_open(){
    if (analogRead(VALVE_PIN) <= VALVE_PIN_INPUT_LIMIT) {
        return false;
    }
    delay(5);
    if (analogRead(VALVE_PIN) <= VALVE_PIN_INPUT_LIMIT) {
        return false;
    }

    logger.log("Valve Opened");
    logger.log(CONFIG.LOGGING.FIELDS, Logger::LogType::HEADER);

    return true;
}


void BaseProgram::spin_once() {
    background_tasks();
    if (RUN_DATA.stage == RunData::WAITING_FOR_VALVE_OPEN){
        bool valve_opened = wait_for_valve_open(); 
        if (valve_opened)
            RUN_DATA.stage = RunData::RECORDING_DATA;
        else
            return;
    } 
    
    if (RUN_DATA.stage == RunData::RECORDING_DATA) {
        bool reaction_end = collect_and_check_data();
        if (reaction_end)
            RUN_DATA.stage = RunData::CALCULATING_DISTANCE;
        else
            return;
    }

    if (RUN_DATA.stage == RunData::CALCULATING_DISTANCE){
        calculate_car_run_time();
        RUN_DATA.stage = RunData::MOVING_CAR;
    }
        
    if (RUN_DATA.stage == RunData::MOVING_CAR){
        bool car_done_moving = move_car();
        if (car_done_moving){
            RUN_DATA.stage = RunData::PROGRAM_DONE;
        }

    }

    finish();
}


