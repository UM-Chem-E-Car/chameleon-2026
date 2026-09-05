#include "ProgramInterface.h"

#if defined(RUN_CAR)
    #include "ProgramFiles/RunProgram.cpp"
    RunProgram program;

#elif defined(TEST_STOPPING)
    #include "ProgramFiles/StoppingTestProgram.cpp"
    StoppingTestProgram program;

#elif defined(TEST_BATTERY)
    #include "RelayProgram.hpp"
    RelayProgram program;

#elif defined(RELAY)
    #include "RelayProgram.hpp"
    RelayProgram program;
#elif defined(DEMO)
    #include "ProgramFiles/DemoProgram.cpp"
    DemoProgram program;
#endif
