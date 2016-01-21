void setup() {
Serial.begin(9600);
}

void loop() {
int en = 10;
int boy= 5;
int alan;
hesaplama(en,boy,alan);
Serial.print("En ");
Serial.println(en);
Serial.print("Boy ");
Serial.println(boy);
Serial.print("Alan ");
Serial.println(alan);
while(1);
}

void hesaplama(int en,int boy,int& alan)
{
  alan=en*boy;
}

