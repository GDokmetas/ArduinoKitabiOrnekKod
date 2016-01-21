#include <Wire.h>
#include <LiquidCrystal_I2C.h>
int val;
int tempPin = A0;
float celeski = 100; //Düşük değişken
byte derece[8] = {  //Özel karakter byte dizisi
B01110,
B01010,
B01110,
B00000,
B00000,
B00000,
B00000,
};


LiquidCrystal_I2C lcd(0x27,16,2); //Lcd Tanımla
void setup() {
lcd.begin();
analogReference(INTERNAL);
lcd.createChar(0, derece);  //Özel karakter oluştur

}

void loop() {

val = analogRead(tempPin);
float mv = ( val/1024.0)*1000;
float cel = mv/10;
lcd.home();
lcd.print("SICAKLIK:");
lcd.print(cel);
lcd.write(byte(0));  //Özel karakteri yaz
lcd.print(" ");
lcd.setCursor(0,1);
if (cel<celeski) // Yeni değer düşükse eskiye aktar
celeski = cel;

lcd.print("EN DUSUK:");
lcd.print(celeski);
lcd.write(byte(0)); //Özel karakteri yaz
lcd.print(" ");
delay(500);

}
