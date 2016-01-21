#include <SPI.h>
#include <ILI9341_due_config.h>
#include <ILI9341_due.h>

#include "fonts\Arial_bold_14.h"

#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 8

ILI9341_due tft = ILI9341_due(TFT_CS, TFT_DC, TFT_RST);
String yazi = "";
void setup()
{
	Serial.begin(9600); // Hata Ayıklama için

	bool result = tft.begin();
	Serial.println("Arduino ILI9341 Seri Port Goruntuleme Ekranina Hos Geldiniz");
	Serial.print("TFT EKRAN DURUMU : ");
	Serial.println(result ? "HAZIR" : "TANINMADI");
  Serial.println("************************************************");
  Serial.println("Kullanim: Yazacaginiz kadar yaziyi yazdiktan sonra ekrana yazdirmak icin '1' karakterini yazin");
  Serial.println("Eger Ekrandaki Yaziyi silmek isterseniz '2' karakterine basin. Kolay Gelsin. "); 
  Serial.println("************************************************");
 tft.fillScreen(ILI9341_DARKBLUE);
 
 tft.setRotation(iliRotation90);
 tft.drawLine(5, 5, 310, 5, ILI9341_WHITE);
 tft.drawLine(5, 230, 310, 230, ILI9341_WHITE); 
 tft.drawLine(5, 5, 5, 230, ILI9341_WHITE);
 tft.drawLine(310, 5, 310, 230, ILI9341_WHITE);

}

void loop()
{
 tft.setTextColor(ILI9341_WHITE, ILI9341_DARKBLUE);
 gTextArea textArea{ 10, 10, 300, 210 };
 tft.setTextArea(textArea);
  if (Serial.available() > 0)
  {
 char karakter = Serial.read();
 if(karakter == '1') 
 yazdir();
 else if(karakter == '2')
 tft.clearTextArea();
 else 
 yazi += karakter; 


  }

}

void yazdir()
{
  tft.setFont(Arial_bold_14);
  tft.clearTextArea();
  tft.print(yazi);
  Serial.print("YAZDIRILDI: ");
  Serial.println(yazi);
  yazi="";
}



