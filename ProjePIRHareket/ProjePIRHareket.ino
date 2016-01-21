
 
int led = 13; // Led Ayağı
int sensor = 4; // Algılayıcı Ayağı
int state = LOW; 
int val = 0;
 
void setup() {
pinMode(led, OUTPUT);
pinMode(sensor, INPUT);
Serial.begin(9600);
}
 
void loop(){
val = digitalRead(sensor);
if (val == HIGH) {
digitalWrite(led, HIGH);
delay(50);
 
if (state == LOW) {
Serial.println("Hareket tespit edildi.");
state = HIGH;
}
}
else {
digitalWrite(led, LOW);
delay(100);
 
if (state == HIGH){
Serial.println("Hareket yoktur.");
state = LOW;
}
}
}
