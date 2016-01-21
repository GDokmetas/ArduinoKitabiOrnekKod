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

long myLong[2];
unsigned long myUlong[2];
float myFloats[4];

void loop(){ 
  if(receiver.available()){
    receiver.read();
    receiver.rxPL(myLong,2);
    receiver.rxPL(myUlong,2);
    receiver.rxPL(myFloats,4);
    
    //**Print received arrays**
    for(int it=0;it<2;it++){
      Serial.print(myLong[it]);
      if(it!=1){
        Serial.print('\t');
      }else{
        Serial.println();
      }
    }
    for(int it=0;it<2;it++){
      Serial.print(myUlong[it]);
      if(it!=1){
        Serial.print('\t');
      }else{
        Serial.println();
      }
    }
    for(int it=0;it<4;it++){
      Serial.print(myFloats[it],4);
      if(it!=3){
        Serial.print(' ');
      }else{
        Serial.println();
      }
    }
    Serial.println();
  }
}
