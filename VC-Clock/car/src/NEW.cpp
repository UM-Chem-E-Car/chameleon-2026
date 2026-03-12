// /* This example will read all channels from the AS7341 and print out reported values */

// #include <Adafruit_AS7341.h>

// Adafruit_AS7341 as7341;


// void setup() {
//   Serial.begin(9600);

//   // Wait for communication with the host computer serial monitor
//   while (!Serial) {
//     delay(1);
//   }
//   if (!as7341.begin()){
//       Serial.println("Could not find AS7341");
//       while (1) { delay(10); }
//     }
    
//     as7341.setATIME(100);
//     as7341.setASTEP(999);
//     as7341.setGain(AS7341_GAIN_256X);
//     Serial.println("HELLO");
// }

// void loop() {
//   // Read all channels at the same time and store in as7341 object
//   if (!as7341.readAllChannels()){
//     Serial.println("Error reading all channels!");
//     return;
//   }

//   // red = SCL
//   // blk = SDA
//   // ylw = 5V
//   // wht = GND

//   // Print out the stored values for each channel
 
//   /*
//   Serial.print("F1 415nm : ");
//   Serial.println(as7341.getChannel(AS7341_CHANNEL_415nm_F1));
//   Serial.print("F2 445nm : ");
//   Serial.println(as7341.getChannel(AS7341_CHANNEL_445nm_F2));
//   Serial.print("F3 480nm : ");
//   Serial.println(as7341.getChannel(AS7341_CHANNEL_480nm_F3));
//   Serial.print("F4 515nm : ");
//   Serial.println(as7341.getChannel(AS7341_CHANNEL_515nm_F4));
//   Serial.print("F5 555nm : ");
//   Serial.println(as7341.getChannel(AS7341_CHANNEL_555nm_F5));
//   Serial.print("F6 590nm : ");
//   Serial.println(as7341.getChannel(AS7341_CHANNEL_590nm_F6));
//   Serial.print("F7 630nm : ");
//   Serial.println(as7341.getChannel(AS7341_CHANNEL_630nm_F7));
//   Serial.print("F8 680nm : ");
//   Serial.println(as7341.getChannel(AS7341_CHANNEL_680nm_F8));

//   Serial.print("Clear    : ");
//   Serial.println(as7341.getChannel(AS7341_CHANNEL_CLEAR));

//   Serial.print("Near IR  : ");
//   Serial.println(as7341.getChannel(AS7341_CHANNEL_NIR));

//   Serial.println("");
//   */
  
//   double b = 16;

//   Serial.print(millis() / 1000.0); Serial.print(",");
//   Serial.print((double) as7341.getChannel(AS7341_CHANNEL_415nm_F1) / pow(2,b) * 100);  Serial.print(",");
//   Serial.print((double) as7341.getChannel(AS7341_CHANNEL_445nm_F2) / pow(2,b) * 100);  Serial.print(",");
//   Serial.print((double) as7341.getChannel(AS7341_CHANNEL_480nm_F3) / pow(2,b) * 100);  Serial.print(",");
//   Serial.print((double) as7341.getChannel(AS7341_CHANNEL_515nm_F4) / pow(2,b) * 100);  Serial.print(",");
//   Serial.print((double) as7341.getChannel(AS7341_CHANNEL_555nm_F5) / pow(2,b) * 100);  Serial.print(",");
//   Serial.print((double) as7341.getChannel(AS7341_CHANNEL_590nm_F6) / pow(2,b) * 100);  Serial.print(",");
//   Serial.print((double) as7341.getChannel(AS7341_CHANNEL_630nm_F7) / pow(2,b) * 100);  Serial.print(",");
//   Serial.print((double) as7341.getChannel(AS7341_CHANNEL_680nm_F8) / pow(2,b) * 100);  Serial.print(",");
//   Serial.print((double) as7341.getChannel(AS7341_CHANNEL_CLEAR) / pow(2,b) * 100);  Serial.print(",");
//   Serial.println((double) as7341.getChannel(AS7341_CHANNEL_NIR) / pow(2,b) * 100);
  
// }