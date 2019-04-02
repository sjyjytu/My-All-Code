#include <IRremote.h> 
int RECV_PIN = 11;              //定义RECV_PIN变量为11 
IRrecv irrecv(RECV_PIN);       //设置RECV_PIN（也就是11引脚）为红外接收端 
decode_results results;         //定义results变量为红外结果存放位置

int relayState1 = HIGH;
int relayState2 = LOW;
int relayState3 = LOW;
int relayPin1 =  3;
int relayPin2 =  4;
int relayPin3 =  5;


void setup() {
  digitalWrite(relayPin1, relayState1); 
  digitalWrite(relayPin2, relayState2); 
  digitalWrite(relayPin3, relayState3);
  Serial.begin(9600);
  
  irrecv.enableIRIn();
   
}

void loop() {
   
   if (irrecv.decode(&results)) { 
     
     Serial.println(results.value, HEX);
     //一号风扇开关
     if(results.value == 0xFF30CF){
       relayState1 = !relayState1;
       digitalWrite(relayPin1, relayState1);
       Serial.println(relayState1) ;
       Serial.println(relayPin1) ;
     }
     //二号风扇开关
     if(results.value == 0xFF18E7){
       relayState2 = !relayState2;
      // digitalWrite(relayPin2, relayState2); 
     }
     //三号风扇开关
     if(results.value == 0xFF7A85){
       relayState3 = !relayState3;
      // digitalWrite(relayPin3, relayState3); 
     }
      irrecv.resume(); 
   }
   
}
