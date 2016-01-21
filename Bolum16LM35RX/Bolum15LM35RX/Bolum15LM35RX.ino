// Bu alıcı için

#include <SPI.h>
#include <nRF24L01p.h>

nRF24L01p alici(7,8);
// CSN 7, CE 8 

void setup(){
  Serial.begin(9600);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  // SPI başlat. Most Significant Bit önde. 
  alici.channel(90);
  alici.RXaddress("Gokhan"); // Aliciya adres ver. 
  alici.init();
  // Alıcı ayarları tamam
}

String sicaklik; // String olarak al. 

void loop(){ 
  while(alici.available()){ // Eğer alıcı mevcutsa 
    
    alici.read(); // oku
    alici.rxPL(sicaklik); // Stringe aktar. 
    /* Modülden gelen veri okundu */
    if(sicaklik.length()>0) // Boş değilse yazdır. 
    {
      Serial.println("SICAKLIK: ");
      Serial.println(sicaklik);
      
      sicaklik=""; // Eski veriyi boşalt. 
      
    }
  }
}
