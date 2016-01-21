int x=560;

void setup() {
Serial.begin(9600);
if (x>1000)
Serial.println("X 1000 den buyuktur");
else if (x>800) 
Serial.println("X 800 den buyuktur 1000 den kucuktur");
else if (x>600)
Serial.println("X 600 den buyuktur 800 den kucuktur");
else if (x>400)
Serial.println("X 400 den buyuktur 600 den kucuktur");
else 
Serial.println("X 400 den kucuktur.");

}

void loop() {}
