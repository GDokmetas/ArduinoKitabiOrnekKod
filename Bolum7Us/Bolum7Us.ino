int sayi=2;
void setup() {
Serial.begin(9600);
for ( int i=0; i<10 ; i++)
{
  Serial.print("Taban:");
  Serial.print(sayi);
  Serial.print(" ");
  Serial.print("Us:");
  Serial.print(i);
  Serial.print("  ");
  Serial.print((pow(sayi,i)));
  Serial.println();
  
}
}

void loop() {

}
