void setup() {
Serial.begin(9600);
}

void loop() {
yazdirma('-',40);
Serial.println("Arduino ile Asiri Yuklenen Fonksiyonlar");
yazdirma('-');
yazdirma();

while(1);
}

void yazdirma (char k,int i)
{
  for(i ; i>0;i--)
  Serial.print(k);
  Serial.println();
}


void yazdirma (char k)
{
  for(int i=30 ; i>0;i--)
  Serial.print(k);
  Serial.println();
}



void yazdirma ()
{
  for(int i=30 ; i>0;i--)
  Serial.print("=");
  Serial.println();
}

