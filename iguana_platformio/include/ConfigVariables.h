#pragma once


#define VALVE_PIN A2
#define RELAY_PIN 2
#define VALVE_PIN_INPUT_LIMIT 50

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
        
    }

    namespace REACTION {
        constexpr double TRIGGER_VALUE = 0.001737;
        constexpr int TRIGGER_COUNT = 3;
    };

    namespace CAR {
        constexpr double CAR_A = 0.5657;
        constexpr double CAR_B = 0.000007;
        constexpr double CURVE_A = -0.000375;
        constexpr double CURVE_B = 37.5;
    };

    namespace LOGGING {
        enum LogMode{
            MAIN,
            CSV
        };
        
        constexpr LogMode LOGMODE = MAIN;
        constexpr int SERIAL_PORT = 9600;

        constexpr int CSV_DECIMALS = 5;

        constexpr double PRINT_END_CHAR = -293482;
        constexpr const char* FIELDS = "Time, v, b, c, g, gy, y, o, r, cl, nir, Value, Average Value, Delta, Average Delta";
    };

    namespace TESTING {
        constexpr unsigned long STOPPING_END_TEST_TIME = 10000UL;
        constexpr unsigned long BATTERY_SIMULATED_END_TIME = 25000UL;
        constexpr int BATTERY_SIMULATED_VALUE = 0;
    }

};
