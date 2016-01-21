// Bu program Alıcı Programıdır.
 #define rfReceivePin A0  //Alıcı A0
 #define ledPin 13        //Led 13

 unsigned int data = 0;   // verinin alınacağı kısım
 const unsigned int upperThreshold = 70;  //üst değer 
 const unsigned int lowerThreshold = 50;  //alt değer 

 void setup(){
   pinMode(ledPin, OUTPUT);
   Serial.begin(9600);
 }

 void loop(){
   data=analogRead(rfReceivePin);    //A0dan veriyi oku
   
    if(data>upperThreshold){
     digitalWrite(ledPin, LOW);   //Düşük sinyalde ledi kapat
     Serial.println(data);
   }
   
   if(data<lowerThreshold){
     digitalWrite(ledPin, HIGH);   //yüksek sinyalde ledi aç l
     Serial.println(data);
   }
 }
