#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);


#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

void setup () {
lcd.begin();
lcd.backlight();
lcd.home(); 

}

void loop () {
    DateTime now = rtc.now();
    lcd.setCursor(0,0);
    lcd.print(now.day(), DEC);
    lcd.print("-");
    lcd.print(now.month(), DEC);
    lcd.print("-");
    lcd.print(now.year(), DEC); 
    lcd.setCursor(0,1);
    lcd.print(now.hour(), DEC);
    lcd.print(":");
    lcd.print(now.minute(), DEC);
    lcd.print(":");
    lcd.print(now.second(), DEC);
    lcd.print("      ");
    delay(50);

}
