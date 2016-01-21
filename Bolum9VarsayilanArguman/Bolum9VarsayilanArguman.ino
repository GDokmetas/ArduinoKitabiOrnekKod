void yazdirma (char k='_',int i=40)
{
  for(i ; i>0;i--)
  Serial.print(k);
  Serial.println();
}



void setup() {
Serial.begin(9600);
}

void loop() {
yazdirma('-',30);
Serial.println("Arduino ile Asiri Yuklenen Fonksiyonlar");
yazdirma();

while(1);
}


