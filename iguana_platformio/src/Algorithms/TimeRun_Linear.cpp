#include "AlgoInterfaces/TimeRun_Linear.h"
#include "Utility/Logger.h"


TimeRun_Linear::TimeRun_Linear() : STORED_TIME(-1){}

void TimeRun_Linear::calculate(double distance) {
    STORED_TIME = (distance / CONSTS::CAR_A + CONSTS::CAR_B)*1000;
}

double TimeRun_Linear::getTimeRun() {
    if (STORED_TIME == -1){Logger::instance().log("INVALID TIME", Logger::LogType::ERROR);}
    return STORED_TIME;
}