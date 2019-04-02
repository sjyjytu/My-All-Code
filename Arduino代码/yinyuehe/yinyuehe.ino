#include <stdio.h>
#include <DS1302.h>
#include <Servo.h>
//**********************************定义旋律
#define B0 -1 
#define XB1 248 
#define XB2 278 
#define XB3 294 
#define XB4 330 
#define XB5 371 
#define XB6 416 
#define XB7 467 
#define B1 495 
#define B2 556 
#define B3 624 
#define B4 661 
#define B5 742 
#define B6 833 
#define B7 935 
#define SB1 990 
#define SB2 1112 
#define SB3 1178 
#define SB4 1322 
#define SB5 1484 
#define SB6 1665 
#define SB7 1869 
//****************************************************
#define NTD0 -1
#define NTD1 294
#define NTD2 330
#define NTD3 350
#define NTD4 393
#define NTD5 441
#define NTD6 495
#define NTD7 556

#define NTDL1 147
#define NTDL2 165
#define NTDL3 175
#define NTDL4 196
#define NTDL5 221
#define NTDL6 248
#define NTDL7 278

#define NTDH1 589
#define NTDH2 661
#define NTDH3 700
#define NTDH4 786
#define NTDH5 882
#define NTDH6 990
#define NTDH7 112
//************************************************
//列出全部D调的频率
#define WHOLE 1
#define HALF 0.5
#define QUARTER 0.25
#define EIGHTH 0.25
#define SIXTEENTH 0.625
//*************************************************


//欢乐颂
int tune0[]=                 //根据简谱列出各频率
{
  NTD3,NTD3,NTD4,NTD5,
  NTD5,NTD4,NTD3,NTD2,
  NTD1,NTD1,NTD2,NTD3,
  NTD3,NTD2,NTD2,
  NTD3,NTD3,NTD4,NTD5,
  NTD5,NTD4,NTD3,NTD2,
  NTD1,NTD1,NTD2,NTD3,
  NTD2,NTD1,NTD1,
  NTD2,NTD2,NTD3,NTD1,
  NTD2,NTD3,NTD4,NTD3,NTD1,
  NTD2,NTD3,NTD4,NTD3,NTD2,
  NTD1,NTD2,NTDL5,NTD0,
  NTD3,NTD3,NTD4,NTD5,
  NTD5,NTD4,NTD3,NTD4,NTD2,
  NTD1,NTD1,NTD2,NTD3,
  NTD2,NTD1,NTD1
};
float durt0[]=                   //根据简谱列出各节拍
{
  1,1,1,1,
  1,1,1,1,
  1,1,1,1,
  1+0.5,0.5,1+1,
  1,1,1,1,
  1,1,1,1,
  1,1,1,1,
  1+0.5,0.5,1+1,
  1,1,1,1,
  1,0.5,0.5,1,1,
  1,0.5,0.5,1,1,
  1,1,1,1,
  1,1,1,1,
  1,1,1,0.5,0.5,
  1,1,1,1,
  1+0.5,0.5,1+1,
};
//****************************************************
//体面
#define WHOLE 1 

#define M 0.5 

#define N 0.25 

#define L 0.1 

#define SIXTEENTH 0.625 

int tune1[]= 

{ 

  B0,B0,B1,B2,
  B3,B1,B2,B3,B0,B1,B5,B5,
  B5,B5,B3,B2,B1,
  B1,XB6,XB7,B1,XB5,B3,B3,
  B3,B3,XB7,XB7,XB6,XB5,
  B1,XB6,XB7,B1,B0,B5,B6,B5,
  B5,B5,B3,B1,B0,B2,B3,XB6,
  XB6,B3,B3,B3,B3,B2,B1,B3,
  B3,B1,B2,
  B3,B1,B2,B3,B0,B1,B5,B5,
  B5,B5,B3,B2,B1,
  B1,XB6,XB7,B1,XB5,B3,B3,
  B3,B2,B3,B5,B1,
  B1,XB6,XB7,B1,B0,XB5,B6,B5,
  B5,B7,SB1,B0,B3,B3,B1,
  XB6,B3,XB6,B0,XB7,B1,
  XB7,B1,B5,B4,
  B3,B6,SB1,
  

}; 
float durt1[]= 

{ 
  1,1,1,1,
  M,M,M,M,M,M,M,M+L,
  1,M,1,M,1,
  M,M,M,1,M,M,M+L,
  1,M,1,M,M+L,M,
  M,M,M,M,M,M,M,M+L,
  M,M,M,M,M,M,M,M+L,
  M,M,M,M,M,M,M,M+L,
  2,1,1,
  M,M,M,M,M,M,M,M+L,
  1,M,1,M,1,
  M,M,M,1,M,M,M+L,
  1,M,1,M,1,
  M,M,M,M,M,M,M,M+L,
  M,1,M,M,M,0.75,N,
  1,M,M,M,M,1,
  3,1,
  3,1,
  3,M,M,
}; 
//********定义引脚*********
int length0;
int length1; 
int tonepin=8; 

int kaiguan =2;

const int kCePin   = 5;  // Chip Enable

const int kIoPin   = 6;  // Input/Output

const int kSclkPin = 7;  // Serial Clock
//*******定义变量和函数***************//
int kaiguan_state =0;
int duo_ji = 1;

Servo myservo;

DS1302 rtc(kCePin, kIoPin, kSclkPin);

//*******************************************定义函数******************************//
void gettime(){
  Time t = rtc.time();
  if (t.hr==14&&t.min==50){
      playmusic(tune1,durt1,length1);
  }
}


void playmusic(int _tune[],float _durt[],int _length)
{
  for(int x=0;x<_length;x++) 
  { 

    tone(tonepin,_tune[x]); 
    myservo.write(179*duo_ji);
    delay(550*_durt[x]);

    noTone(tonepin);
    duo_ji = duo_ji*(-1); 

   } 
}

void _kaiguan(){
  kaiguan_state=digitalRead(kaiguan);
  if (kaiguan_state==1)
  {
    delay(4000);
    if (kaiguan_state==1)   playmusic(tune0,durt0,length0);
    else playmusic(tune1,durt1,length1);
  }
}

void setup() 

{ 
  rtc.writeProtect(false);
  rtc.halt(false);
  pinMode(tonepin,OUTPUT); 
  pinMode(kaiguan,INPUT);
  myservo.attach(9);
  length0=sizeof(tune0)/sizeof(tune0[0]); 
  length1=sizeof(tune1)/sizeof(tune1[0]);
} 


void loop() 

{    
  gettime();
  _kaiguan();
  
}
