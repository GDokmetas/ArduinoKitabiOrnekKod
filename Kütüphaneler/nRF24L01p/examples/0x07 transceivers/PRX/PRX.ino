#include <SPI.h>
#include <nRF24L01p.h>

nRF24L01p receiver(7,8);//CSN,CE
String message;
int iteration=0;

void setup(){
  delay(150);
  Serial.begin(115200);
  SPI.begin();
  //SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.setBitOrder(MSBFIRST);
  receiver.channel(90);
  receiver.TXaddress("Prado");
  receiver.RXaddress("Artur");
  receiver.init();
  delay(3000);
  Serial.println("I'm PRX as transceiver");
  receiver.txPL("Hi PTX. I'm ready.");
  receiver.send(SLOW);
  receiver.txPL("tell me the library's name");
  receiver.send(SLOW);
}

void loop(){
  if(receiver.available()){
    message="";
    receiver.read();
    receiver.rxPL(message);
    Serial.print("PTX says: \"");
    Serial.print(message);
    Serial.println("\"");
  }else{
    message="";
  }
  delay(20);
  if(message=="nRF24L01p"){
    message="**You're right ";
    message+=String(iteration);
    message+="**";
    receiver.txPL(message);
    receiver.send(SLOW);
    Serial.println("***The nRF24L01p library***");
    Serial.println("It works");
    Serial.println();
    iteration++;
  }else if(message.length()>0){
    receiver.txPL("That's not the name");
    receiver.send(SLOW);
    Serial.println("PTX is wrong");
    Serial.println();
  }
}





