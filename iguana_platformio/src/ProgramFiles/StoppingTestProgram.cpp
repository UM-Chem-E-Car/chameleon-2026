#include "RunProgram.cpp"

class StoppingTestProgram : public RunProgram {
    bool collect_and_check_data() override {
        RunProgram::collect_and_check_data();
        if (run_data.currentTime() >= CONFIG::TESTING::STOPPING_END_TEST_TIME){
            return true;
        }
        return false;
    }
    
    bool move_car() override {
        logger.log("RUN_COMPLETE", Logger::LogType::HEADER);
        return false;
    }
};


/*
B1 40.59
B2 26.22
B3 24.52
B4 11.86
B5 13.85

*/