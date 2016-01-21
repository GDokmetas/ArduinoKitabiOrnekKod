void setup() {
pinMode(6,OUTPUT);
Serial.begin(9600);
}

void loop() {
int pwmdeger = map(analogRead(A0),0,1023,0,255);
Serial.println("PWM: ");
Serial.println(pwmdeger);
analogWrite(6,pwmdeger);
delay(100);
}
