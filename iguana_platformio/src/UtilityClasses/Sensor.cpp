#include "Sensor.h"
#include "ConfigVariables.h"
#include "Logger.h"

Color_Sensor::Color_Sensor(int ATIME_in, int ASTEP_in) : Color_Sensor(ATIME_in, ASTEP_in, CONFIG.SENSOR.VALUE_GAIN){};

Color_Sensor::Color_Sensor(int ATIME_in, int ASTEP_in, double gain_in): ready_to_read(false), ATIME(ATIME_in), ASTEP(ASTEP_in), sensor(), gain(gain_in), readings() {}

Color_Sensor::Color_Sensor() : Color_Sensor(CONFIG.SENSOR.ATIME, CONFIG.SENSOR.ASTEP, CONFIG.SENSOR.VALUE_GAIN){}


void Color_Sensor::gatherData(){

    if(!sensor.getIsDataReady())
        return;

    Data ret{};

    if(!sensor.readAllChannels()){
        Logger::instance().log("Sensor read failed");
        return;
    }

    ret.v  = sensor.getChannel(AS7341_CHANNEL_415nm_F1) / 65536.0 * gain;
    ret.b  = sensor.getChannel(AS7341_CHANNEL_445nm_F2) / 65536.0 * gain;
    ret.c  = sensor.getChannel(AS7341_CHANNEL_480nm_F3) / 65536.0 * gain;
    ret.g  = sensor.getChannel(AS7341_CHANNEL_515nm_F4) / 65536.0 * gain;
    ret.gy = sensor.getChannel(AS7341_CHANNEL_555nm_F5) / 65536.0 * gain;
    ret.y  = sensor.getChannel(AS7341_CHANNEL_590nm_F6) / 65536.0 * gain;
    ret.o  = sensor.getChannel(AS7341_CHANNEL_630nm_F7) / 65536.0 * gain;
    ret.r  = sensor.getChannel(AS7341_CHANNEL_680nm_F8) / 65536.0 * gain;
    ret.cl = sensor.getChannel(AS7341_CHANNEL_CLEAR) / 65536.0 * gain;
    ret.nir= sensor.getChannel(AS7341_CHANNEL_NIR) / 65536.0 * gain;

    if(ret != readings){
        readings = ret;
        ready_to_read = true;
        return;
    }
}

const Color_Sensor::Data& Color_Sensor::getReadings() {
    if (!ready_to_read){
        Logger::instance().log("NOT READY");
        return invalid;
    }
    ready_to_read = false;
    return readings;
}



double Color_Sensor::getIntegrationTimeInMiliseconds() {
    return (ATIME+1)*(ASTEP+1)*2.78/1000;
}




