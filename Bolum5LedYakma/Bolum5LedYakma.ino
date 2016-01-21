
 void setup()  
 {
  pinMode(12, OUTPUT);
  
 }

 void loop()
 {
    digitalWrite(12, HIGH);  // Ledi Yak
    delay(300);
    digitalWrite(12, LOW);  // Ledi Söndür
    delay(300);
 }

