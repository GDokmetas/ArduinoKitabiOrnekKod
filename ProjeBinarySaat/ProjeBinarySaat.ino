
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 RTC;
int datapin = 2;
int clockpin = 3;
int latchpin = 4;
int datapin2 = 8;
int clockpin2 = 9;
int latchpin2= 10;

void setup()
{
  Serial.begin(57600);
  Wire.begin();
  RTC.begin();

  if (! RTC.isrunning()) {
    Serial.println("RTC calismiyor!");
    // Aşağıdaki kod RTC modülü ayarlamayı sağlar. Bir kereliğine çalıştırın eğer ayarlı değilse.
    //RTC.adjust(DateTime(__DATE__, __TIME__));
  }

  pinMode(datapin, OUTPUT);
  pinMode(clockpin, OUTPUT);
  pinMode(latchpin, OUTPUT);
  pinMode(datapin2, OUTPUT);
  pinMode(clockpin2, OUTPUT);
  pinMode(latchpin2, OUTPUT);
}

void loop()
{

  DateTime now = RTC.now();

  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
 
  int mins = now.minute();
  int secs = now.second();
  int hr = now.hour();

  if (hr>12)
  {
    hr = hr-12;
  }


  byte data1 = 0;
  byte data2 = 0;


 
  
  for (int i =0;i<4;i++)
  {
    if (bitRead(hr,i)==1)
    {
      bitWrite(data1,3-i,1);
    }
  }
  
  for (int i =2;i<6;i++)
  {
    if (bitRead(mins,i)==1)
    {
      bitWrite(data1,9-i,1);
    }
  }
 
  for (int i =0;i<2;i++)
  {
    if (bitRead(mins,i)==1)
    {
      bitWrite(data2,1-i,1);
    }
  }
  
  for (int i =2;i<8;i++)
  {
    if (bitRead(secs,i-2)==1)
    {
      bitWrite(data2,9-i,1);
    }
  }
  
  writeByte(data1,1);
  writeByte(data2,2);
  
  delay(1000);

}

void writeByte(byte data, byte set)
{
  int d,c,l;
  if (set==1)
  {
    d = 2;
    c = 3;
    l = 4;
  }
  else if (set==2)
  {
    d = 8;
    c = 9;
    l = 10;
  }
  shiftOut(d, c, MSBFIRST, data);
  
  digitalWrite(l, HIGH);
  digitalWrite(l, LOW);
} 
