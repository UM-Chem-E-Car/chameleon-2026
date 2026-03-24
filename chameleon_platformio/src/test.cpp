#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Filter.cpp>
#include <Adafruit_AS7341.h>
#include <Sensor.cpp>


Color_Sensor sensor;
void setup(){
    Serial.begin(9600);
    Serial.println("Program Started");
    sensor.init(229, 599);

}

void loop(){

    Serial.println("Hello");

    if(sensor.read()){
        // read() already prints timestamp
    }

}