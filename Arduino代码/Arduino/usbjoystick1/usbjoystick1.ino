#include <usbhid.h>
#include <hiduniversal.h>
#include <usbhub.h>
#include <Servo.h>
// Satisfy IDE, which only needs to see the include statment in the ino.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

#include "hidjoystickrptparser.h"

//Servo Part
Servo pan;
int angle_pan=0;
Servo tile;
int angle_tile=0;
Servo trigger;
int trigger_switch=15;

Servo wheel;


USB Usb;
USBHub Hub(&Usb);
HIDUniversal Hid(&Usb);
JoystickEvents JoyEvents;
JoystickReportParser Joy(&JoyEvents);
GamePadEventDataPlus myData;
void setup() {
        Serial.begin(115200);
#if !defined(__MIPSEL__)
        while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
        Serial.println("Start");

        if (Usb.Init() == -1)
                Serial.println("OSC did not start.");

        delay(200);

        if (!Hid.SetReportParser(0, &Joy))
                ErrorMessage<uint8_t > (PSTR("SetReportParser"), 1);

        pan.attach(9); 
        pan.write(90);
         
        tile.attach(10);
        tile.write(90);
        
        trigger.attach(11);
        trigger.write(90);

        wheel.attach(12);
        wheel.write(0);
        
        delay(100);

        
        
}

void loop() {
  
      //程序原有部分：
        Usb.Task();
        myData = JoyEvents.MyData;
      //云台程序
//        angle_pan=map(myData.X,0,255,0,180);
//        angle_tile=map(myData.Y,0,255,0,180);
//        Serial.print("angle_pan = ");
//        Serial.print(angle_pan);
//        Serial.print("    angle_tile = ");
//        Serial.println(angle_tile);
//        pan.write(angle_pan);
//        tile.write(angle_tile);
      //扑克牌发射器程序
      //扳机部分
      delay(100);
        trigger_switch=myData.ButtonDown;
        //Serial.print("TS:");Serial.println(trigger_switch);
        
        //JY write:
        //head_switch changes from 0-7 in clockwise; if u don't switch it, it keeps 15.
        //ButtonDown and ButtonUp record the last button that u Down/Up. If u Up the button that u just Down, then Down will be set to zero.
        
        if (trigger_switch==1)
        {
          Serial.println("Fire!");
        }
        Serial.print("Up:");Serial.println(myData.ButtonUp);
        Serial.print("Down:");Serial.println(myData.ButtonDown);
        Serial.print("Head:");Serial.println(myData.head_switch);

        /*Serial.print("X:");Serial.print(myData.X);Serial.print("   ");
        Serial.print("Y:");Serial.print(myData.Y);Serial.print("   ");
        Serial.print("Z1:");Serial.print(myData.Z1);Serial.print("   ");
        Serial.print("Z2:");Serial.print(myData.Z2);Serial.print("   ");
        Serial.print("Rz:");Serial.println(myData.Rz);*/
        

        
        /*if (trigger_switch == 1)
          {
            trigger_switch=myData.ButtonUp;
            trigger.write(120);
            Serial.println("Are You Ready???");
            if (myData.ButtonDown ==1)
            {
              trigger.write(90);
              Serial.println("lease......");
              trigger_switch=0;
            }
            else
            delay(10);
          }
         else
         {
          Serial.println("Nope");
          trigger.write(90);
          trigger_switch=0;
         }*/
          
         

//         if (myData.head_switch ==0)
//          {
//            wheel.write(100);
//            delay(20);
//            Serial.write("Fire!!!!");
//          }
//          else 
//            wheel.write(0);
            
}
