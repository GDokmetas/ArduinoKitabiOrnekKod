void setup() {
Serial.begin(9600); 
int sifre=0;
Serial.println("Sifreyi Girin");
while(sifre!=48)
{
  sifre = Serial.read();
}
Serial.println("Sifre Dogru Hos Geldiniz");
Serial.println("E-Mail Sifreniz asbf452_");
}

void loop() {
}
