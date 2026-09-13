#pragma once


#include "Utility/Sensor.h"
#include "Utility/Filter.h"
#include "AlgoInterfaces/CustomDataType/TimeData.h"


class RxnOver_Photoresistor
{
public:


    RxnOver_Photoresistor() : valueFilter(Filter(50)), derFilter(Filter()), derivative(DDx()), STORED_REACTION_DATA(){}

    void setInitialValues(void* values){

    }

    bool verifyReactionDone(const Light_Sensor::Data& data, const double& time){
        double value = data.value;

        if (time < 50){
            return false;
        }
        valueFilter.newAverage(value);

        static double bavg = 0;
        static double bno = 0;
        if (time > 500 && time < 1000){
            bavg += value;
            bno++;
            return false;
        }

        static double eavg = 0;
        static double eno = 0;
        if (time > 59000 && time < 60000){
            eavg += value;
            eno++;
            return false;
        }

        if (time > 60000){
            STORED_REACTION_DATA.diff = bavg/bno - eavg/eno;
            return true;
        }

        
        return false;
    }

    const ValueDiff& getReactionData() {
        return STORED_REACTION_DATA;
    };

private:

    Filter valueFilter;
    Filter derFilter;
    DDx derivative;


    ValueDiff STORED_REACTION_DATA;
};