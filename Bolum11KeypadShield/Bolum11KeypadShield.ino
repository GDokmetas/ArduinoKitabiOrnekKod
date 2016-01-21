
#include <LiquidCrystal.h>


// LCD Panelin kullanacağı LCD ayakları seçilir. Başka ayaklar seçmeyin. 
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// Düğme değerleri verilir. 
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

// Düğme okuma
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // Düğme değeri A0'dan analog olarak okunur. 
 //Düğmeden okunan ADC değerine göre program çalıştırılır.
 if (adc_key_in > 1000) return btnNONE; // Eğer hiç bir değer alınmıyorsa düğme boş bırakılır 
 // For V1.1 us this threshold
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 250)  return btnUP; 
 if (adc_key_in < 450)  return btnDOWN; 
 if (adc_key_in < 650)  return btnLEFT; 
 if (adc_key_in < 850)  return btnSELECT;  



 return btnNONE;  // Hiç biri olmadığında none döndürür. 
}

void setup()
{
 lcd.begin(16, 2);             
 lcd.setCursor(0,0);
 lcd.print("Dugmelere Basin"); // 
}
 
void loop()
{
 lcd.setCursor(9,1);            // İmleci 9,1'e getir 



 lcd.setCursor(0,1);            // İkinci satıra atla
 lcd_key = read_LCD_buttons();  // Düğmeleri oku

 switch (lcd_key)               // Hangi düğme basıldıysa ona göre işlem yap.
 {
   case btnRIGHT:
     {
     lcd.print("RIGHT ");
     break;
     }
   case btnLEFT:
     {
     lcd.print("LEFT   ");
     break;
     }
   case btnUP:
     {
     lcd.print("UP    ");
     break;
     }
   case btnDOWN:
     {
     lcd.print("DOWN  ");
     break;
     }
   case btnSELECT:
     {
     lcd.print("SELECT");
     break;
     }
     case btnNONE:
     {
     lcd.print("NONE  ");
     break;
     }
 }

}

