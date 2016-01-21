
const int sensorMin = 0;   
const int sensorMax = 1024; 

void setup() {

  Serial.begin(9600);  
}
void loop() {

	int sensorReading = analogRead(A0);

 
	int range = map(sensorReading, sensorMin, sensorMax, 0, 3);
  
  // range value:
  switch (range) {
  case 0:    // Eğer ateş 50cm'den yakınsa
    Serial.println("** Ates Cok Yakin **");
    break;
  case 1:    // Eger ateş 0.5m - 1.5m arasındaysa
    Serial.println("** Uzakta Ates Var **");
    break;
  case 2:    // Ateş algılanmazsa
    Serial.println("Ates algilanmadi (Belki uzaklarda vardir.)");
    break;
  }
  delay(1); 
}
