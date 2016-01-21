

#include <SPI.h>
#include "Ucglib.h"
Ucglib_ILI9341_18x240x320_SWSPI ucg(/*sclk=*/ 4, /*data=*/ 3, /*cd=*/ 6 , /*cs=*/ 7, /*reset=*/ 5);  
void setup(void)
{
  delay(1000);
  ucg.begin(UCG_FONT_MODE_TRANSPARENT);
  ucg.clearScreen();
}

void loop(void)
{
  //ucg.setRotate90();
  ucg.setFont(ucg_font_ncenR12_tr);
  ucg.setColor(200, 200, 255);
  ucg.setColor(1, 255, 0,0);
  
  ucg.setPrintPos(20,25);
  ucg.print("Merhaba Dunya!");

  delay(500);  
}
