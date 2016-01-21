void setup() {
Serial.begin(9600);
}

void loop() {
int inc=25;
Serial.print("Inch:");
Serial.println(inc);
Serial.print("Inch:");
Serial.println(donusum(inc));

while(1);
}

float donusum(int inc) 
{
  return inc * 2.54;
}

