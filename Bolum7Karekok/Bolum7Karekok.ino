void setup() {
Serial.begin(9600);
for ( int i=0; i<30 ; i++)
{
  Serial.print("Sayi:");
  Serial.print(i);
  Serial.print("  ");
  Serial.print(sqrt(i));
  Serial.println();
}
}

void loop() {
  // put your main code here, to run repeatedly:

}
