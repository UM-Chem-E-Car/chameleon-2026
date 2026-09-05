#include "Core/BaseProgram.h"
#include "Utility/Sensor.h"
#include "Utility/Logger.h"

class DemoProgram : public BaseProgram {
public:
    DemoProgram() : sensor((Color_Sensor())), logger(Logger::instance()){}

    void setup_impl() override {
        delay(50);
        logger.begin();
        sensor.begin();
        logger.log(CONFIG::LOGGING::FIELDS, Logger::LogType::HEADER);
        logger.log("HIHIHIHI");
    }

    void spin_once() override {
        

        sensor.gatherData();
        if (sensor.ready_to_read == false)
            return;
        
        Color_Sensor::Data data = sensor.getReadings();
        const double printarr[] = {
            (double) millis(),
            data.v, 
            data.b, 
            data.c, 
            data.g, 
            data.gy, 
            data.y, 
            data.o, 
            data.r, 
            data.cl, 
            data.nir, 
            CONFIG::LOGGING::PRINT_END_CHAR};
        logger.log_csv(printarr);
    }

private:
    Color_Sensor sensor;
    Logger& logger;
};
