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

float myFloats[8]={
  1.414213,220,311.1269,1.73205,-9.8,2.71828,3.14159,6.673};

void loop(){
  if(Serial.available()>0){
    char character=Serial.read();
    if(character=='\n'){
      transmitter.txPL(myFloats,4,7);
      transmitter.send(SLOW);
    }
  }
}



