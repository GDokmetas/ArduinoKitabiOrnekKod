/*
Bu gönderici devrenin programıdır. Gönderim bacağı 12'ye bağlanmalı.
*/
#include <VirtualWire.h>
void setup()
{
// Initialize the IO and ISR
vw_setup(2000); // Saniyedeki Bit sayisi
}
void loop()
{
send("Merhaba Dunya");
delay(1000);
}
void send (char *message)
{
vw_send((uint8_t *)message, strlen(message));
vw_wait_tx(); // Tüm mesaj gidene kadar bekle
}
