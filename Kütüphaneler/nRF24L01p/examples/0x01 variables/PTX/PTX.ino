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

String message;
byte numberByte=0;
char letter='!';
int numberInt=-1730;
unsigned int numberUint=43156;
long numberLong=-2147304468;
unsigned long numberUlong=3294967295;
float numberFloat=311.1269;

void loop(){
  if(Serial.available()>0){
    char character=Serial.read();
    if(character=='\n'){
      transmitter.txPL(letter);
      transmitter.txPL(numberByte);
      transmitter.txPL(numberInt);
      transmitter.txPL(numberUint);
      transmitter.txPL(numberLong);
      transmitter.txPL(numberUlong);
      transmitter.txPL(numberFloat);
      transmitter.txPL(message);
      transmitter.send(SLOW);
      letter++;
      numberByte++;
      numberInt+=20;
      numberUint-=51;
      numberLong+=1234567;
      numberUlong-=1234567;
      numberFloat-=5.3121;
      message="";
    }else{
      message+=character;
    }
  }
}
