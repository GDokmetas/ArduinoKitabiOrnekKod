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

float myFloats[10];

void loop(){ 
  if(receiver.available()){
    receiver.read();
    receiver.rxPL(myFloats,5,8);    
    for(int ctr=5;ctr<=8;ctr++){
      Serial.print(myFloats[ctr],4);
      if(ctr==8){
        Serial.println();
      }
      else{
        Serial.print('\t');
      }
    }
  }
}
