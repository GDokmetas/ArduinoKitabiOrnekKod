void setup() {
Serial.begin(9600);
}

void loop() {
cizgi();
Serial.println("Merhaba Dunya!");
cizgi();
while(1);
}

void cizgi ()
{
  for (int i=0; i<30; i++)
  Serial.print("-");
  Serial.println();
}

