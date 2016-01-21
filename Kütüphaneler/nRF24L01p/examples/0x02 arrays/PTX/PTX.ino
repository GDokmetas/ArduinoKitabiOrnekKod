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

byte myData[5]={18,05,19,89,24};                 // 5 Bytes
char *myCharArray="NRF24L01+";                   //10 Bytes
int myInts[3]={-311,220,311};                    // 6 Bytes
unsigned int myUint[5]={41000,65000,15,200,5000};//10 Bytes +
                                              // = 31 Bytes
                                  //less than 32 Bytes PayLoad

void loop(){
  if(Serial.available()>0){
    char character=Serial.read();
    if(character=='\n'){
      transmitter.txPL(myData,5);
      transmitter.txPL(myCharArray,10);
      transmitter.txPL(myInts,3);
      transmitter.txPL(myUint,5);
      transmitter.send(SLOW);
    }
  }
}
