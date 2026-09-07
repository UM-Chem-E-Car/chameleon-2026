#include "AlgoInterfaces/CalcDist_Linear.h"
#include "Utility/Logger.h"

CalcDist_Linear::CalcDist_Linear() : STORED_DISTANCE(-1){}

void CalcDist_Linear::calculate(const CalcDist_Linear::RxnData& rxnData) {
    STORED_DISTANCE = CONSTS::CURVE_A * rxnData.time_reaction_end + CONSTS::CURVE_B;
}

double CalcDist_Linear::getDistance(){
    if (STORED_DISTANCE == -1){Logger::instance().log("INVALID DISTANCE", Logger::LogType::ERROR);}
    return STORED_DISTANCE;
}