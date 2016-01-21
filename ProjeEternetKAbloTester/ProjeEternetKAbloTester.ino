//#define VERBOSE

char straight[8] = {2, 3, 4, 5, 6, 7, 8, 9};
char cross[8] = {4, 7, 2, 5, 6, 3, 8, 9};

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(12, INPUT); // Straight (normal) cable or cross cable
  pinMode(13, OUTPUT); // Control LED
#ifdef VERBOSE
  Serial.begin(9600);
#endif
}

void loop() {
  if (digitalRead(12) == LOW) { // Cross cable
#ifdef VERBOSE
    Serial.println("Cross cable");
#endif
    for (char n = 0;n < 8;n++) {
#ifdef VERBOSE
      Serial.print(n+1, DEC);
      Serial.print(": line ");
      Serial.print(cross[n]-1, DEC);
      Serial.print(" (pin ");
      Serial.print(cross[n], DEC);
      Serial.println(")");
#endif
      PulseOut(cross[n], 1000);
      PulseOut(13, 50);
    }
  } else { // Straight (normal) cable
#ifdef VERBOSE
    Serial.println("Straight cable");
#endif
    for (char n = 0;n < 8;n++) {
 #ifdef VERBOSE
      Serial.print(n+1, DEC);
      Serial.print(": line ");
      Serial.print(straight[n]-1, DEC);
      Serial.print(" (pin ");
      Serial.print(straight[n], DEC);
      Serial.println(")");
#endif
      PulseOut(straight[n], 1000);
      PulseOut(13, 50);
    }
  }
}

void PulseOut(char pin, int ms)
{
  digitalWrite(pin, HIGH);
  delay(ms);
  digitalWrite(pin, LOW);
}
