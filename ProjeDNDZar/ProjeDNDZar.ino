
#include <LiquidCrystal.h>
byte kare[8] = {  // Boş seçim düğmesi
  B00000,
  B11111,
  B10001,
  B10001,
  B11111,
  B00000,
  B00000,
};

byte dolukare[8] = { // Dolu seçim düğmesi
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
  B00000,
  B00000,
};

  
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int button = 0;
int buttonState=0;
int col,row;
int secim =0;
int deger=0;
void setup() 
{
  col=0;
  row=0;
  lcd.begin(16, 2);
 pinMode(button,INPUT);
 Serial.begin(9600);
lcd.createChar(0, kare);
lcd.createChar(1, dolukare); 
lcd.setCursor(0,0);
lcd.print("    D&D    ");  // Giriş yazısı
lcd.setCursor(0,1);
lcd.print("Zar Programi");
delay(3000);
lcd.clear();
randomSeed(millis()); // Rastgele sayı beslemesi. 
}

void loop() {
  /*
   * Ana Ekran
   */
  switch (secim)
  {
    case 0: 
    lcd.setCursor(4,0);
    lcd.write(byte(1));
    lcd.setCursor(8,0);
    lcd.write(byte(0));
    lcd.setCursor(12,0);
    lcd.write(byte(0));
    lcd.setCursor(4,1);
    lcd.write(byte(0));
    lcd.setCursor(8,1);
    lcd.write(byte(0));
    lcd.setCursor(12,1);
    lcd.write(byte(0));
    break;

    case 1:
    lcd.setCursor(4,0);
    lcd.write(byte(0));
    lcd.setCursor(8,0);
    lcd.write(byte(1));
    lcd.setCursor(12,0);
    lcd.write(byte(0));
    lcd.setCursor(4,1);
    lcd.write(byte(0));
    lcd.setCursor(8,1);
    lcd.write(byte(0));
    lcd.setCursor(12,1);
    lcd.write(byte(0));
    break;

    case 2:
    lcd.setCursor(4,0);
    lcd.write(byte(0));
    lcd.setCursor(8,0);
    lcd.write(byte(0));
    lcd.setCursor(12,0);
    lcd.write(byte(1));
    lcd.setCursor(4,1);
    lcd.write(byte(0));
    lcd.setCursor(8,1);
    lcd.write(byte(0));
    lcd.setCursor(12,1);
    lcd.write(byte(0));
    break;
    
    case 3:
    lcd.setCursor(4,0);
    lcd.write(byte(0));
    lcd.setCursor(8,0);
    lcd.write(byte(0));
    lcd.setCursor(12,0);
    lcd.write(byte(0));
    lcd.setCursor(4,1);
    lcd.write(byte(1));
    lcd.setCursor(8,1);
    lcd.write(byte(0));
    lcd.setCursor(12,1);
    lcd.write(byte(0));
    break;

    case 4:
    lcd.setCursor(4,0);
    lcd.write(byte(0));
    lcd.setCursor(8,0);
    lcd.write(byte(0));
    lcd.setCursor(12,0);
    lcd.write(byte(0));
    lcd.setCursor(4,1);
    lcd.write(byte(0));
    lcd.setCursor(8,1);
    lcd.write(byte(1));
    lcd.setCursor(12,1);
    lcd.write(byte(0));
    break;

    case 5:
    lcd.setCursor(4,0);
    lcd.write(byte(0));
    lcd.setCursor(8,0);
    lcd.write(byte(0));
    lcd.setCursor(12,0);
    lcd.write(byte(0));
    lcd.setCursor(4,1);
    lcd.write(byte(0));
    lcd.setCursor(8,1);
    lcd.write(byte(0));
    lcd.setCursor(12,1);
    lcd.write(byte(1));
    break;
   }
lcd.setCursor(0,0);
lcd.print("DnD");
lcd.setCursor(0,1);
lcd.print(deger);
 lcd.setCursor(5,0);
 lcd.print("D4");
 lcd.setCursor(9,0);
 lcd.print("D6");
 lcd.setCursor(13,0);
 lcd.print("D8");
 lcd.setCursor(5,1);
 lcd.print("D10");
 lcd.setCursor(9,1);
 lcd.print("D12");
 lcd.setCursor(13,1);
 lcd.print("D20");

 ///////////////////////////////////////////////Buton Okuma
  int x = analogRead(A0);
  int y = analogRead(A1);
  buttonState = digitalRead(button);
if (x>700)  // Yön okuma
{ butonasagi(); }
if (x<300)
{ butonyukari(); }
if (y>700)
{ sol(); }
if (y<300)
{ sag();}
if (buttonState==LOW)
{ buton(); }
delay(60);
lcd.clear();



}

void butonasagi() 
{
switch (secim)
{
  case 0:
  secim=3;
  break; 
  case 1:
  secim=4;
  break;
  case 2:
  secim=5;
  break;
  delay(200);
  }
}

void butonyukari()
{
{
  switch (secim)
  {
  case 3:
  secim=0;
  break; 
  case 4:
  secim=1;
  break;
  case 5:
  secim=2;
  break;
  }
  delay(200);
  }
}

void sag()
{
  if (secim<5)
secim++;
delay(200);
}


void sol()
{
if (secim>0)
secim--;
delay(200);
}

void buton()
{
  delay(200);

 switch(secim)
 {
  case 0: //d4
  deger=random(1,5);
  break;
  case 1: //d6
  deger=random(1,7);
  break;
  case 2: //d8
  deger=random(1,9);
  break;
  case 3: //d10
  deger=random(1,11);
  break;
  case 4: //d12
  deger=random(1,13);
  break;
  case 5: //d20
  deger=random(1,21);
  break;
 }

}

