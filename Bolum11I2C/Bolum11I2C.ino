#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 1);

void setup()
{

	lcd.begin();
  
	lcd.print("Arduino ile I2C");
}

void loop()
{

}
