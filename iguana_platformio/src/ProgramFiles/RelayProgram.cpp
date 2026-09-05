#include "Core/BaseProgram.h"

class RelayProgram : public BaseProgram{
    void spin_once() override {
        digitalWrite(RELAY_PIN, HIGH);
        logger.log("USING RELAY");
    }

    bool wait_for_valve_open(){
        return false;
    }
};