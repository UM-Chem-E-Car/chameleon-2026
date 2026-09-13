#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Utility/Logger.h"
#include "Utility/Sensor.h"
#include "Utility/Filter.h"
#include "Core/BaseProgram.h"
#include "Core/RunVariables.h"

class RunProgram : public BaseProgram {
public:
    RunProgram() : BaseProgram(), sensor(CONFIG::ALGOS::SensorType()), run_data(RunData()){}

    void setup_impl() override {
        //Hardware Setup
        BaseProgram::setup_impl();
        pinMode(RELAY_PIN, OUTPUT);
        pinMode(VALVE_PIN, INPUT);     
        logger.log("Hardware Setup Finished");

        //Software Setup
        logger.begin();
        sensor.begin();
        digitalWrite(RELAY_PIN, LOW);
    }

    void spin_once() override {
        sensor.gatherData();
    }

    bool wait_for_valve_open() override{
        logger.log("Waiting For Valve Open");
        if (analogRead(VALVE_PIN) <= VALVE_PIN_INPUT_LIMIT) {
            return false;
        }
        delay(5);
        if (analogRead(VALVE_PIN) <= VALVE_PIN_INPUT_LIMIT) {
            return false;
        }

        logger.log("Valve Opened");
        logger.log(CONFIG::LOGGING::FIELDS, Logger::LogType::HEADER);
        run_data.valve_open_time = millis();
        return true;
    }

    void collect_initial_data() override {
        rxnOver.setInitialValues(nullptr);
    }


    bool collect_and_check_data() override {
        if (sensor.ready_to_read == false)
            return false;
        
        CONFIG::ALGOS::SensorDataType data = sensor.getReadings();

        // double value = data.r/data.o;
        // double avg_value = valueFilter.newAverage(value);
        // double delta_value = derivative.change(value);
        // double avg_delta_value = derFilter.newAverage(delta_value);

        

        const double printarr[] = {
            millis() - run_data.valve_open_time, 
            data.value,
            // value, 
            // avg_value, 
            // delta_value, 
            // avg_delta_value, 
            CONFIG::LOGGING::PRINT_END_CHAR};
        logger.log_csv(printarr);


        

        return rxnOver.verifyReactionDone(data, run_data.currentTime());
    }

    void calculate_car_run_time() override {
        calcDist.calculate(rxnOver.getReactionData());
        timeRun.calculate(calcDist.getDistance());
        run_data.time_to_run = timeRun.getTimeRun() + run_data.currentTime();
        logger.log("Calculated Distance: " + String(calcDist.getDistance()));
        logger.log("TIMETORUN: " + String(timeRun.getTimeRun()));
    }

    bool move_car() override {
        if (run_data.currentTime() < run_data.time_to_run){
            digitalWrite(RELAY_PIN, HIGH);
            return false;
        }
        else {
            digitalWrite(RELAY_PIN, LOW);
            logger.log("Done Moving Car");
            return true;
        }

    }

protected:
    Logger& logger = Logger::instance();

    CONFIG::ALGOS::SensorType sensor;
    Filter valueFilter;
    Filter derFilter;
    DDx derivative;
    RunData run_data;

    //Algos
    CONFIG::ALGOS::ReactionOverAlgorithm rxnOver;
    CONFIG::ALGOS::CalcDistAlgorithm calcDist;
    CONFIG::ALGOS::TimeRunAlgorithm timeRun;

};