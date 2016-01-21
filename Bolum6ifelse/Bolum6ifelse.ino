void setup() {
pinMode(2,INPUT_PULLUP);
Serial.begin(9600);
}

void loop() {
if (digitalRead(2)==LOW)
Serial.println("Dugmeye Basildi");
else
Serial.println("Dugme Basili Degil");
delay(200);
}
