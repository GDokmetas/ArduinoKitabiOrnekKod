
#include <OneWire.h> 
#include <SPI.h>
#include "Ucglib.h"

int DS18S20_Pin = 2; 
OneWire ds(DS18S20_Pin);  
Ucglib_ILI9341_18x240x320_SWSPI ucg(/*sclk=*/ 4, /*data=*/ 3, /*cd=*/ 6 , /*cs=*/ 7, /*reset=*/ 5);  

byte deger[275]; // Değerlerin yazılacağı byte dizisi
int dizisirasi=0;
int xsabiti=25;
int ysabiti=170; // Grafik için sabitler. 
void setup(void) {
  Serial.begin(9600); 
  ucg.begin(UCG_FONT_MODE_TRANSPARENT); // Yazılar şeffaf olacak. 
  ucg.clearScreen(); // Ekranı temizle
  delay(1000);
}

void loop(void) {
  ucg.setRotate90(); // Ekranı 90c çevir. 
  ucg.setFont(ucg_font_7x14_tf); // kullanılacak fonk
  ucg.setPrintPos(10,15); // İmleci X Y kordinatına götür
  ucg.setColor(255, 255, 255); // Rengi R 255 G 255 B 255 ayarla (Beyaz)
  ucg.print("Dijital Termometre ve Kayit Tutucu"); // Yazdır
  ucg.setColor(70, 174, 236); // Rengi mavimsi bir renk yap
  ucg.drawFrame(5, 20, 310, 216); // çerçeve çiz. x y başlangıç , xy bitiş
  float temperature = getTemp();  // Sıcaklık fonksiyonunu al. 
  ucg.setFont(ucg_font_fub42_tf); // Font ayarla. 
  ucg.setPrintPos(150,70); // İmleci götür 
  ucg.print(temperature); // Sıcaklığı yaz
  deger[dizisirasi]=temperature*2;
  /*****/
  Serial.print("Sicaklik: "); // Seri ekrana da yazdır. 
  Serial.println(temperature);
  /*****/
  for (int d=90;d<=190;d+=10) // Noktalı alanı yazdır. 
  {
  for (int i=25;i<=300;i+=10)
  {
  ucg.setColor( 0, 100, 100, 100);
  ucg.drawPixel( i,d );
  }
  }
  int sicaklikyazdir=40;
  for(int i=90;i<=190;i+=10) // Sıcaklığı yazdır. 
{
  ucg.setColor(255, 0, 0);
  ucg.setFont(ucg_font_orgv01_hn);
  ucg.setPrintPos(8,i);
  ucg.print(sicaklikyazdir);
  sicaklikyazdir-=5;
}
int saatyazdir=1;
for (int i=85;i<=300;i+=60) // Zaman etiketlerini yazdır. 
{
  ucg.setColor(0, 0, 255);
  ucg.setFont(ucg_font_orgv01_hn);
  ucg.setPrintPos(i,210);
  ucg.print(saatyazdir);
  saatyazdir++;
}
for (int i=0;i<=dizisirasi;i++)
{

int d=deger[i];
d=ysabiti-d;
ucg.setColor( 0, 255, 127, 30);
ucg.drawPixel( i+xsabiti,d );
}
dizisirasi++;
if (dizisirasi>=275)
dizisirasi=0;
  delay(5000);
  ucg.clearScreen();
 

}





/* SICAKLIK SENSÖRÜ FONKSİYONU. */ 
float getTemp(){
  
  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
      ds.reset_search();
      return -1000;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return -1000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device is not recognized");
      return -1000;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); // start conversion, with parasite power on at the end

  byte present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE); // Read Scratchpad

  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
  }

  ds.reset_search();

  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;

  return TemperatureSum;

}

