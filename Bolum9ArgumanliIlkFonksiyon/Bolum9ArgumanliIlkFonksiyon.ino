void setup() {
Serial.begin(9600);
}

void loop() {
cizgi('*');
Serial.println("Merhaba Dunya!");
cizgi('*');
Serial.println("Arduino ile Fonksiyonlari Deniyoruz");
cizgi('_');
while(1);
}

void cizgi (char c)
{
  for (int i=0; i<40; i++)
  Serial.print(c);
  Serial.println();
}

