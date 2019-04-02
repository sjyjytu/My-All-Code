#include <IRremote.h>        //调用IRremote.h库 
int RECV_PIN = 11;            //定义RECV_PIN变量为11 
IRrecv irrecv(RECV_PIN);    //设置RECV_PIN（即11引脚）为红外接收端 
decode_results results;      //定义results变量为红外结果存放位置 
int currentNumber = 0;      //该变量用于存放当前数字
long codes[12]=                 //该数组用来存放红外遥控器发出的红外码 
{           
0xFF30CF,0xFF6897,      
0xFF18E7,0xFF7A85,       
0xFF10EF,0xFF38C7,
0XFF5AA5,0XFF42BD,
0XFF4AB5,0XFF52AD,      
0xFFA857,0xFFE01F,     // + ,-
};
int number[10][8] =            //该数组用来存放数码管显示的数字 
{  {0,0,0,1,0,0,0,1},//0  
{0,1,1,1,1,1,0,1},//1  
{0,0,1,0,0,0,1,1},//2  
{0,0,1,0,1,0,0,1},//3  
{0,1,0,0,1,1,0,1},//4  
{1,0,0,0,1,0,0,1},//5  
{1,0,0,0,0,0,0,1},//6  
{0,0,1,1,1,1,0,1},//7  
{0,0,0,0,0,0,0,1},//8  
{0,0,0,0,1,1,0,1} //9 
};
void numberShow(int i) 
{     //该函数用来让数码管显示数字  
  for(int pin = 2; pin <= 9 ; pin++)
  {     digitalWrite(pin, number[i][pin - 2]);  } 
}
void setup()
{  
  Serial.begin(9600);           //设置波特率为9600  
  irrecv.enableIRIn();           //启动红外解码    
  for(int pin = 2 ; pin <= 9 ; pin++)
  {   //设置数字引脚2~9为输出模式      
    pinMode(pin, OUTPUT);      
    digitalWrite(pin, HIGH);  } 
}
void loop() 
{  //判断是否接收到解码数据,把接收到的数据存储在变量results中  
  if (irrecv.decode(&results)) 
  {      
    for(int i = 0; i <= 11; i++)
    {         //判断是否接收到0~9按键的红外码         
      if(results.value == codes[i]&& i <= 9)
      {               
        numberShow(i);         //在数码管上对应显示0~9               
        currentNumber = i;   //把当前显示的值赋给变量currentNumber               
        Serial.println(i,results.value);               
        break;                       
        }                  // 判断是否接收到递减的红外码，并且当前值不为0         
       else if(results.value == codes[10]&& currentNumber != 0)
        {               
          currentNumber--;                      //当前值递减               
          numberShow(currentNumber);  //数码管显示递减后的值               
          Serial.println(currentNumber);   //串口输出递减后的值               
          break;                 
          }                  //判断是否接收到递增的红外码，并且当前值不为9         
        else if(results.value == codes[11]&& currentNumber != 9)
          {               
            currentNumber++;                    //当前值递增               
            numberShow(currentNumber);  //数码管显示递增后的值               
            Serial.println(currentNumber);   //串口输出递增后的值               
            break;                     
            }    
    }
         Serial.println(results.value, HEX);            //串口监视器查看红外码
           
         irrecv.resume();                                     //等待接收下一个信号  
      }
    }
  



