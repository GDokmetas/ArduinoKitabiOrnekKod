
void setup() {
pinMode(13,OUTPUT);
Serial.begin(9600);
}

void loop() {

  kartled();
  delay(500);
  kartled();
  delay(500);
}

void kartled ()
{
  static bool leddurum=0;
  if (leddurum)
  digitalWrite(13,HIGH);
  else
  digitalWrite(13,LOW);
  leddurum= !leddurum;
}

