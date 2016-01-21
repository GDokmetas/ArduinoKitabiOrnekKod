void setup() {
pinMode(2,INPUT_PULLUP);
pinMode(13,OUTPUT);
digitalWrite(13,0);
}

void loop() {
if (digitalRead(2)==LOW)
digitalWrite(13,HIGH);
}
