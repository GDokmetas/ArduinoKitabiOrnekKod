#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
byte bar1[8] = {
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
};
byte bar2[8] = {
  B11011,
  B11011,
  B11011,
  B11011,
  B11011,
  B11011,
  B11011,
};

void setup() {
lcd.begin();
lcd.backlight();
lcd.createChar(5, bar1);
lcd.createChar(6, bar2);
}

void loop() {
 int kalan=16;
 int bardeger=analogRead(A0);
 bardeger=map(bardeger, 0, 1023, 0, 32);
 lcd.home();
 lcd.print("Bar:");
 lcd.print(bardeger);
 lcd.print(" ");
 lcd.setCursor(0,1);
while(!(bardeger<=0))
 {
  if(bardeger>1)
  {
  lcd.write(byte(6));
  bardeger-=2;
  /* kalan */ 
  kalan--;
  }
  else
  {
  lcd.write(byte(5));
  bardeger--;
  kalan--;
  } 
 }
for (int i=kalan; kalan>0; kalan--)
lcd.print(" ");
}
