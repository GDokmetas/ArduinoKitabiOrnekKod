int pinler[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
int sayma = 0;
int zaman = 100;

void setup() {
for (sayma = 0; sayma < 10 ; sayma++)
pinMode(pinler[sayma], OUTPUT);
}

void loop() {
for (sayma=0; sayma<10; sayma++)
{
  digitalWrite(pinler[sayma],HIGH);
  delay(zaman);
  digitalWrite(pinler[sayma],LOW);
}
for (sayma=9; sayma>=0; sayma--)
{
  digitalWrite(pinler[sayma], HIGH);
  delay(zaman);
  digitalWrite(pinler[sayma], LOW);
}
}
