#include "RunProgram.cpp"

class BatteryTestProgram : public RunProgram {
    bool collect_and_check_data() override {
        run_data.time_reaction_end = CONFIG::TESTING::BATTERY_SIMULATED_END_TIME;
        run_data.reaction_value = CONFIG::TESTING::BATTERY_SIMULATED_VALUE;
        return true;
    }

};