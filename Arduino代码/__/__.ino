#define LED  10               //定义LED灯引脚

int i = 0;                   //存储最新数值变数，我们将使用它来从上到下计数

void setup(){

  pinMode(LED,OUTPUT);       //设定LED引脚为输出

}

void loop(){

  

    analogWrite(LED, 255);     //设定LED亮度

    delay(4000);               //延时10ms,因为analogWrite执行瞬间完成，

    analogWrite(LED, 0);                         //速度太快不易察觉
                             

 

}
