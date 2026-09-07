#pragma once

template <typename SensorDataType, typename RxnDataType>
class ReactionOverAlgorithm {
public:

    typedef SensorDataType SensorData;
    typedef RxnDataType RxnData;

    virtual bool verifyReactionDone(const SensorData& data, const double& time) = 0;
    virtual const RxnData& getReactionData() = 0;

    virtual ~ReactionOverAlgorithm() = default;
};