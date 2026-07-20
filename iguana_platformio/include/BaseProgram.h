#pragma once

#include "ProgramInterface.h"
#include "Logger.h"
#include "RunVariables.h"

class BaseProgram : public Program {

public:
    void hardware_setup_impl() override;
    void software_setup_impl() = 0;
    void spin_once() final;

protected:
    BaseProgram();
    BaseProgram(Logger& logger_in);



    void finish();
    bool wait_for_valve_open();

    virtual void background_tasks() = 0;
    virtual bool collect_and_check_data() = 0;
    virtual void calculate_car_run_time() = 0;
    virtual bool move_car() = 0;

protected:
    Logger& logger;
};


