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

String message;
byte numberByte;
char letter;
int numberInt;
unsigned int numberUint;
long numberLong;
unsigned long numberUlong;
float numberFloat;

void loop(){ 
  if(receiver.available()){
    receiver.read();
    receiver.rxPL(letter);
    receiver.rxPL(numberByte);
    receiver.rxPL(numberInt);
    receiver.rxPL(numberUint);
    receiver.rxPL(numberLong);
    receiver.rxPL(numberUlong);
    receiver.rxPL(numberFloat);
    receiver.rxPL(message);
    Serial.print(letter);
    Serial.print(" ");
    Serial.print(numberByte);
    Serial.print(" ");
    Serial.print(numberInt);
    Serial.print(" ");
    Serial.print(numberUint);
    Serial.print(" ");
    Serial.print(numberLong);
    Serial.print(" ");
    Serial.print(numberUlong);
    Serial.print(" ");
    Serial.print(numberFloat);
    Serial.print(" ");
    Serial.println(message);
    message="";
  }
}
