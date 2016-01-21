// Nick Gamon Tarafından Yazılmıstır
// Nisan 2011
// 


#include <SPI.h>

void setup (void)
{
  Serial.begin (115200);
  Serial.println ();
  
  digitalWrite(SS, HIGH);  // SS bacağının HIGH olduğundan emin ol

  // SCK,MOSI,SS Bacaklarını çıkış yap. 
  // SCK MOSI Low SS HIGH YAP
  // SPI BAŞLAT
  SPI.begin ();

  // SPI 4Mhz'de çalıştır. 
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  
}  

byte transferAndWait (const byte what) // SPI transfer fonksiyonu
{
  byte a = SPI.transfer (what);
  delayMicroseconds (20);
  return a;
} // 

void loop (void)
{

  byte a, b, c, d; // 4 adet byte tanımla 
  
  // SS aktif et, uydu ile bağlantıyı kur. 
  digitalWrite(SS, LOW);    

  transferAndWait ('a');  // toplama komutu
  transferAndWait (10); 
  a = transferAndWait (17);
  b = transferAndWait (33);
  c = transferAndWait (42);
  d = transferAndWait (0);

  // SS kapat. 
  digitalWrite(SS, HIGH);
  // Degerleri ekranda goster
  Serial.println ("Toplama Sonuclari:");
  Serial.println (a, DEC);
  Serial.println (b, DEC);
  Serial.println (c, DEC);
  Serial.println (d, DEC);
  
  // SS aktif et 
  digitalWrite(SS, LOW);   
 
  transferAndWait ('s');  // çıkarma komutu
  transferAndWait (10);
  a = transferAndWait (17);
  b = transferAndWait (33);
  c = transferAndWait (42);
  d = transferAndWait (0);

  // SS KAPAT
  digitalWrite(SS, HIGH);

  Serial.println ("Cikarma Sonuclari:"); // Çıkarma sonuçları
  Serial.println (a, DEC);
  Serial.println (b, DEC);
  Serial.println (c, DEC);
  Serial.println (d, DEC);
  
  delay (1000);  // 1 saniye bekle 
}  // loop bitir. 

/*
 * Bu program öncelikle SPI yazdırma fonksiyonu tanımlar. Bu fonksiyon bir byte değeri gönderir ve gelen değeri a baytına aktararak 
 * a değişkenini değer olarak döndürür. 
 */
