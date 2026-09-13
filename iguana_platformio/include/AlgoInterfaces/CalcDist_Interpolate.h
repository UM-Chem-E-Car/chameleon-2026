#pragma once

#include "AlgoInterfaces/CustomDataType/TimeData.h"

class CalcDist_Interpolate{
public:

    CalcDist_Interpolate() : STORED_DISTANCE(-1) {}

    void calculate(const ValueDiff& reactionSummary){
        STORED_DISTANCE = CURVE_A * reactionSummary.diff + CURVE_B;
    }

    double getDistance() {
        return STORED_DISTANCE;
    }

private:
    const double CURVE_A = 0;
    const double CURVE_B = 17.10; 


    double STORED_DISTANCE;
};