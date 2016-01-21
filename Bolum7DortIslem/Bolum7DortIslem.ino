int x = 65;
int y = 20;
int z = 0;
void setup() {
Serial.begin(9600);
z = x + y;
Serial.print("x + y =");
Serial.println(z);
z = x - y;
Serial.print("x - y =");
Serial.println(z);
z = x * y;
Serial.print("x * y =");
Serial.println(z);
z = x / y;
Serial.print("x / y =");
Serial.println(z);
}

void loop() {


}
