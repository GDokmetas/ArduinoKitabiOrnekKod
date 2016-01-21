/*
 * Nokia 3310 SMS Programı if ifadesiyle :)
 */

void setup() 
{
pinMode(2,INPUT_PULLUP);
pinMode(13,OUTPUT);
}

void loop() {
if (digitalRead(2)==LOW)
{
digitalWrite(13, HIGH);
delay(100);
digitalWrite(13, LOW);
delay(100);

digitalWrite(13, HIGH);
delay(100);
digitalWrite(13, LOW);
delay(100);

digitalWrite(13, HIGH);
delay(100);
digitalWrite(13, LOW);
delay(300);

digitalWrite(13, HIGH);
delay(300);
digitalWrite(13, LOW);
delay(200);

digitalWrite(13, HIGH);
delay(300);
digitalWrite(13, LOW);
delay(200);

digitalWrite(13, HIGH);
delay(100);
digitalWrite(13, LOW);
delay(100);

digitalWrite(13, HIGH);
delay(100);
digitalWrite(13, LOW);
delay(100);

digitalWrite(13, HIGH);
delay(100);
digitalWrite(13, LOW);
delay(100);
delay(500);
}
}
