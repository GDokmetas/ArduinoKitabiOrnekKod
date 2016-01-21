void setup() {
Serial.begin(9600);
}

void loop() {
int okuma = analogRead(A0);
Serial.print("Analog Deger: ");
Serial.println(okuma);
 float gerilim = okuma * (5.0 / 1023.0);
 Serial.print("Gerilim: ");
 Serial.print(gerilim);
 Serial.println("V");
delay(100);
}
