#include <SPI.h>
#include <SD.h>
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
const int chipSelect = 10; //SD CS/SS bacağı

LiquidCrystal_I2C lcd(0x27,16,2); //Lcd Tanımla
void setup() {
lcd.begin();
analogReference(INTERNAL);
lcd.createChar(0, derece);  //Özel karakter oluştur
pinMode(2,OUTPUT);

  Serial.println("SD KART YUKLENIYOR");  // KART KONTROL
  if (!SD.begin(chipSelect)) {
  Serial.println("SD KART TANINMADI");
  }
  Serial.println("SD KART TANINDI VE HAZIR");

  if (!SD.exists("datalog.txt"))  // Eğer dosya yoksa yenisini oluştur
  { 
  SD.open("datalog.txt");
  Serial.println("Yeni Datalog.txt Dosyası Acildi"); 
  }
  else 
  { Serial.println("Datalog.txt Bulundu"); } // TXT dosyası Kontrolü

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

//SD KAYIT
 digitalWrite(2,HIGH);
 File dataFile = SD.open("datalog.txt", FILE_WRITE);
  dataFile.print(millis()/1000); // Geçen süreyi kaydet. (millis program başından itibaren geçen ms değerini verir.)
  dataFile.print(" ");
  dataFile.println(cel); // Sıcaklık Kaydet
  dataFile.close(); 
 delay(100);
 digitalWrite(2,LOW);
delay(4900);
}
