#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 rtc;

int val;
int tempPin = A0;

const int chipSelect = 10; //SD CS/SS bacağı


void setup() {

analogReference(INTERNAL);

pinMode(2,OUTPUT);

  Serial.println("SD KART YUKLENIYOR");  // KART KONTROL
  if (!SD.begin(chipSelect)) {
  Serial.println("SD KART TANINMADI");
  }
  Serial.println("SD KART TANINDI VE HAZIR");

  if (!SD.exists("datalog.txt"))  // Eğer dosya yoksa yenisini oluştur
  { 
  SD.open("datalog.txt");
  Serial.println("Yeni Datalog.txt Dosyası Acildi"); 
  }
  else 
  { Serial.println("Datalog.txt Bulundu"); } // TXT dosyası Kontrolü

}

void loop() {

val = analogRead(tempPin);
float mv = ( val/1024.0)*1000;
float cel = mv/10;


//SD KAYIT
 digitalWrite(2,HIGH);
 DateTime now = rtc.now();
 File dataFile = SD.open("datalog.txt", FILE_WRITE);
 dataFile.print(now.day(), DEC);
 dataFile.print("/");
 dataFile.print(now.month(), DEC);
 dataFile.print("/");
 dataFile.print(now.year(), DEC); 
  dataFile.print(" ");
  dataFile.print(now.hour(), DEC);
  dataFile.print(":");
  dataFile.print(now.minute(), DEC);
  dataFile.print(":");
  dataFile.print(now.second(), DEC);
  dataFile.print("            ");
  dataFile.println(cel); // Sıcaklık Kaydet
  dataFile.close(); 
 delay(100);
 digitalWrite(2,LOW);
delay(900);
}
