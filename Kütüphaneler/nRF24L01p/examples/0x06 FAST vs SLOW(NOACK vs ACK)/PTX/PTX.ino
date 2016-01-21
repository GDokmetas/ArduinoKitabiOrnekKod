#include <SPI.h>
#include <nRF24L01p.h>

nRF24L01p transmitter(7,8);//CSN,CE

void setup(){
  delay(150);
  Serial.begin(115200);
  SPI.begin();
  //SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.setBitOrder(MSBFIRST);
  transmitter.channel(90);
  transmitter.TXaddress("Artur");
  transmitter.init();
  Serial.println("Send \\n(newline) either to start or to stop");
}

String message;
unsigned long myLong=0;

void loop(){
  if(Serial.available()>0){
    char caracter=Serial.read();
    if(caracter=='\n'){
      while(1){
        message=String(myLong);
        transmitter.txPL(message);
        unsigned long tmr1=micros();
        if(transmitter.send(FAST)){//FAST or SLOW
          unsigned long tmr2=micros();
          Serial.print("Sent: \"");
          Serial.print(myLong);
          Serial.print("\", time: ");
          Serial.print(tmr2-tmr1);
          Serial.println(" uS");
          message="";
          myLong+=25;
          caracter=NULL;
        }else{
          Serial.println("Stopped");
          message="";
          break;
        }
        if(Serial.available()>0){
          if(Serial.read()=='\n'){
            Serial.println();
            Serial.println("*****************  Stopped  *****************");
            Serial.println("Send \\n(newline) either to start or to stop");
            break; 
          }
        }
      }
    }
  }
}

