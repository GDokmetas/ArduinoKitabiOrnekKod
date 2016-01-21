int butondurum;
void setup() {
pinMode(2,INPUT_PULLUP);
pinMode(3,INPUT_PULLUP);
pinMode(4,INPUT_PULLUP);
pinMode(5,INPUT_PULLUP);

Serial.begin(9600);
}

void loop() {
if(!(digitalRead(2)))
butondurum=1;
if(!(digitalRead(3)))
butondurum=2;
if(!(digitalRead(4)))
butondurum=3;
if(!(digitalRead(5)))
butondurum=4;


switch (butondurum)
{
  case 1:
  Serial.println("Birinci Dugmeye Basildi");
  break;
  case 2:
  Serial.println("Ikinci Dugmeye Basildi");
  break;
  case 3:
  Serial.println("Ucuncu Dugmeye Basildi");
  break;
  case 4:
  Serial.println("Dorduncu Dugmeye Basildi");
  break;

  default: 
  Serial.println();
}
butondurum=0;
delay(200);
}
