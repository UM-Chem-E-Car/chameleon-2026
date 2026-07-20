#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Sensor.h"
#include "Filter.h"
#include "BaseProgram.h"
#include "RunVariables.h"

class RunProgram : public BaseProgram {
public:
    RunProgram() : BaseProgram(Logger::instance()), sensor(Color_Sensor()), valueFilter(Filter()), derFilter(Filter()), derivative(DDx()), run_data(RunData()){}

    void software_setup_impl() override {
        digitalWrite(RELAY_PIN, LOW);
    }

    void background_tasks() override {
        sensor.gatherData();
    }

    bool collect_and_check_data() override {
        if (sensor.ready_to_read == false)
            return false;
        
        Color_Sensor::Data data = sensor.getReadings();

        double value = data.r/data.o;
        double avg_value = valueFilter.newAverage(value);
        double delta_value = derivative.change(value);
        double avg_delta_value = derFilter.newAverage(delta_value);

        

        const double printarr[] = {
            millis() - run_data.valve_open_time, 
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
            value, 
            avg_value, 
            delta_value, 
            avg_delta_value, 
            CONFIG.LOGGING.PRINT_END_CHAR};
        logger.log_csv(printarr);

        if (CONFIG.RUNTIME.SLOPE_GRACE_PERIOD < run_data.currentTime()){
            return false;
        }
        
        if (abs(avg_delta_value) < CONFIG.REACTION.TRIGGER_VALUE){
            run_data.triggers_hit++;
            if (run_data.triggers_hit >= CONFIG.REACTION.TRIGGER_COUNT){
                run_data.time_reaction_end = run_data.currentTime();
                run_data.reaction_value = value;
                return true;
            }
        }
        return false;
    }

    void calculate_car_run_time() override {
        float estimated_distance = CONFIG.CAR.CURVE_A * run_data.time_reaction_end + CONFIG.CAR.CURVE_B;
        float calculated_time = (estimated_distance / CONFIG.CAR.CAR_A + CONFIG.CAR.CAR_B)*1000;

        run_data.time_to_run = calculated_time + run_data.currentTime();
        logger.log("Calculated Distance: " + String(estimated_distance));
        logger.log("TIMETORUN: " + String(calculated_time));
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

private:
    Color_Sensor sensor;
    Filter valueFilter;
    Filter derFilter;
    DDx derivative;
    RunData run_data;
};