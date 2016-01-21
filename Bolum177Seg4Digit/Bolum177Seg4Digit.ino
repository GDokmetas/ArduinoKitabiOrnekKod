

#include "SevSeg.h"

//Objeyi tanımla
SevSeg myDisplay;

//Global değişkenler
unsigned long timer;
int deciSecond = 0;

void setup()
{

  int displayType = COMMON_CATHODE; //Ortak Katot gösterger


  //Basamaklara bağlanan ayakları tanımla
  int digit1 = 2; // Göstergedeki 12. bacak
  int digit2 = 3; // Göstergedeki 9. bacak
  int digit3 = 4; // Göstergedeki 8. bacak
  int digit4 = 5; // Göstergedeki 6. bacak

  //Segmentlere bağlanan ayakları tanımla
  int segA = 6; //Göstergedeki 11. bacak
  int segB = 7; //Göstergedeki 7. bacak
  int segC = 8; //Göstergedeki 4. bacak
  int segD = 9; //Göstergedeki 2. bacak
  int segE = 10; //Göstergedeki 1. bacak
  int segF = 11; //Göstergedeki 10. bacak
  int segG = 12; //Göstergedeki 5. bacak
  int segDP= 13; //Göstergedeki 3. bacak.

  int numberOfDigits = 4; //Basamak sayısını ayarla.

  myDisplay.Begin(displayType, numberOfDigits, digit1, digit2, digit3, digit4, segA, segB, segC, segD, segE, segF, segG, segDP);
  
  myDisplay.SetBrightness(100); //Parlaklık %100

  timer = millis();
}

void loop()
{
  //Numaraları göster
  char tempString[10]; //sprintf için
  sprintf(tempString, "%4d", deciSecond); // dönüşümü yap ve göster
 
  myDisplay.DisplayString(tempString, 3); // Noktanın yeri

 
  //Zamana göre artır 
  if (millis() - timer >= 100)
  {
    timer = millis();
    deciSecond++;
  }

  delay(5);
}

