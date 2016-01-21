const int analogPin = A0;   // trimpot bağlanacak ayak
const int ledCount = 10;    // led sayısı

int ledPins[] = {  //Led pinlerini dizi olarak tanımla
  2, 3, 4, 5, 6, 7, 8, 9, 10, 11
};  


void setup() {

  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT); //Led ayakları çıkış olarak tanımlanır
  }
}

void loop() {

  int sensorReading = analogRead(analogPin); //Trimpottan analog okuma yapılır

  int ledLevel = map(sensorReading, 0, 1023, 0, ledCount); // 0-1023 arası değer 0-led sayısı arasına çevrilir.

  // led seviyesi kadar led yakılır
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
 
    if (thisLed < ledLevel) {
      digitalWrite(ledPins[thisLed], HIGH);
    }
    
    else {
      digitalWrite(ledPins[thisLed], LOW);
    }
  }
}


