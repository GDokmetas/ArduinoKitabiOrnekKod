
// Nick Gammon Tarafından Yazılmıştır
// Ocak 2011

#include <SPI.h>

void setup (void)
{
}


void loop (void)
{

  
  digitalWrite(SS, HIGH);  // SS ayağının HIGH olmasından emin ol

  // SCK, MOSI , MISO ayakları çıkış olarak ayarlanır
  // Ayrıca SCK, MOSI, MISO LOW SS HIGH OLARAK AYARLANIR
  // Sonrasında SPI Ana aygıt olarak ayarlanır ve başlatılır.
  SPI.begin ();

  delay (5000);  // Lojik Analizör için bekleme

  char c;
  
  // SS bacağını etkinleştir.
  digitalWrite(SS, LOW);    //SS bacağı 10
  
  // Test karakter dizisini yolla
  for (const char * p = "Fab" ; c = *p; p++)
    SPI.transfer (c);

 // SS bacağını kapat. 
 digitalWrite(SS, HIGH);

 // SP kapat
 SPI.end ();
 
 while (1);  //Programı bitir. 
}
