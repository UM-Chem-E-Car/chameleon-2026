#pragma once

#include "AlgoInterfaces/BaseAlgos/TimeRunAlgorithm.h"

namespace CONSTS {
    constexpr double CAR_A = 0.5657;
    constexpr double CAR_B = 0.000007;
}

class TimeRun_Linear : public TimeRunAlgorithm {
public:
    TimeRun_Linear();

    void calculate(double distance) override;
    double getTimeRun() override;

private:
    double STORED_TIME;
};