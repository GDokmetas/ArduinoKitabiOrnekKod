#include <SPI.h>

void setup (void)
{
  Serial.begin(115200);
  digitalWrite(SS, HIGH);
  SPI.begin ();
  SPI.setClockDivider(SPI_CLOCK_DIV8);
}

void loop (void)
{
  char c;

  // Uydu seçmeyi aç 
  digitalWrite(SS, LOW);    // SS is pin 10

  // Test stringi gönder
  for (const char * p = "Merhaba Dunya!\n" ; c = *p; p++) {
    SPI.transfer (c);
    Serial.print(c);
  }

  // Uydu seçmeyi kapat
  digitalWrite(SS, HIGH);

  delay (1000);
}

