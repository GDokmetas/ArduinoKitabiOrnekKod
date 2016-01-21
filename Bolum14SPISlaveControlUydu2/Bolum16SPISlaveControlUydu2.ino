// Rick Gamon Tarafından yazılmıştır
// Nisan 2011 


volatile byte command = 0;

void setup (void)
{

  // MISOyu çıkış ayarla
  pinMode(MISO, OUTPUT);

  // SPI uydu modunda aç
  SPCR |= _BV(SPE);

  // Kesmeleri aç
  SPCR |= _BV(SPIE);

}  


// SPI Kesmesi Fonksiyonu
ISR (SPI_STC_vect)
{
  byte c = SPDR;
 
  switch (command)
  {
  // Komut yokken
  case 0:
    command = c;
    SPDR = 0;
    break;
    
  // Eğer a gelirse topla ve değeri döndür. 
  case 'a':
    SPDR = c + 15;  // 15 ekle
    break;
    
  // Eğer s gelirse çıkart ve değeri döndür. 
  case 's':
    SPDR = c - 8;  // 8 Çıkart. 
    break;

  } 

}  // Kesme fonksiyonunu bitir. 

void loop (void)
{
  
  // SPI kapalıysa komutu temizle. 
  if (digitalRead (SS) == HIGH)
    command = 0;
}  
