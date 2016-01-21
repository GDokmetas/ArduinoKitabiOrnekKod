void setup() {
Serial.begin(9600);
}

void loop() {
int okuma = analogRead(A0);
Serial.print("Analog Deger: ");
Serial.println(okuma);
delay(100);
}
