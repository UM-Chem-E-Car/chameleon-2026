#include "AlgoInterfaces/RxnOver_RedOrange.h"
#include "Utility/Logger.h"

RxnOver_RedOrange::RxnOver_RedOrange() : valueFilter(Filter()), derFilter(Filter()), derivative(DDx()), triggers_hit(0), STORED_REACTION_DATA(RxnData()){} 

bool RxnOver_RedOrange::verifyReactionDone(const RxnOver_RedOrange::SensorData& sensorData, const double& time) {
    double value = sensorData.r/sensorData.o;
    double avg_value = valueFilter.newAverage(value);
    double delta_value = derivative.change(value);
    double avg_delta_value = derFilter.newAverage(delta_value);

    // const double printarr[] = {
    //     time, 
    //     value,
    //     avg_value,
    //     delta_value,
    //     avg_delta_value,
    //     CONFIG::LOGGING::PRINT_END_CHAR};

    // Logger::instance().log_csv(printarr);

    if (abs(avg_delta_value) < CONSTS::TRIGGER_VALUE){
        triggers_hit++;
        Logger::instance().log("TRIGGER HITS: " + String(triggers_hit));
        if (triggers_hit >= CONSTS::TRIGGER_COUNT){
            STORED_REACTION_DATA.time_reaction_end = time;
            STORED_REACTION_DATA.reaction_end_value = value;
            return true;
        }
    }
    return false;
}

const RxnOver_RedOrange::RxnData& RxnOver_RedOrange::getReactionData(){
    if (STORED_REACTION_DATA == TimeAndRegimeData()){Logger::instance().log("INVALID REACTION DATA", Logger::LogType::ERROR);}
    return STORED_REACTION_DATA;
}