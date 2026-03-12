// #include <Arduino.h>
// #include <SoftwareSerial.h>
// #include <Filter.cpp>
// #include <Adafruit_AS7341.h>

// // red = SCL
// // blk = SDA
// // ylw = 5V
// // wht = GND

// //TODO
// /*
// Define 2 varibles for color sensor input pins
// In measuredate function, store the wavelength
// movecar function

// */  
// // #define PHOTORESISTOR_PIN_IN A0
// #define VALVE_SWITCH_PIN_IN A1
// #define VALVE_PIN_LIMIT 600
// #define RELAY_PIN_OUT 3

// #define COLOR_SENSOR_SDA 20
// #define COLOR_SENSOR_SCL 21

// Adafruit_AS7341 Color_Sensor;


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
// //Average Window size - Smaller: Faster Detection; Bigger: Resistant to Anomalies; Default: 35;
// #define AVERAGE_WINDOW_SIZE 10
// //Slope that will trigger the car movement
// #define SLOPE_LIMIT .002
// //IF TESTING, SECONDS TO TEST
// #define TEST_TIME 50
// //minimum time before car starts to run
// #define SLOPE_GRACE_PERIOD 5

// /*----------------------------   CHEMICAL CALIBRATION CONSTANTS   ------------------------------*/
// #define CAR_A 1.9 //1.67345 //2.13022  // m/s
// #define CAR_B -0.0347561//-3.2255

// // EQUATION : distance = ae^{btime}+c

// #define CURVE_A -0.25
// #define CURVE_B 35
// //#define CURVE_C 4.88783

// //bool car_timed = false;
// #define CAR_START_DELAY 0

// #define dt 10


// /*--------------------------------   DONT TOUCH THESE   --------------------------------*/

// //Array of Last Few Values
// float average_buffer[AVERAGE_WINDOW_SIZE];

// //Array of Last Few Times
// float time_buffer[AVERAGE_WINDOW_SIZE];

// Filter avg_value_filter(AVERAGE_WINDOW_SIZE);

// Filter der_value_filter(AVERAGE_WINDOW_SIZE);


// DDx deriv = DDx(dt);

// //float value_avg_running;
// float value_avg_running;
// float time_of_biggest_slope;
// float biggest_slope;
// float valve_open_time;
// float car_start_time;
// int index;

// bool valve_opened;
// bool reaction_done;

// float baseline;

// float der_avg_running;



// bool measureData();
// void data_setup();
// void data_loop();
// void moveCar();
// void wait();
// void printDataSummary();
// void printCarMove();
// float calcDistance(float time_of_biggest_slope);
// float calcCarTime(float distance);
// float calc_weighted_wavelength(float data[]);




// void setup() {
    
//     //     //INIT
//     //     value_avg_running = 0;
//     //     time_of_biggest_slope = 0;
//     //     biggest_slope = 0;
//     //     valve_open_time = 0;
//     //     car_start_time = 0;
//     //     valve_opened = false;
//     //     reaction_done = false;
//     //     index = 0;
//     //     ///HRER
    
//     Serial.begin(9600);
//     while (!Serial) {
//         delay(1);
//     }
//     // red = SCL
//     // blk = SDA
//     // ylw = 5V
//     // wht = GND
//     Serial.println("sfsdf");
//     if (!Color_Sensor.begin()){
//         while (1) {
//             delay(10);
//         }
//     }
//     // if (!began){
//     //     Serial.println("Could not find AS7341");
//     //     while (!began) {
//     //         began = Color_Sensor.begin();
//     //         delay(10); 
//     //         Serial.println("Could not find AS7341");
//     //     }
//     // }
//     Serial.println("world");
//     Color_Sensor.setATIME(25);
//     Color_Sensor.setASTEP(100);
//     // Color_Sensor.setASTEP((dt/2.78e-6 - 1)*1000);
//     Color_Sensor.setGain(AS7341_GAIN_256X);
//     pinMode(VALVE_SWITCH_PIN_IN, INPUT);
//     pinMode(RELAY_PIN_OUT, OUTPUT);
//     digitalWrite(RELAY_PIN_OUT, LOW);
//     delay(10);

//     Serial.println("Started Recording Data");


// }

// void loop() {
//     digitalWrite(RELAY_PIN_OUT, LOW); // test
//     if (!Color_Sensor.readAllChannels()){
//         Serial.println("NOT FUCKING NFNFNNFN");
//         return;
//     }
//     Serial.println("NOT FUCKING PRINGINTs");
//     digitalWrite(RELAY_PIN_OUT, LOW); // test

