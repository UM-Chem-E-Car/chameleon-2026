#pragma once

template <typename RxnDataType>
class CalcDistAlgorithm {
public:

    typedef RxnDataType RxnData;

    virtual void calculate(const RxnData& reactionSummary) = 0;
    virtual double getDistance() = 0;

    virtual ~CalcDistAlgorithm() = default;
};