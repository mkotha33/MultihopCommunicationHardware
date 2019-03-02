#include<SoftwareSerial.h>

SoftwareSerial bt(2,3);
int c;
void setup() {
  //pinMode(ledPin, OUTPUT);
  //digitalWrite(ledPin, LOW);
  Serial.begin(9600); // Default communication rate of the Bluetooth module
  bt.begin(9600);
}

void loop() {
 
 // Controlling the LED
 
if(Serial.available() > 0){ // Checks whether data is comming from the serial port
    c = Serial.read();
    Serial.write(c);
    bt.write(c);
 }

 
//if(bt.available()){
  //Serial.println("available");
  
//}
 
}
