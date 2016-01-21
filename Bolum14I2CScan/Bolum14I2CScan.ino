// I2C Scanner
// Nick Gammon Tarafından Yazılmıştır
// 

#include <Wire.h>

void setup() {
  Serial.begin (115200);


  Serial.println ();
  Serial.println ("I2C Tarayici Baslatiliyor ...");
  byte count = 0;
  
  Wire.begin();
  for (byte i = 8; i < 120; i++)
  {
    Wire.beginTransmission (i);
    if (Wire.endTransmission () == 0)
      {
      Serial.print ("Bulunan Adres: ");
      Serial.print (i, DEC);
      Serial.print (" (0x");
      Serial.print (i, HEX);
      Serial.println (")");
      count++;
      delay (1);  
      } 
  } 
  Serial.println ("Bitti.");
  Serial.print ("Bulunan Aygit Sayisi: ");
  Serial.print (count, DEC);
}  

void loop() {}
