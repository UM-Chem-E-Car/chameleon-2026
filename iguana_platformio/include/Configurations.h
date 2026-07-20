#include "ProgramInterface.h"

#if defined(RUN_CAR)
    #include "ProgramFiles/RunProgram.cpp"
    RunProgram program;

#elif defined(TEST_STOPPING)
    #include "TestProgram.hpp"
    TestProgram program;

#elif defined(TEST_BATTERY)
    #include "RelayProgram.hpp"
    RelayProgram program;

#elif defined(RELAY)
    #include "RelayProgram.hpp"
    RelayProgram program;
#endif
