#include "main.hpp"

// ------- Objects -------
ReactionOut reaction;
// Filter valueFilter(WINDOW_SIZE);
// Filter derFilter(WINDOW_SIZE);
// DDx derivative(DT);
// Adafruit_AS7341 Color_Sensor;
Car car;
// -----------------------

void setup(){
    Serial.begin(9600);
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(VALVE_PIN_IN, INPUT);     

    Serial.println("Program Started");
    delay(5000); // testing speed

}

// loop for testing speed
void loop() {
    if (car.time_car_move == -1){
        car.time_car_move = millis();
        digitalWrite(RELAY_PIN, HIGH);
    }
}
