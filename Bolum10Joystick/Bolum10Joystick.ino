void setup() {

Serial.begin(9600);
}

void loop() {
  Serial.print("X Ekseni: ");
  Serial.println(analogRead(A0));
  Serial.print("Y Ekseni: ");
  Serial.println(analogRead(A1));
  Serial.println("_____________________");
  delay(500);
}
