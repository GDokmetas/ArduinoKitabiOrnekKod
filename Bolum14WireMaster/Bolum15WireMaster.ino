
// Nick Gamon Tarafından Yazılmıştır
// February 2012
// Ana kart kodu

#include <Wire.h> // I2C kütüphanesi

const byte SLAVE_ADDRESS = 42; // Uydu adresini ayarla.
const byte LED = 13;

void setup () 
  {
  Wire.begin (); // I2C başlat
  pinMode (LED, OUTPUT);     
  }  

void loop () 
  {
  for (byte x = 2; x <= 7; x++) // 2'den 7'ye kadar çalıştır
    {  
    Wire.beginTransmission (SLAVE_ADDRESS); // Gönderime başla
    Wire.write (x); // X değerini yazdır. 
    if (Wire.endTransmission () == 0)
      digitalWrite (LED, HIGH);  // iletim bitince led yak
    else
      digitalWrite (LED, LOW);  // gönderimde led kapa
      
    delay (200); // biraz bekle. 
    }  // döngü bitimi
  }  
