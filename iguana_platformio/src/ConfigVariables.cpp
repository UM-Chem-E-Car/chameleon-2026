#include "ConfigVariables.h"

Config CONFIG{
    {/*DT*/1, /*SLOPE_GRACE_PERIOD*/10000},                                     // RUNTIME
    {/*WINDOW_SIZE*/65},                                                        // FILTER
    {/*VALUE_GAIN*/100},                                                        // SENSOR
    {/*TRIGGER_VALUE*/0.001737, 3},                                                // REACTION
    {/*CAR_A*/0.5657, /*CAR_B*/0.000007, /*CURVE_A*/-0.000375, /*CURVE_B*/37.5},// CAR
    {Config::Logging::CSV, 9600, -293482, "SFLSKDJF"}                                // LOGGING
};
