void setup() {
pinMode(2,INPUT);
pinMode(13,OUTPUT);
}

void loop() {

digitalWrite(13,digitalRead(2));
}
