#pragma once

template<
    typename RxnOverAlgorithmType,
    typename CalcDistAlgorithmType,
    typename TimeRunAlgorithmType
>
struct AlgorithmSet {

    typedef RxnOverAlgorithmType RxnOver;
    typedef CalcDistAlgorithmType CalcDist;
    typedef TimeRunAlgorithmType TimeRun;

};