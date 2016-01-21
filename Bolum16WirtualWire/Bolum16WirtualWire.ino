/*
Bu alıcı devresidir. Alıcının bacağı dijital 11 'e bağlanmalı
*/
#include <VirtualWire.h>
byte message[VW_MAX_MESSAGE_LEN]; //gelen mesajı tutmak için tampon bellek
byte messageLength = VW_MAX_MESSAGE_LEN; // gelen mesajın hacmi
void setup()
{
Serial.begin(9600);
Serial.println("Cihaz Hazır");
// Giriş çıkışı ve cihazı tanımla
vw_setup(2000); // Bit hızı 
vw_rx_start(); // Cihazı başlat.
}
void loop()
{
if (vw_get_message(message, &messageLength)) 
{
Serial.print("Gelen Mesaj: ");
for (int i = 0; i < messageLength; i++)
{
Serial.write(message[i]);
}
Serial.println();
}
}
