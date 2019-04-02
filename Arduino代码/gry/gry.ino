int kaiguan =7;
int carRed=8;
int carYellow = 9;
int carGreen = 10;
int pedRed = 11;
int pedGreen = 12;
unsigned long changeTime;
int crossTime = 5000;
void setup() 
{
        pinMode(kaiguan,INPUT);
        pinMode(carRed,OUTPUT);
        pinMode(carYellow,OUTPUT);
        pinMode(carGreen,OUTPUT);
        pinMode(pedRed,OUTPUT);
        pinMode(pedGreen,OUTPUT);
        digitalWrite(carGreen,HIGH);
        digitalWrite(pedRed,HIGH);
}
void loop()
{
  int state = digitalRead(kaiguan);          
  //检测按钮是否被按下，并且是否距上次按下后有5秒的等待时间           
  if(state == HIGH && (millis() - changeTime)> 5000)
  {          
    //调用变灯函数          
    changeLights(); 
    }
}

void changeLights() 
{           
  digitalWrite(carGreen, LOW);       //汽车绿灯灭           
  digitalWrite(carYellow, HIGH);      //汽车黄灯亮           
  delay(2000);                               //等待2秒             
  digitalWrite(carYellow, LOW);      //汽车黄灯灭           
  digitalWrite(carRed, HIGH);         //汽车红灯亮           
  delay(1000);                              //为安全考虑等待1秒             
  digitalWrite(pedRed, LOW);        //行人红灯灭           
  digitalWrite(pedGreen, HIGH);    //行人绿灯亮
  delay(crossTime);                      //等待一个通过时间             //闪烁行人灯绿灯，提示可过马路时间快到           
  for (int x=0; x<10; x++) 
  {                     
  digitalWrite(pedGreen, HIGH);                     
  delay(250);                     
  digitalWrite(pedGreen, LOW);                     
  delay(250);}        
  digitalWrite(pedRed, HIGH);         //行人红灯亮           
  delay(500);
  digitalWrite(carRed, LOW);          //汽车红灯灭           
  digitalWrite(carYellow, HIGH);      //汽车黄灯亮            
  delay(1000);           
  digitalWrite(carYellow, LOW);      //汽车黄灯灭           
  digitalWrite(carGreen, HIGH);      //汽车绿灯亮
  changeTime = millis();                //记录自上一次灯变化的时间           
   //返回到主函数循环中 
   }
