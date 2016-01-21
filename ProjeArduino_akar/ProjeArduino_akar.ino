
const int analogInPin = A0; 
int sensorValue = 0;       
int timer = 0;             

void setup() {

  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
  
  sensorValue = analogRead(analogInPin);
 
  timer = map(sensorValue, 0, 1023, 10, 500);

  digitalWrite(12, HIGH);
  delay(timer);
  digitalWrite(12, LOW);
  delay(timer);
  digitalWrite(12, HIGH);
  delay(timer);
  digitalWrite(12, LOW);
  digitalWrite(11, HIGH);
  delay(timer);
  digitalWrite(11, LOW);
  delay(timer);
  digitalWrite(11, HIGH);
  delay(timer);
  digitalWrite(11, LOW);
}
