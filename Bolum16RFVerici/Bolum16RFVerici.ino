 // Bu program verici programıdır. 
 #define rfTransmitPin 4  //RF Gönderim Ayağı
 #define ledPin 13        //Onboard LED

 void setup(){
   pinMode(rfTransmitPin, OUTPUT);     
   pinMode(ledPin, OUTPUT);    
 }

 void loop(){
   for(int i=4000; i>5; i=i-(i/3)){
     digitalWrite(rfTransmitPin, HIGH);     //Sinyal Yolla
     digitalWrite(ledPin, HIGH);            //Ledi Aç
     delay(2000);                           //1 Sn bekle
     
     digitalWrite(rfTransmitPin,LOW);      //Sinyali Düşür
     digitalWrite(ledPin, LOW);            //ledi kapat
     delay(i);                            //bir süre bekle. 
   }
 }
