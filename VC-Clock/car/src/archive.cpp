// /*----------------------------------------------------------------------------------

// CHEM-E-CAR Battery Car
// Main Contributors:
// Arya Rukadikar <arukad@umich.edu>
// Jayden Elliot <jaydene@umich.edu>

// Seth Hansen <sethhan@umich.edu>


// TODO for improvement:
// Separate Measuredata into two separate functions
// Create HPP file to store variables and function bloat
// Create new files for Constants and CarState
// ------------------------------------------------------------------------------------
// */

// #include "CarInfo.cpp"
// #include "meain.hpp"




// /*--------------------------------   DONT TOUCH THESE   --------------------------------*/

// //Array of Last Few Values
// float average_buffer[AVERAGE_WINDOW_SIZE];  

// //Array of Last Few Times
// float time_buffer[AVERAGE_WINDOW_SIZE];


// //float value_avg_running;
// float value_avg_running;
// float time_of_biggest_slope;
// float biggest_slope;
// float valve_open_time;
// float car_start_time;
// int index;

// float time_temp_use;

// bool valve_opened;
// bool reaction_done;

// float carRunTime = 0;



// bool measureData();
// void dataSetup();
// void dataLoop();
// void moveCar();
// void wait();
// void printDataSummary();
// void printCarMove();
// float calcDistance(float time_of_biggest_slope);
// float calcCarTime(float distance);

// //REQUIRES: NONE
// //EFFECTS: Initializes CarInfo and Arduino Variables
// //RETURNS: CarInfo, Init Variables, 
// void setup() {
//     //INIT
//     Serial.begin(9600);
//     setPins();
//     pinMode(VALVE_SWITCH_PIN_IN, INPUT);
//     pinMode(RELAY_PIN_OUT, OUTPUT);
//     pinMode(MULTIMETER_PIN_OUT, OUTPUT);
//     digitalWrite(RELAY_PIN_OUT, LOW);
//     digitalWrite(MULTIMETER_PIN_OUT, HIGH);
//     delay(10);
//     Serial.println("Starting recording data");
// }

// //EFFECT: CALLS FUNCTIONS SHOULD NOT MODIFY VARIABLES
// //REQUIRES: mode, 
// //RETURNS: nothing
// void loop() {
//     string mode = "RUN";

//     switch(mode) {
//         case "RUN":
//             populateBuffer();

//             detect() == -1 ? return :
//             (detect) -> 
//             runCar()
//         case "TEST":
//             populateBuffer();
//         case "PULSE":
//             return;
//         case "CURVE":
//             return;
//         case "RELAY":
//             Serial.println("USING RELAY");
//             digitalWrite(RELAY_PIN_OUT, HIGH);
//     }



//     /*
//     SWITCH
//         CASE RUN
//             populatebuffer()
//             detect()
//             runcar()
//         CASE TEST
//             populatebuffer()
//         CASE PULSE
//             runcar.pulse()
//         CASE CURVE
//             runcar(constant)
//         CASE RELAY
//             runcar.relay()

//     Gameplan Pseudocode:

//     Data Recording part
//         case RUN: populateBuffer();
//         case TEST: populateBuffer();
//         case PULSE: Do Nothing
//         case CURVE: Do Nothing
//         case RELAY: RunRelayCode(); BREAK;

//     Detection Part
//         case RUN: provide Data Summary
//         case TEST: provide Data Summary; BREAK
//         case PULSE: Do NOTHING
//         case CURVE: DO NOTHING
//         case RELAY: -----

//     Car Moving Part
//         case Run: Do the Car calculations; RUN CAR
//         case TEST: -------
//         case PULSE: Do pulse code;
//         case CURVE: RUN CAR with preset value
//         case RELAY: ------

//     Car ending stuff
//         stuff
    
    
    
//     */





//     //make a program that establishes baseline


//     //TODO
//     /*
//     1) Make a new CarInfo variable called bufferPopulated
//     2) If Buffer not populated, keep adding data values to the buffer using method populateBuffer
//     3) Take Average Readings 
//     4) After Buffer is full, set baseline to average, set bufferPopulated to True and 
//         close out of the function when called afterward
//     */

//     if (program == RUN)
//         populateBuffer();


//     if (program == RELAY){
        
//     }

//     delay(LOOP_DELAY);

//     if (!valve_opened){
//         wait();
//     }

//     if (program == RUN && START_NOW == true){
//         digitalWrite(RELAY_PIN_OUT, HIGH);
//         carRunTime = millis();
//     }
    

//     if (!reaction_done){
//         measureData();
//     }

//     if (program == RUN || program == CURVE)
//         moveCar();
    
    
// }

// //TODO: RENAME
// //EFFECT: gets two readings from the arduino. If both are positive, print valve opened
// //and set the according CarInfo variables
// //RETURNS: true if Valve Switch PIN IN is > Valve Pin Limit
// bool waitForValveOpen(){

//     if (analogRead(VALVE_SWITCH_PIN_IN) < VALVE_PIN_LIMIT) {
//         return false;
//     } 
//     delay(5);
//     if (analogRead(VALVE_SWITCH_PIN_IN) < VALVE_PIN_LIMIT) {
//         return false;
//     }
   
//     valve_opened = true;
//     valve_open_time = float(millis()) / 1000;
//     Serial.println("Valve Opened");
//     return true; 

// }

// populateBuffer()


// //TODO: Rename, Make Data Struct
// //EFFECTS: Updates Buffer
// //TAKES: Get some reaction variables
// //Returns: average running
// //MODIFIES: The buffer lists
// void calcBuffer() {

