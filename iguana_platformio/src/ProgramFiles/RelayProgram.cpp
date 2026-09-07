#include "Core/ProgramInterface.h"
#include "Utility/Logger.h"

class RelayProgram : public Program{
public:
    RelayProgram() : logger(Logger::instance()){}
    
    void setup_impl() override {
        pinMode(RELAY_PIN, OUTPUT);
        digitalWrite(RELAY_PIN, HIGH);
        logger.begin();
        logger.log("USING RELAY", Logger::LogType::HEADER);
    }

    void loop_impl() override{
        // digitalWrite(RELAY_PIN, LOW);
        // delay(1000);
        // digitalWrite(RELAY_PIN, HIGH);
        // delay(1000);
    }

private:
    Logger& logger;
};