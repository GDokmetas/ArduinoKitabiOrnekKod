int kup;
int sayi;

void setup() {
Serial.begin(9600);

while (kup<5000)
{
  Serial.print(sayi);
  Serial.print("    ");
  kup=sayi*sayi*sayi;
  Serial.println(kup);
  sayi++;
}
  Serial.println("Islem Bitti");
}
void loop() {

}
