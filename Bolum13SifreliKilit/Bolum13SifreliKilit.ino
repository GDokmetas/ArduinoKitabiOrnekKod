#include <LiquidCrystal.h>
#include <EEPROM.h>
LiquidCrystal lcd(8,9,4,5,6,7); // lcd bağlantı bacakları
int basamak1=0;
int basamak2=0;
int basamak3=0; // iki fonksiyon da kullanacağı için  global değişken yapıldı. 
int sifre;
void setup() {
pinMode(A5,INPUT_PULLUP);
pinMode(A4,INPUT_PULLUP);
pinMode(A3,INPUT_PULLUP); // Düğmeler buraya bağlanacağından input pullup seçimi yApıldı
lcd.begin(16,2);
Serial.begin(9600); //  Geliştiriciler için
/* LCD EKRAN YAZDIRMA */ 
lcd.print("Arduino ile");
lcd.setCursor(0,1);
lcd.print("Sifreli Kilit");
delay(2000);
lcd.clear(); // ekranı temizle
lcd.home(); //en başa gel
 
}

void loop() {  // Ana programda şifre girilecek

lcd.clear();
lcd.setCursor(0,1);
lcd.print("  SIFRE GIRIN  ");
lcd.setCursor(0,0); 
lcd.print("     0 0 0      ");  // ekranda basamak gösterimi
lcd.blink(); // Yanıp sönen imleç 
basamak1=0;
basamak2=0;
basamak3=0; // Değerleri sıfırladık
//Basamak1
lcd.setCursor(5,0); 

while((digitalRead(A5))) // Geçme düğmesi 3. düğme o basılmadığında programı sürdür. 
{
  if (!(digitalRead(A3)) && basamak1>0 ) // Basamak 0dan küçükse 1. düğme ile azalt 
  {
  basamak1--;
  lcd.setCursor(5,0); 
  lcd.print(basamak1);
  }
  if (!(digitalRead(A4)) && basamak1<9 ) // Basamak 9 da küçükse 2. düğme ile bir artır. 
  {
  basamak1++;
  lcd.setCursor(5,0);  // Güncellenen basamak değerini ekrana yaz. 
  lcd.print(basamak1);
  }

 if ( !(digitalRead(A3)) && !(digitalRead(A4)) ) // Eğer 1. ve ikinci düğme basılı tutulursa. 
 {
 yenisifre(); // yeni şifre koyma fonksiyonuna git. 
 loop(); // sonrasında loop fonksiyonunun başına dön 
 }
 
delay(200); // azıcık bekle 
}
if (!(digitalRead(A5))) // Eğer düğmeye hala basılıyorsa biraz beklet. 
delay(500);

basamak1 = basamak1 * 100; // basamak sayısını hesapla 

//2. basamak

lcd.setCursor(7,0);  // imleci basamak rakamının yanına getir. 

while((digitalRead(A5))) // Yukarıdaki işlemin aynısını uygula 
{
  if (!(digitalRead(A3)) && basamak2>0 )
  {
  basamak2--;
  lcd.setCursor(7,0); 
  lcd.print(basamak2);
  }
  if (!(digitalRead(A4)) && basamak2<9 )
  {
  basamak2++;
  lcd.setCursor(7,0); 
  lcd.print(basamak2);
  }
delay(200);
}
if (!(digitalRead(A5)))
delay(500);

basamak2 = basamak2 * 10; // onlar basamağını hesapla

//3. basamak

lcd.setCursor(9,0);  // imleci 3. sayının olduğu yere getir. 

while((digitalRead(A5))) // yukarıdaki işlemin aynısını uygula
{
  if (!(digitalRead(A3)) && basamak3>0 )
  {
  basamak3--;
  lcd.setCursor(9,0); 
  lcd.print(basamak3);
  }
  if (!(digitalRead(A4)) && basamak3<9 )
  {
  basamak3++;
  lcd.setCursor(9,0); 
  lcd.print(basamak3);
  }
delay(200);
}
if (!(digitalRead(A5)))
delay(500);

basamak3 = basamak3 * 1; // birlik basamağı da hesapla

// Sifre karsilastirma

int girilensifre = basamak1 + basamak2 + basamak3; // En sonunda bütün sayıları topla 
EEPROM.get(0,sifre);  // EEPROM dan da şifreyi oku
if (girilensifre == sifre) // İkisini karşılaştır
{
lcd.setCursor(0,1); 
lcd.print("  SIFRE DOGRU! "); //Doğruysa söyle. 
while(1); // Programı kapat Bu kısma kendi fonksiyonunuzu ekleyebilirsiniz.
}
if (girilensifre!=sifre) // Eğer yanlışsa 
{
  lcd.setCursor(0,1);
  lcd.print("  SIFRE YANLIS! "); // Yanlış olduğunu söyle. 
  delay(2000);
}

}

void yenisifre() 
{
eepromsilme(); // EEPROM sil
lcd.setCursor(0,1);
lcd.print("YENI SIFRE GIRIN");
lcd.setCursor(0,0); 
lcd.print("     0 0 0      ");
lcd.blink();
//Basamak1
lcd.setCursor(5,0); 

while((digitalRead(A5))) // Yukarının aynısı
{
  if (!(digitalRead(A3)) && basamak1>0 )
  {
  basamak1--;
  lcd.setCursor(5,0);
  lcd.print(basamak1);
  }
  if (!(digitalRead(A4)) && basamak1<9 )
  {
  basamak1++;
  lcd.setCursor(5,0);
  lcd.print(basamak1);
  }

delay(200);
}
if (!(digitalRead(A5)))
delay(500);

basamak1 = basamak1 * 100;

//2. basamak

lcd.setCursor(7,0); 

while((digitalRead(A5)))
{
  if (!(digitalRead(A3)) && basamak2>0 )
  {
  basamak2--;
  lcd.setCursor(7,0); 
  lcd.print(basamak2);
  }
  if (!(digitalRead(A4)) && basamak2<9 )
  {
  basamak2++;
  lcd.setCursor(7,0); 
  lcd.print(basamak2);
  }
delay(200);
}
if (!(digitalRead(A5)))
delay(500);

basamak2 = basamak2 * 10;

//3. basamak

lcd.setCursor(9,0); 

while((digitalRead(A5)))
{
  if (!(digitalRead(A3)) && basamak3>0 )
  {
  basamak3--;
  lcd.setCursor(9,0); 
  lcd.print(basamak3);
  }
  if (!(digitalRead(A4)) && basamak3<9 )
  {
  basamak3++;
  lcd.setCursor(9,0); 
  lcd.print(basamak3);
  }
delay(200);
}
if (!(digitalRead(A5)))
delay(500);

basamak3 = basamak3 * 1;


int girilensifre = basamak1 + basamak2 + basamak3; // Sayıları topla
EEPROM.put(0,girilensifre); // EEPROMA yazdır
lcd.setCursor(0,1);
lcd.print("YENI SIFRE!!    ");
delay(2000);  
//

}

void eepromsilme() // Bütün hücreleri tara ve 0 yerleştir. 
{
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
 
}

