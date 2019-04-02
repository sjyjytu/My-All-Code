#define x A5       //定义X轴对应的引脚为A5 
#define y A4       //定义y轴对应的引脚为A4
#define sw 2       //定义按键对应的引脚为2
 
void setup() {
  pinMode(sw, INPUT);    //设置为输入模式
  digitalWrite(sw,HIGH); //给sw高电平,非按下状态为1,按下状态为0
  Serial.begin(115200);  //设置波特率
}
 
void loop() {
  Serial.print("x = ");            //串口输出x值
  Serial.print(analogRead(x));
  Serial.print(" | ");
  
  Serial.print("y = ");            //串口输出y值
  Serial.print(analogRead(y));
  Serial.print(" | ");
  
  Serial.print("key = ");          //串口输出sw值
  Serial.println(digitalRead(sw));
  delay(50);                       //延时50毫秒
}
