void setup() {
pinMode(9,OUTPUT); // Kırmızı
pinMode(10,OUTPUT); // Yeşil
pinMode(11,OUTPUT); // Mavi

}

void loop() {

for (int i=0; i<255; i++)
{
analogWrite(9,i); 
delay(5);
}

for (int i=0; i<255; i++)
{
analogWrite(10,i); 
delay(5);
}

for (int i=0; i<255; i++)
{
analogWrite(11,i); 
delay(5);
}

for (int i=255; i>0; i--)
{
  analogWrite(9,i);
  delay(5);
  
}

for (int i=255; i>0; i--)
{
  analogWrite(10,i);
  delay(5);
  
}

for (int i=255; i>0; i--)
{
  analogWrite(11,i);
  delay(5);
  
}
}
