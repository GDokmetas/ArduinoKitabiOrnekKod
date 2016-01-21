void setup() {
pinMode(6,OUTPUT);
Serial.begin(9600);
}

void loop() {
int tonedeger = map(analogRead(A0),0,1023,31,1000);
Serial.println("Frekans: ");
Serial.println(tonedeger);
tone(6,tonedeger);
delay(100);
}
