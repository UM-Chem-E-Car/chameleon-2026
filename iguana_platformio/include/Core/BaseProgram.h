#pragma once

#include "ProgramInterface.h"

class BaseProgram : public Program {

public:
    void setup_impl() override;
    void loop_impl() final;

protected:
    BaseProgram();



    virtual void finish();
    virtual bool wait_for_valve_open() = 0;
    virtual void collect_initial_data() = 0;

    virtual void spin_once() = 0;
    virtual bool collect_and_check_data() = 0;
    virtual void calculate_car_run_time() = 0;
    virtual bool move_car() = 0;


};


