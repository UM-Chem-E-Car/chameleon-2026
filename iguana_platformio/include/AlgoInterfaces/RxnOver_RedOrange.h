#pragma once

#include "AlgoInterfaces/BaseAlgos/ReactionOverAlgorithm.h"
#include "Utility/Sensor.h"
#include "Utility/Filter.h"

namespace CONSTS{
    constexpr int TRIGGER_COUNT = 3;
    //0.001737
    constexpr double TRIGGER_VALUE = 0.01737;
}

struct TimeAndRegimeData {
    double time_reaction_end;
    double reaction_end_value;

    TimeAndRegimeData() : time_reaction_end(-1), reaction_end_value(-1){};
    bool operator==(const TimeAndRegimeData& rhs) const {
        if (time_reaction_end != rhs.time_reaction_end)
            return false;
        if (reaction_end_value != rhs.reaction_end_value)
            return false;
        return true;
    }
};

class RxnOver_RedOrange : public ReactionOverAlgorithm<Color_Sensor::Data, TimeAndRegimeData>
{
public:

    typedef Color_Sensor::Data SensorData;
    typedef TimeAndRegimeData RxnData;

    RxnOver_RedOrange();

    bool verifyReactionDone(const SensorData& data, const double& time) override;
    const RxnData& getReactionData() override;

private:
    Filter valueFilter;
    Filter derFilter;
    DDx derivative;

    int triggers_hit;

    RxnData STORED_REACTION_DATA;
};