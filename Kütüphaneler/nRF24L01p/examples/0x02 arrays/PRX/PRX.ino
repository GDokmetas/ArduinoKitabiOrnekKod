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

byte myData[5];
char myCharArray[10];
int myInts[3];
unsigned int myUint[5];

void loop(){ 
  if(receiver.available()){
    receiver.read();
    receiver.rxPL(myData,5);
    receiver.rxPL(myCharArray,10);
    receiver.rxPL(myInts,3);
    receiver.rxPL(myUint,5);
	
    //**Print received arrays**
    for(int it=0;it<5;it++){
      Serial.print(myData[it]);
      if(it!=4){
        Serial.print('\t');
      }else{
        Serial.println();
      }
    }
    Serial.println(myCharArray);
    for(int it=0;it<3;it++){
      Serial.print(myInts[it]);
      if(it!=2){
        Serial.print('\t');
      }else{
        Serial.println();
      }
    }
    for(int it=0;it<5;it++){
      Serial.print(myUint[it]);
      if(it!=4){
        Serial.print('\t');
      }else{
        Serial.println();
      }
    }
    Serial.println();
  }
}
