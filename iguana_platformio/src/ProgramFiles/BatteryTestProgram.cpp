#include "RunProgram.cpp"

class BatteryTestProgram : public RunProgram {
    bool collect_and_check_data() override {
        return true;
    }

    void calculate_car_run_time() override {
        TimeData simulatedReaction;
        simulatedReaction.time_reaction_end = CONFIG::TESTING::BATTERY_SIMULATED_END_TIME;

        calcDist.calculate(simulatedReaction);
        timeRun.calculate(calcDist.getDistance());
        run_data.time_to_run = timeRun.getTimeRun() + run_data.currentTime();
        logger.log("Calculated Distance: " + String(calcDist.getDistance()));
        logger.log("TIMETORUN: " + String(timeRun.getTimeRun()));
    }

};