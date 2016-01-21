#include <SPI.h>

char buf [100]; // tampon 100
volatile byte pos;
volatile boolean process_it;

void setup (void)
{
  Serial.begin (115200);

  // Mıso çıkış ayarla
  pinMode(MISO, OUTPUT);

  // SPI'ı slave modunda aç 
  SPCR |= _BV(SPE);

  // Kesme için hazırlan
  pos = 0;   // tampon boş
  process_it = false;

  // SPI kesmeyi aç. 
  SPI.attachInterrupt();
}


// SPI kesmesi spı veri akışında çalıştırılacak fonksiyonu belirler.
ISR (SPI_STC_vect)
{
  byte c = SPDR;  // SPI data kaydediciden baytı al.
  if (pos < sizeof buf)
  {
    buf [pos++] = c;
    if (c == '\n')
      process_it = true;
  }
}

void loop (void)
{
  if (process_it)
  {
    buf [pos] = 0;          // Alınan veriyi göster. 
    Serial.println (buf);
    pos = 0;
    process_it = false;
  } 
}
