void setup() {
pinMode(2,INPUT_PULLUP);
pinMode(13,OUTPUT);
}

void loop() {

digitalWrite(13,digitalRead(2));
}