//     float time = float(millis()) / 1000;
//     float value = float(analogRead(PHOTORESISTOR_PIN_IN));
//     value_avg_running += (value - average_buffer[index]) / AVERAGE_WINDOW_SIZE;
//     float slope = (value_avg_running - average_buffer[index]) / (time - time_buffer[index]);
//     average_buffer[index] = value_avg_running;
//     time_buffer[index] = time;
//     index = (index + 1) % AVERAGE_WINDOW_SIZE;
//     //Return the average running
// }

// //Prolly dont need this, make a toString function in DATUM
// void printData(/*GET A DATA STRUCT*/) {
//     Serial.println(String(time - valve_open_time) + ", " + String(value) + ", " + String(slope));
// }

// //EFFECTS: Using the program and the Reaction Variables, return the decision to start or not start car
// bool decision(){

//     if (program == TEST && time - valve_open_time >= TEST_TIME){
//         reaction_done = true;
//     }

//     if (program == CURVE){
//         reaction_done = true;
//         time_of_biggest_slope = TEST_TIME + valve_open_time;
//         return true;
//     }
    
//     //OLD CODE
    
//     if (abs(slope) > biggest_slope && time - valve_open_time > SLOPE_GRACE_PERIOD) {
//         biggest_slope = abs(slope);
//         time_of_biggest_slope = time;
//     }
    
//     if (program == TEST && time - valve_open_time >= TEST_TIME){

//         reaction_done = true;
//         printDataSummary();

//     }

//     if (program == CURVE){
//         reaction_done = true;
//         time_of_biggest_slope = TEST_TIME + valve_open_time;
//         printDataSummary();
//         Serial.println("REACTION DONE, MOVING CAR");
//         printCarMove();
//     }

//     if (program == RUN && abs(value - baseline) > SLOPE_LIMIT && (time - valve_open_time) > SLOPE_GRACE_PERIOD){
//         reaction_done = true;
//         time_temp_use = time - valve_open_time;
//         printDataSummary();
//         Serial.println("REACTION DONE, MOVING CAR");
//         printCarMove();

//     }

//     return false;
// }

// //TODO: RENAME
// bool measureData() {

//     //Decisions of the CAR
//     if (abs(slope) > biggest_slope && time - valve_open_time > SLOPE_GRACE_PERIOD) {
//         biggest_slope = abs(slope);
//         time_of_biggest_slope = time;
//     }


//     if (program == TEST && time - valve_open_time >= TEST_TIME){

//         reaction_done = true;
//         printDataSummary();

//     }

//     if (program == CURVE){
//         reaction_done = true;
//         time_of_biggest_slope = TEST_TIME + valve_open_time;
//         printDataSummary();
//         Serial.println("REACTION DONE, MOVING CAR");
//         printCarMove();
//     }

//     if (program == RUN && abs(value - baseline) > SLOPE_LIMIT && (time - valve_open_time) > SLOPE_GRACE_PERIOD){
//         reaction_done = true;
//         time_temp_use = time - valve_open_time;
//         printDataSummary();
//         Serial.println("REACTION DONE, MOVING CAR");
//         printCarMove();

//     }

//     return false;
// }

// void printDataSummary(){
//     Serial.println("Stopped recording data");
//     float time_from_valve = time_of_biggest_slope - valve_open_time;
//     float distance = calcDistance(time_of_biggest_slope);
//     float time = calcCarTime(distance);  // ms
//     Serial.println("Biggest Slope: " + String(biggest_slope));
//     Serial.println("Time of Biggest Slope: " + String(time_from_valve));
//     Serial.println("Estimated Distance: " + String(distance));
//     Serial.println("Wait Time: " + String(time));
// }


// void runCar(float timeOfActivation){
    
// }

// //COMPLETLY OVERHAUL
// void printCarMove(){
//     float time_from_valve = time_temp_use - valve_open_time;


//     float distance = calcDistance(time_temp_use);
//     float calcTime = calcCarTime(distance);
//     Serial.println("Time From Valve: " + String(time_temp_use) + ", ESTIMATED DISTANCE " + String(distance) + ", Time for Car Run " + String(calcTime));
// }

// void moveCar() {

//     float distance = calcDistance(time_temp_use);



//     float calcTime = calcCarTime(distance);


//     //float curr_time = float(millis()) / 1000;
//     float time_left = calcTime;// - (curr_time - valve_open_time) + CAR_START_DELAY;
//     Serial.println("Time Left: " + String(time_left));
//     digitalWrite(RELAY_PIN_OUT, HIGH);
//     delay(time_left * 1000);
//     digitalWrite(RELAY_PIN_OUT, LOW);
//     Serial.println("PROGRAM END");
//     delay(100);
//     exit(0);


// }

// float calcDistance(float time_of_biggest_slope){ //42.5
//     //float calcDistance = CURVE_A * pow(EULER, CURVE_B * time_of_biggest_slope) + CURVE_C;
//     float calcdistance = CURVE_A * (time_of_biggest_slope - valve_open_time - carRunTime/1000) + CURVE_B;
//     return calcdistance;
// }

// float calcCarTime(float distance){
//     return distance * CAR_A + CAR_B;
// }

// // void dataSetup() {
// //     Serial.begin(9600);
// //     pinMode(VALVE_SWITCH_PIN_IN, INPUT);
// //     Serial.println("Starting recording data");
// // }

// // void dataLoop() {
// //     if (digitalRead(VALVE_SWITCH_PIN_IN) != HIGH && valve_open_time == 0) {
// //         return;
// //     }

// //     if (valve_open_time == 0) {
// //         valve_open_time = millis();
// //         Serial.println("Valve Opened");
// //     }

// //     long time = float(millis() - valve_open_time);
// //     int value = analogRead(PHOTORESISTOR_PIN_IN);
// //     Serial.println(String(time) + ", " + String(value));
// //     delay(10);
// // }