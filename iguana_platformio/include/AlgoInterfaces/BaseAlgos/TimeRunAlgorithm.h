#pragma once

class TimeRunAlgorithm {
public:

    virtual void calculate(double distance) = 0;
    virtual double getTimeRun() = 0;

    virtual ~TimeRunAlgorithm() = default;
};