
#include <IRremote.h> 
#include <Servo.h> 
Servo myservo;
int val;
int potpin = 0;  //旋钮
int relayPin =  2;         // 继电器连接到数字2 
int relayState = 0;    //继电器状态
int RECV_PIN = 11;       //红外         
IRrecv irrecv(RECV_PIN); 
decode_results results;
void setup(){  
  myservo.attach(9);
  Serial.begin(9600);  
  irrecv.enableIRIn();   
  
  pinMode(relayPin, OUTPUT);// 设置LED为输出状态
  digitalWrite(relayPin, relayState);
}
void loop() 
{  
  while(1)
  {
  val = analogRead(potpin); 
  val = map(val, 0, 1023, 0, 179);  //通过map函数进行数值转换 
  myservo.write(val); 
  delay(15);
  if (irrecv.decode(&results)) 
{         
  Serial.println(results.value, HEX);
  if(results.value == 0xAE7EE0)//5
  {         
    relayState = !relayState;   
    digitalWrite(relayPin, relayState);  
    delay(1000);  
    digitalWrite(relayPin,0) ;             
    }
   else if (results.value ==0xFF30CF) //1
   {
    myservo.write(45);         
   }
   else if (results.value ==0xFF18E7) //2
   {
    myservo.write(90);         
   }
   else if (results.value ==0xFF7A85) //3
   {
    myservo.write(135);         
   }
   else if (results.value ==0xFF10EF) //4
   {
    myservo.write(180);
   }
   else 
   {
         Serial.println('bad');    
   }
   }
    irrecv.resume();   
    } 
  
 }

