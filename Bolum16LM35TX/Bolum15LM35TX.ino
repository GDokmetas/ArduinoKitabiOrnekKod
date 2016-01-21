// Bu verici için 
#include <SPI.h>
#include <nRF24L01p.h>
#include <String.h>

nRF24L01p verici(7,8);
// CSN 7, CE 8

float sicaklik;
static char veri[10];

void setup() {
  Serial.begin(9600);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST); // SPI başlat Most Significant bit önde. 
  
  verici.channel(90);
  verici.TXaddress("Gokhan"); // Vericiye adres ver. 
  verici.init();
 // Verici ayarları tamam 
}
void loop() {
  sicaklik = analogRead(A0);  // Sıcaklık ölçümü yap. 
float mv = ( val/1024.0)*1000;
float cel = mv/10;

  Serial.print("SICAKLIK = "); 
  Serial.print(cel);
  Serial.println(" C");
  // Sıcaklığı ekrana yazdır. 
  
  dtostrf(cel,5, 2, veri);
  // Floatı string verisine çevir. 
  
  verici.txPL(veri); // yolla. 
  boolean gonderimDurum = verici.send(FAST); 

  if(gonderimDurum==true){ // Eğer gönderildiyse. 
        Serial.println("mesaji gonderildi");
  }else{
        Serial.println("mesaji gonderilemedi");
  }
  
  delay(1000); 
}
