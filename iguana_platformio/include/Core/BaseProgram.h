#pragma once

#include "ProgramInterface.h"
#include "Utility/Logger.h"
#include "Core/RunVariables.h"

class BaseProgram : public Program {

public:
    void setup_impl() override;
    void loop_impl() final;

protected:
    BaseProgram();
    BaseProgram(Logger& logger_in);



    void finish();
    virtual bool wait_for_valve_open() = 0;

    virtual void spin_once() = 0;
    virtual bool collect_and_check_data() = 0;
    virtual void calculate_car_run_time() = 0;
    virtual bool move_car() = 0;

protected:
    Logger& logger;
};


