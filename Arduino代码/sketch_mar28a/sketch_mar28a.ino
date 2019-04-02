#include <DS1302.h>
#include <Wire.h>
DS1302 rtc(0, 1, 2); // RST, DAT, CLK
void getdatetime()
{
  //Serial.println(rtc.getDateStr(FORMAT_LONG, FORMAT_LITTLEENDIAN, '/'));
  //Serial.print(rtc.getDOWStr());
  Serial.print("    ");
  //Serial.println(rtc.getTimeStr());
}
void setup()
{
  Serial.begin(9600);
  // 设置时间后, 需要注释掉设置时间的代码,并重新烧录一次. 以免掉电重新执行setup中的时间设置函数.
  rtc.halt(false);
  rtc.writeProtect(false);
  rtc.setDOW(SATURDAY);
  rtc.setTime(17, 22, 30);
  rtc.setDate(31, 12, 2016);
  rtc.writeProtect(true);
}
void loop()
{
  getdatetime();
  delay(1000);
}
