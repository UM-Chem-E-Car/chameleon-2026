#pragma once

//DEFINE YOUR ALGOS IN GLOBAL NAMESPACE
#include "AlgoInterfaces/RxnOver_Photoresistor.h"
#include "AlgoInterfaces/CalcDist_Interpolate.h"
#include "AlgoInterfaces/TimeRun_Linear.h"

#include "Utility/Sensor.h"

#define VALVE_PIN A0
#define RELAY_PIN 8
#define VALVE_PIN_INPUT_LIMIT 100

namespace CONFIG {

    namespace RUNTIME {
        constexpr int DT = 1;
        constexpr unsigned long SLOPE_GRACE_PERIOD = 10000UL;
        
        enum ExitBehavior {
            DELAY, LOOP, EXIT
        };
        constexpr ExitBehavior EXIT_BEHAVIOR = LOOP;
    };

    namespace FILTER {
        constexpr int WINDOW_SIZE = 65;
    };

    namespace SENSOR {
        constexpr int ATIME = 25;
        constexpr int ASTEP = 99;
        constexpr double VALUE_GAIN = 10000;

    };
    
    namespace ALGOS {
        using SensorType = Light_Sensor;

        using SensorDataType = Light_Sensor::Data;
        using ReactionOverAlgorithm = RxnOver_Photoresistor;
        
        using ReactionSummaryDataType = ValueDiff;
        using CalcDistAlgorithm = CalcDist_Interpolate;

        using TimeRunAlgorithm = TimeRun_Linear;

    }



    namespace LOGGING {
        enum LogMode{
            MAIN,
            CSV
        };
        
        constexpr LogMode LOGMODE = CSV;
        constexpr int SERIAL_PORT = 9600;

        constexpr int CSV_DECIMALS = 5;

        constexpr double PRINT_END_CHAR = -293482;
        constexpr const char* FIELDS = "Time, Value";//, Value, Average Value, Delta, Average Delta";
    };

    namespace TESTING {
        constexpr unsigned long STOPPING_END_TEST_TIME = 60000UL;
        constexpr unsigned long BATTERY_SIMULATED_END_TIME = 25000UL;
        constexpr int BATTERY_SIMULATED_VALUE = 0;
    }

};
