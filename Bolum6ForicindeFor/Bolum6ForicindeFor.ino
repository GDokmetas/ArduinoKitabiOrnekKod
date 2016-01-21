void setup() {
Serial.begin(9600);
for(char k=50; k<110; k++)
{
for(int i=0; i<30; i++)
Serial.print(k);
Serial.println();
}
}

void loop() {
  // put your main code here, to run repeatedly:

}
