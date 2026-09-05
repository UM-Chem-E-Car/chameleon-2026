#pragma once
#include <Arduino.h>
#include "ConfigVariables.h"

using LogMode = CONFIG::LOGGING::LogMode;

class Logger {
public:
    enum class LogType {
        INFO,
        HEADER,
        DATA,
        ERROR
    };


    void begin(){
        Serial.begin(CONFIG::LOGGING::SERIAL_PORT);
        delay(50);
        log("Logger Started");
    }

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
        if (CONFIG::LOGGING::LOGMODE == LogMode::CSV &&
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
        if (arr == nullptr){
            return;
        }
        Serial.print(String(arr[0], CONFIG::LOGGING::CSV_DECIMALS));
        size_t index = 1;
        while (arr[index] != CONFIG::LOGGING::PRINT_END_CHAR){
            Serial.print(", " + String(arr[index], CONFIG::LOGGING::CSV_DECIMALS));
            index++;
        }
        Serial.println();
    }

private:
    Logger() {}

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
};

