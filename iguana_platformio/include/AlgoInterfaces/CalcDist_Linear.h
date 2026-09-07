#pragma once

#include "AlgoInterfaces/BaseAlgos/CalcDistAlgorithm.h"
#include "AlgoInterfaces/RxnOver_RedOrange.h"

namespace CONSTS {
    constexpr double CURVE_A = -0.000375;
    constexpr double CURVE_B = 37.5; 
}

class CalcDist_Linear : public CalcDistAlgorithm<TimeAndRegimeData>{
public:

    typedef TimeAndRegimeData RxnData;

    CalcDist_Linear();

    void calculate(const RxnData& reactionSummary) override;
    double getDistance() override;

private:
    double STORED_DISTANCE;
};