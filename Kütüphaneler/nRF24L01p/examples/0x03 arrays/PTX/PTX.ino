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
                                  
long myLong[2]={5464531,-42165813};              // 8 Bytes
unsigned long myUlong[2]={45611589,1588426};     // 8 Bytes
float myFloats[4]={1.414213,220,311.1269,-9.8};  //16 Bytes
                                              // = 32 Bytes

void loop(){
  if(Serial.available()>0){
    char character=Serial.read();
    if(character=='\n'){
      transmitter.txPL(myLong,2);
      transmitter.txPL(myUlong,2);
      transmitter.txPL(myFloats,4);
      transmitter.send(SLOW);
    }
  }
}
