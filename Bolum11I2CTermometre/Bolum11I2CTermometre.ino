#include <Wire.h>
#include <LiquidCrystal_I2C.h>
int val;
int tempPin = A0;
LiquidCrystal_I2C lcd(0x27,16,2);
void setup() {
lcd.begin();
analogReference(INTERNAL);
}

void loop() {
val = analogRead(tempPin);
float mv = ( val/1024.0)*1000;
float cel = mv/10;
float farh = (cel*9)/5 + 32;
lcd.home();
lcd.print("SICAKLIK=");
lcd.print(cel);
lcd.print("*C");
lcd.setCursor(0,1);
lcd.print("LCD Termometre");
delay(1000);
}
