#pragma once

#include "AlgoInterfaces/CustomDataType/TimeData.h"

class CalcDist_Linear{
public:

    CalcDist_Linear() : STORED_DISTANCE(-1) {}

    void calculate(const TimeData& reactionSummary){
        STORED_DISTANCE = CURVE_A * reactionSummary.time_reaction_end + CURVE_B;
    }

    double getDistance() {
        return STORED_DISTANCE;
    }

private:
    const double CURVE_A = -0.000375;
    const double CURVE_B = 37.5; 


    double STORED_DISTANCE;
};