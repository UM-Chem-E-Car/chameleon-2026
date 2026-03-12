// #include <Arduino.h>
// //#include <SoftwareSerial.h>
// #include "CarInfo.cpp"

// #define PHOTORESISTOR_PIN_IN A0
// #define VALVE_SWITCH_PIN_IN A1 //7
// #define MULTIMETER_PIN_OUT 4
// #define VALVE_PIN_LIMIT 1015
// #define RELAY_PIN_OUT 2

// enum PROGRAM {
//     //Run the Whole program
//     RUN = 0,
//     //Test the Chemical Reaction (No Motor)
//     TEST = 1,
//     //Test the Relay with 1-2 Delay
//     PULSE = 2,
//     //TEST DATA Calibration curve
//     CURVE = 4,
//     //JUST RELAY
//     RELAY = 5
// };

// /*--------------------------------   SELECT TEST PROGRAM   --------------------------------*/

// #define program RUN



// /*----------------------------   VARIABLES YOU WANT TO CHANGE   ------------------------------*/
// #define START_NOW false
// //Average Window size - Smaller: Faster Detection; Bigger: Resistant to Anomalies; Default: 35;
// #define AVERAGE_WINDOW_SIZE 35
// //Slope that will trigger the car movement
// #define SLOPE_LIMIT 50
// //IF TESTING, SECONDS TO TEST
// #define TEST_TIME 40
// //minimum time before car starts to run
// #define SLOPE_GRACE_PERIOD 5
// //Car Head Start
// #define CAR_HEAD_START 15
// //main loop delay
// #define LOOP_DELAY 10

// /*----------------------------   CHEMICAL CALIBRATION CONSTANTS   ------------------------------*/
// #define CAR_A 3.448 //1.67345 //2.13022  // m/s .31
// #define CAR_B -0.0347561//-3.2255

// // EQUATION : distance = ae^{btime}+c
// #define CURVE_A -.33333
// #define CURVE_B 31.66667
// //#define CURVE_C 4.88783

// //bool car_timed = false;
// #define CAR_START_DELAY 0


// bool measureData();
// void dataSetup();
// void dataLoop();
// void moveCar();
// void wait();

// void populateBuffer();

// void printDataSummary();
// void printCarMove();
// // float calcDistance(float time_of_biggest_slope);
// // float calcCarTime(float distance);

// class ReactionInfo{
//     private:
    
//     float valve_open_time;


//     float value_avg_running;
//     float time_of_biggest_slope;
//     float biggest_slope;
    
//     float baseline;

//     int index;

//     //Array of Last Few Values
//     //float average_buffer[AVERAGE_WINDOW_SIZE];
//     float time_buffer[AVERAGE_WINDOW_SIZE];
//     float value_buffer[AVERAGE_WINDOW_SIZE];


//     ReactionInfo() {
//         : valve_open_time(-1) ,value_avg_running(0), time_of_biggest_slope(0), biggest_slope(0), baseline(0), index(0); 
//     }

//     std::string toString() {
//         return "Value average running: " + value_avg_running + ", Time of biggest slope: " 
//         + time_of_biggest_slope + ", Biggest slope: " + biggest_slope + ", Baseline: " + baseline;
//     }

    
//     void populateBuffer(){


//         float time = float(millis()) / 1000;
//         if (valve_open_time == -1) { 
//             valve_open_time = time;
//         }
//         float value = float(analogRead(PHOTORESISTOR_PIN_IN));

//         time_buffer[index] = time;
//         float temp = value_buffer[index];
//         value_buffer[index] = value;

//         value_avg_running += (value - temp) / AVERAGE_WINDOW_SIZE;

//         //float slope = (value_avg_running - average_buffer[index]) / (time - time_buffer[index]);
//         //average_buffer[index] = value_avg_running;
//         index = (index + 1) % AVERAGE_WINDOW_SIZE;
        
//     }


//     float detect() {

//         if (abs(value_avg_running - baseline) > SLOPE_LIMIT && (time - valve_open_time) > SLOPE_GRACE_PERIOD){
//             reaction_done = true;
//             printDataSummary();
//             float time = float(millis()) / 1000;
//             return time - valve_open_time;
//         }

//         return -1;
//     }


//     void printDataSummary(){
//         Serial.println("REACTION DONE, MOVING CAR");    
//         Serial.println("Stopped recording data");
//         float time_from_valve = time_of_biggest_slope - valve_open_time;
//         float distance = calcDistance(time_of_biggest_slope);
//         float time = calcCarTime(distance);  // ms
//         Serial.println("Biggest Slope: " + String(biggest_slope));
//         Serial.println("Time of Biggest Slope: " + String(time_from_valve));
//         Serial.println("Estimated Distance: " + String(distance));
//         Serial.println("Wait Time: " + String(time));
//     }
// };

