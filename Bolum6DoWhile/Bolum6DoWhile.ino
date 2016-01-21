int sayi = 12;
void setup() {
Serial.begin(9600);
do
{
Serial.print("Sayi: ");
Serial.println(sayi);
sayi++;
}
while (sayi < 20);
}

void loop() {

}
