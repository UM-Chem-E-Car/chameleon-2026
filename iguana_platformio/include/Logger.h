#pragma once
#include <Arduino.h>
#include "ConfigVariables.h"

using LogMode = Config::Logging::LogMode;

class Logger {
public:
    enum class LogType {
        INFO,
        HEADER,
        DATA,
        ERROR
    };


    static Logger& instance(){
        static Logger logger;
        return logger;
    }

    template <typename T>
    void log(const T& value) {
        log(value, LogType::INFO);
    }

    template <typename T>
    void log(const T& value, LogType type) {
        if (CONFIG.LOGGING.LOGMODE == LogMode::CSV &&
            type == LogType::INFO)
            return;

        switch (type) {
            case LogType::INFO:
                Serial.print(F("[INFO] "));
                break;

            case LogType::ERROR:
                Serial.print(F("[ERROR] "));
                break;

            default:
                break;
        }

        Serial.println(value);
    }

    void log_csv(const double arr[]){
        size_t index = 0;
        while (arr[index] == CONFIG.LOGGING.PRINT_END_CHAR){
            Serial.print(String(arr[index]) + ", ");
            index++;
        }
        Serial.println();
    }

private:
    Logger() {
        Serial.begin(CONFIG.LOGGING.SERIAL_PORT);
        Serial.println(F("Logger Started"));
    }

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
};