//     double b = 16;
    
//     // Serial.print(millis() / 1000.0); Serial.print(",");
//     // Serial.print((double) Color_Sensor.getChannel(AS7341_CHANNEL_415nm_F1) / pow(2,b) * 100);  Serial.print(",");
//     // Serial.print((double) Color_Sensor.getChannel(AS7341_CHANNEL_445nm_F2) / pow(2,b) * 100);  Serial.print(",");
//     // Serial.print((double) Color_Sensor.getChannel(AS7341_CHANNEL_480nm_F3) / pow(2,b) * 100);  Serial.print(",");
//     // Serial.print((double) Color_Sensor.getChannel(AS7341_CHANNEL_515nm_F4) / pow(2,b) * 100);  Serial.print(",");
//     // Serial.print((double) Color_Sensor.getChannel(AS7341_CHANNEL_555nm_F5) / pow(2,b) * 100);  Serial.print(",");
//     // Serial.print((double) Color_Sensor.getChannel(AS7341_CHANNEL_590nm_F6) / pow(2,b) * 100);  Serial.print(",");
//     // Serial.print((double) Color_Sensor.getChannel(AS7341_CHANNEL_630nm_F7) / pow(2,b) * 100);  Serial.print(",");
//     // Serial.print((double) Color_Sensor.getChannel(AS7341_CHANNEL_680nm_F8) / pow(2,b) * 100);  Serial.print(",");
//     // Serial.print((double) Color_Sensor.getChannel(AS7341_CHANNEL_CLEAR) / pow(2,b) * 100);  Serial.print(",");
//     // Serial.println((double) Color_Sensor.getChannel(AS7341_CHANNEL_NIR) / pow(2,b) * 100);

//     // float data[8];
//     // data[0] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_415nm_F1) / pow(2,b) * 100;
//     // data[1] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_445nm_F2) / pow(2,b) * 100;
//     // data[2] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_480nm_F3) / pow(2,b) * 100;
//     // data[3] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_515nm_F4) / pow(2,b) * 100;
//     // data[4] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_555nm_F5) / pow(2,b) * 100;
//     // data[5] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_590nm_F6) / pow(2,b) * 100;
//     // data[6] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_630nm_F7) / pow(2,b) * 100;
//     // data[7] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_680nm_F8) / pow(2,b) * 100;

//     //Serial.println(calc_weighted_wavelength(data));


//     if (program == RELAY){
//         Serial.println("USING RELAY");
//         digitalWrite(RELAY_PIN_OUT, HIGH);
//         return;
//     }

//     delay(dt);
//     if (!valve_opened){
//         wait();
//         return;
//     }

//     Serial.println(reaction_done);
//     if (!reaction_done){
//         measureData();
//         return;
//     }

//     if (program == RUN || program == CURVE)
//         moveCar();
    
    
// }
// void readData(float * data) {
//     if (!Color_Sensor.readAllChannels()){
//         Serial.println("NOT FUCKING NFNFNNFN");
//         return;
//     }
//     int b = 16;
//     data[0] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_415nm_F1) / pow(2,b) * 100;
//     data[1] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_445nm_F2) / pow(2,b) * 100;
//     data[2] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_480nm_F3) / pow(2,b) * 100;
//     data[3] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_515nm_F4) / pow(2,b) * 100;
//     data[4] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_555nm_F5) / pow(2,b) * 100;
//     data[5] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_590nm_F6) / pow(2,b) * 100;
//     data[6] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_630nm_F7) / pow(2,b) * 100;
//     data[7] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_680nm_F8) / pow(2,b) * 100;
//     data[8] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_CLEAR) / pow(2,b) * 100;
//     data[9] = (double) Color_Sensor.getChannel(AS7341_CHANNEL_NIR) / pow(2,b) * 100;
// }

// float calc_weighted_wavelength(float data[]) {
//      float waves_sum = 0.0;
//      float total_intensity = 0.0;
//      for (int i = 0 ; i < 8; i++) {
//         waves_sum += (i+1) * data[i];
//         total_intensity += data[i];
//      }
//      return waves_sum/total_intensity;
//  }

// void wait(){


//     Serial.println(analogRead(VALVE_SWITCH_PIN_IN));
//     if (analogRead(VALVE_SWITCH_PIN_IN) < VALVE_PIN_LIMIT) {
//         return;
//     } 
//     delay(5);
//     if (analogRead(VALVE_SWITCH_PIN_IN) < VALVE_PIN_LIMIT) {
//         return;
//     }
//     valve_opened = true;
//     valve_open_time = float(millis()) / 1000;
//     Serial.println("Valve Opened");
    
