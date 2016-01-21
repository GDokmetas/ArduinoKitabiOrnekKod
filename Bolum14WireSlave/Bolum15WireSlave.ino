

// Nick Gammon tarafından yazılmıştır
// February 2012
// Uydu kartın kodu

#include <Wire.h>

const byte MY_ADDRESS = 42; // Bu kartın adresi 42 olacak. 

void setup () 
  {
  Wire.begin (MY_ADDRESS); // 42 olarak I2C protokolünü başlat. 
  for (byte i = 2; i <= 7; i++) // 2'den 7'ye kadar dijital ayakları çıkış yap
    pinMode (i, OUTPUT);
 
  Wire.onReceive (receiveEvent); // Veri Alımda çalışacak fonksiyonu kararlaştır.
  }  

void loop() 
  {
 
  }

// Eğer I2C üzerinden veri alımı olursa bu kesme fonksiyonu çalışır
void receiveEvent (int howMany)
  {
  for (int i = 0; i < howMany; i++)
    {
    byte c = Wire.read (); // Hangi ayağın yakılacağını oku
    // Ledleri sırayla yak
    if (digitalRead (c) == LOW)
      digitalWrite (c, HIGH);
    else
      digitalWrite (c, LOW);
    }  
}  

