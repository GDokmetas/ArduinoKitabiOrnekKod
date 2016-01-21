#include <SPI.h>
#include <nRF24L01p.h>

nRF24L01p transmitter(7,8);//CSN,CE

void setup(){
  delay(150);
  Serial.begin(115200);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  transmitter.channel(90);
  transmitter.TXaddress("Artur");
  transmitter.init();
}

char msg[]="Reference to Pointer";
int numero=0;

void loop(){
  if(Serial.available()>0){
    char character=Serial.read();
    if(character=='\n'){
      transmitter.txPL(msg);
      transmitter.txPL(numero);
      transmitter.send(SLOW);
      numero++;
    }
  }
}
