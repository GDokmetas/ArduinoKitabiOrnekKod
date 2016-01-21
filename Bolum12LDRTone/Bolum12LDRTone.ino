/*
Kod : Arduino.cc 
 http://www.arduino.cc/en/Tutorial/Tone2

 */


void setup() {
  // initialize serial communications (for debugging only):
  Serial.begin(9600);
}

void loop() {
  
  int sensorReading = analogRead(A0);
  
  Serial.println(sensorReading);

  int thisPitch = map(sensorReading, 400, 1000, 120, 1500);

  tone(6, thisPitch, 10);
  delay(1);        
}