// }


// bool measureData() {

//     float time = float(millis()) / 1000;

//     // float value = calc_weighted_wavelength(data);
//     float channels[10];
//     readData((float*) &channels);
//     double red_value = channels[7]; // AS7341_CHANNEL_680nm_F8)
   
//     value_avg_running = avg_value_filter.average(red_value);
//     ///Serial.println("Time: " + String(time) + ", Rem Time: " + String(time_buffer[index]) + ", Value Avg: " + String(value_avg_running) + ", Rem Value Avg " + String(value_avg_buffer[index]));
//     float slope = deriv.change(red_value);
//     der_avg_running = der_value_filter.average(slope);
//     Serial.println(String(time - valve_open_time) + ", " + String(red_value, 5) + ", " + String(slope, 5) + ", " + String(der_avg_running, 5));
//     time_buffer[index] = time;
    


//     if (program == TEST && time - valve_open_time >= TEST_TIME){

//         reaction_done = true;
//         printDataSummary();

//     }

//     if (program == CURVE){
//         reaction_done = true;
//         time_of_biggest_slope = TEST_TIME;
//         printDataSummary();
//         Serial.println("REACTION DONE, MOVING CAR");
//         printCarMove();
//     }

//     // if (program == RUN && abs(biggest_slope) > SLOPE_LIMIT && (time - valve_open_time) > SLOPE_GRACE_PERIOD){
//     //     reaction_done = true;
//     //     printDataSummary();
//     //     Serial.println("REACTION DONE, MOVING CAR");
//     //     printCarMove();

//     // }

//     if (program == RUN && abs(der_avg_running) < SLOPE_LIMIT && (time - valve_open_time) > SLOPE_GRACE_PERIOD){
//         reaction_done = true;
//         time_of_biggest_slope = time-valve_open_time;
//         printDataSummary();
//         Serial.println("REACTION DONE, MOVING CAR");
//         printCarMove();

//     }

//     // if (car_start_time == 0) {
//     //     if (float(millis()) / 1000 - valve_open_time < CAR_START_DELAY) {
//     //         return;
//     //     }
//     //     car_start_time = float(millis()) / 1000;
//     //     digitalWrite(RELAY_PIN_OUT, HIGH);
//     // }



//     return false;
//     // if (abs(slope) > slope_limit && slope < biggest_slope) {
//     //     Serial.println("Stopped recording data");
//     //     moveCar(time_of_biggest_slope);
//     // }
// }

// void printDataSummary(){
//     Serial.println("Stopped recording data");
//     float time_from_valve = time_of_biggest_slope - valve_open_time;
//     float distance = calcDistance(time_of_biggest_slope);
//     float time = calcCarTime(distance);  // ms
//     Serial.println("Slope: " + String(der_avg_running, 8));
//     Serial.println("Time of Biggest Slope: " + String(time_from_valve));
//     Serial.println("Estimated Distance: " + String(distance));
//     Serial.println("Wait Time: " + String(time));
// }

// void printCarMove(){
//     float time_from_valve = time_of_biggest_slope - valve_open_time;


//     float distance = calcDistance(time_of_biggest_slope);
//     float calcTime = calcCarTime(distance);
//     Serial.println("Time From Valve: " + String(time_from_valve) + ", ESTIMATED DISTANCE " + String(distance) + ", Time for Car Run " + String(calcTime));
// }

// void moveCar() {

//     float distance = calcDistance(time_of_biggest_slope);


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

// float calcDistance(float time_of_biggest_slope){
//     //float calcDistance = CURVE_A * pow(EULER, CURVE_B * time_of_biggest_slope) + CURVE_C;

    
//     float calcdistance = CURVE_A * (time_of_biggest_slope - valve_open_time) + CURVE_B;
//     return calcdistance;
// }

// float calcCarTime(float distance){
//     return distance * CAR_A + CAR_B;
// }

// void data_setup() {
//     Serial.begin(9600);
//     pinMode(VALVE_SWITCH_PIN_IN, INPUT);
//     Serial.println("Starting recording data");
// }

// void data_loop() {
//     if (digitalRead(VALVE_SWITCH_PIN_IN) != HIGH && valve_open_time == 0) {
//         return;
//     }

//     if (valve_open_time == 0) {
//         valve_open_time = millis();
//         Serial.println("Valve Opened");
//     }

//     long time = float(millis() - valve_open_time);
//     int value = 1; // analogRead(PHOTORESISTOR_PIN_IN);
//     Serial.println(String(time) + ", " + String(value));
//     delay(10);
// }