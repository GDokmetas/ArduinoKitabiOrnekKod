//Pins
int photoResistor = 0;

int b = 2;
int r = 3;
int g = 4;
int y = 5;


double bAdj = 1.0;
double rAdj = 1.02;
double gAdj = 1.0;
double yAdj = 1.17;
double ambientAdj = 1.0;

void setup()
{
  pinMode(g, OUTPUT);
  pinMode(y, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(r, OUTPUT);
  pinMode(photoResistor, OUTPUT);
  Serial.begin(9600);
}

void loop()
{  
    allOff();
    delay(100);
    asses(100,100);
}

void allOff()
{
    digitalWrite(g, LOW);
    digitalWrite(y, LOW);
    digitalWrite(r, LOW);
    digitalWrite(b, LOW);
}

void allOn()
{
    digitalWrite(g, HIGH);
    digitalWrite(y, HIGH);
    digitalWrite(r, HIGH);
    digitalWrite(b, HIGH);
}

void pulse(int colour)
{
   for(int i=0;i<3;i++)
   {
      digitalWrite(colour, HIGH);
      delay(100);
      digitalWrite(colour, LOW);
      delay(100);
   }
}
 

void asses(int colldownTime, int saturationTime)
{
 
    delay(500);
    double ambient = analogRead(photoResistor);
    Serial.print("Ambient: ");
    Serial.println(ambient*ambientAdj);
    
    digitalWrite(g, HIGH);
    delay(saturationTime);
    double green = analogRead(photoResistor);
    Serial.print("Green: ");
    Serial.println(green*gAdj);
    digitalWrite(g, LOW);
    delay(colldownTime);
    
    digitalWrite(r, HIGH);
    delay(saturationTime);
    double red = analogRead(photoResistor);
    Serial.print("Red: ");
    Serial.println(red*rAdj);
    digitalWrite(r, LOW);
    delay(colldownTime);
    
    digitalWrite(b, HIGH);
    delay(saturationTime);
    double blue = analogRead(photoResistor);
    Serial.print("Blue: ");
    Serial.println(blue*bAdj);
    digitalWrite(b, LOW);
    delay(colldownTime);
    
    digitalWrite(y, HIGH);
    delay(saturationTime);
    double yellow = analogRead(photoResistor);
    Serial.print("Yellow: ");
    Serial.println(yellow*yAdj);
    digitalWrite(y, LOW);
    delay(colldownTime);
    
    double rawData[] = {(green*gAdj), (red*rAdj), (blue*bAdj), (yellow*yAdj)};
    double maximum = ambient*ambientAdj;
    int decision;
    
    for (int i=0; i<4; i++)  
    {
       if (maximum<rawData[i])
      {
          maximum = rawData[i];
          decision = i+1;
      }
    }
         
    Serial.println("");
    
    if(decision == 0)
    {
       Serial.println("Herhangi bir nesne bulunmadi.");
       allOn();
       delay(1000);
       allOff();
    }
    else if(decision == 1)
    {
       Serial.println("Yesil.");
       pulse(g);
    }
    else if(decision == 2)
    {
       Serial.println("Kirmizi.");
       pulse(r);
    }
    else if(decision == 3)
    {
       Serial.println("Mavi.");
       pulse(b);
    }
    else if(decision == 4)
    {
       Serial.println("Sari.");
       pulse(y);
    }
    Serial.println("");

}
