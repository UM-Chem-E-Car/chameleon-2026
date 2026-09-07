#include "ProgramInterface.h"

#if defined(RUN_CAR)
    #include "ProgramFiles/RunProgram.cpp"
    using ActiveProgram = RunProgram;

#elif defined(TEST_STOPPING)
    #include "ProgramFiles/StoppingTestProgram.cpp"
    using ActiveProgram = StoppingTestProgram;

#elif defined(TEST_BATTERY)
    #include "RelayProgram.hpp"
    using ActiveProgram = RelayProgram;

#elif defined(RELAY)
    #include "ProgramFiles/RelayProgram.cpp"
    using ActiveProgram = RelayProgram;
#elif defined(DEMO)
    #include "ProgramFiles/DemoProgram.cpp"
    using ActiveProgram = DemoProgram;
#endif

ActiveProgram program;