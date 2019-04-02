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

//c pinlv 

#define WHOLE 1 

#define M 0.5 

#define N 0.25 

#define L 0.1 

#define SIXTEENTH 0.625 

  

int tune[]= 

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

float durt[]= 

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

int length; 

int tonepin=8; 

int ledp=1; 

void setup() 

{ 

  pinMode(tonepin,OUTPUT); 

  pinMode(ledp,OUTPUT); 

  length=sizeof(tune)/sizeof(tune[0]); 

} 

void loop() 

{ 

  for(int x=0;x<length;x++) 

  { 

    tone(tonepin,tune[x]); 

    digitalWrite(ledp, HIGH);  

    delay(450*durt[x]);//与前一代码不同之处，这里将原来的500分为了400和100，分别控制led的开与关，对于蜂鸣器来说依然是500. 

    digitalWrite(ledp, LOW); 

    delay(100*durt[x]); 

    noTone(tonepin); 

      

  } 

  delay(2000); 

}
