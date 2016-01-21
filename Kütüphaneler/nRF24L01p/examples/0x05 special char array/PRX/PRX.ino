#include <SPI.h>
#include <nRF24L01p.h>

nRF24L01p receiver(7,8);//CSN,CE

void setup(){
  delay(150);
  Serial.begin(115200);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  receiver.channel(90);
  receiver.RXaddress("Artur");
  receiver.init();
}

char *msg;
int numero=0;

void loop(){ 
  if(receiver.available()){
    receiver.read();
    receiver.rxPL(msg);
    receiver.rxPL(numero); 
    Serial.print(msg);
    Serial.print(" ");
    Serial.println(numero);
  }
}
