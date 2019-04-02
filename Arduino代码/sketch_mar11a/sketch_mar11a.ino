#include "MeOrion.h" [/align]#include <Wire.h>
#include <SoftwareSerial.h>
  
MePotentiometer myPotentiometer(PORT_6);
  
void setup()
{
    Serial.begin(9600);
}
  
void loop()
{
    Serial.print("value=");
    Serial.println(myPotentiometer.read() );
    delay(100);
}
