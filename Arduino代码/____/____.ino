#include <Servo.h>
Servo esc;

void setup()  
{  
esc.attach(9,1000,2000); // Specify the esc signal pin,Here as D9  
delay(2500);
esc.writeMicroseconds(1000); // initialize the signal to 1000  
delay(2000);
Serial.begin(9600);

} 
void loop()
{
  Serial.print("hello");
  delay(2000);
  esc.writeMicroseconds(1200);
  delay(20000);
}

