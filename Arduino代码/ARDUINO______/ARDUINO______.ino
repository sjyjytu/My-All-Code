#include <IRremote.h> 
#include <Servo.h>
Servo esc; // Creating a servo class with name as esc  
int RECV_PIN=11;
IRrecv irrecv(RECV_PIN);       //设置RECV_PIN（也就是11引脚）为红外接收端 
decode_results results;
void setup()  
{  
esc.attach(9,1000,2000); // Specify the esc signal pin,Here as D9  
delay(2500);
esc.writeMicroseconds(1000); // initialize the signal to 1000  
delay(2000);
Serial.begin(9600);
irrecv.enableIRIn();  
}  
void loop()  
{  
 if (irrecv.decode(&results)) { 
  Serial.println(results.value, HEX);
  if(results.value == 0xFF30CF){
    esc.writeMicroseconds(1000);
  }
  if(results.value == 0xFF18E7){
    esc.writeMicroseconds(1200);
  }
  if(results.value == 0xFF7A85){
    esc.writeMicroseconds(1400);
  }
  if(results.value == 0xFF10EF){
    esc.writeMicroseconds(1600);
  }
  if(results.value == 0xFF38C7){
    esc.writeMicroseconds(1800);
  }
  
  irrecv.resume();
 }  
}  
