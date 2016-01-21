#include <EEPROM.h>
#include <LiquidCrystal.h>
// Kütüphaneleri Ekliyoruz 

LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // 8 RS 9 E 4 5 6 7 Data Ayakları 

byte derece[8] = {  //Özel karakter byte dizisi
B01110,
B01010,
B01110,
B00000,
B00000,
B00000,
B00000,
};

int val;
int tempPin = A1;  // Analog 1 olmasına dikkat!. 
int romadres = EEPROM.get(1000,romadres); 
/* Adres değeri program kapatılmadan önce kayıt altında tutulur. Böylelikle her program açılışında 0'dan başlanmak engellenir  */

void setup() {
Serial.begin(9600);
lcd.begin(16,2);
analogReference(INTERNAL); //1v1 referans 
lcd.createChar(0, derece);
/* Giriş Yazısı */ 
lcd.home(); 
lcd.print("Arduino ile");
lcd.setCursor(0,1);
lcd.print("DL Termometre");
delay(2000);
lcd.clear(); 
/*Seri Giriş Ekranı*/ 
Serial.println("*****************************************************");
Serial.println("LM35 ile Datalogger Dijital Termometre by Gokhan Dokmetas");
Serial.println("Programi Calistirmak icin 1");
Serial.println("EEPROM Silmek icin 2 ye basiniz");
Serial.println("_____________________________________________________");
}

void loop() {
val = analogRead(tempPin);
float mv = ( val/1024.0)*1000; 
float cel = mv/10;  // LM35 okuma ve hesaplama 

EEPROM.put(romadres,cel); //Float değişkenini kaydet
romadres+=4;
EEPROM.put(1000,romadres); //4 byte yer atla .

if(romadres>995) //Romadres değeri taştığında sıfırla
romadres=0;

if (Serial.available() > 0) // Eğer seri giriş olursa 
  {
    char Serikontrol = Serial.read(); //Klavyeden değeri al 1 veya 2
    if (Serikontrol=='1')
    seriyazdirma(cel);  // Buradaki gönderilen float değeri get fonksiyonunda değer tipi algılamak için
    if (Serikontrol=='2')
    romsilme();
    else 
    Serial.println("1 Goruntuleme, 2 Silme");
  }
/* LCD DURUM EKRANI */ 
lcd.home();
lcd.print("SICAKLIK:");
lcd.print(cel);
lcd.write(byte(0));  //Özel karakteri yaz
lcd.print(" ");
lcd.setCursor(0,1);

delay(20000); // 20 SN aralıklarla ölçüm yapar. Bunu istediğiniz gibi değiştirebilirsiniz.
}

void seriyazdirma(float cel)
{
  Serial.println("SICAKLIK DEGERLERI");
  for(int i=0; i<=romadres; i+=4) // Baştan rom adrese kadar yazdır.
  {
  Serial.print(i*5); // Sırasını yazdır. 
  Serial.print(" ");
  EEPROM.get(i,cel);
  Serial.println(cel); // Değeri yazdır. 
  }
Serial.println("ISLEM TAMAMLANDI"); 
delay(1000);
}

void romsilme () 
{
 for (int i = 0 ; i < EEPROM.length() ; i++)  //EEPROM sil
 EEPROM.write(i, 0);
Serial.println("EEPROM SILINDI");
romadres=0;
EEPROM.put(1000,romadres);
Serial.println("Cihazi Yeniden Baslatmak icin");
Serial.println("Bilgisayar ile baglantiyi kesin");
while(1);
}

