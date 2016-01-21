int val;
int tempPin = A0;

void setup()
{
Serial.begin(9600);
analogReference(INTERNAL);
}
void loop()
{
val = analogRead(tempPin);
float mv = ( val/1024.0)*1000;
float cel = mv/10;
float farh = (cel*9)/5 + 32;

Serial.print("SICAKLIK = ");
Serial.print(cel);
Serial.print("*C");
Serial.println();
delay(1000);
}
