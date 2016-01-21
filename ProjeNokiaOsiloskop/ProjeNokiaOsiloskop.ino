#include <SPI.h>


#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// pin 2 - Serial clock out (SCLK)
// pin 3 - Serial data out (DIN)
// pin 4 - Data/Command select (D/C)
// pin 5 - LCD chip select (CS)
// pin 6 - LCD reset (RST)
Adafruit_PCD8544 nokia = Adafruit_PCD8544(2, 3, 4, 5, 6);

// a bitmap of a 16x16 fruit icon
const unsigned char __attribute__ ((progmem)) logo16_glcd_bmp[]={
  0x06, 0x0D, 0x29, 0x22, 0x66, 0x24, 0x00, 0x01, 0x87, 0x00, 0x27, 0x6C, 0x20, 0x23, 0x06, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };
#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

int channelAI = A1;     
int scaleYAI = A2;       
int scaleXAI = A3;     
int offsetXAI = A4;       
int delayVariable = 0;  
int xVariable = 0;       
int yCtr = 0;            
int posy = 0;           
int myArray[85];         
int offsetX = 0;
int fiveV = 1023;


void setup(void) 
{

  nokia.begin();
  nokia.setContrast(50);


  nokia.display();
  delay(500);
  nokia.clearDisplay();
}

void loop() 
{  
  delayVariable = analogRead(scaleYAI);
  delayVariable = (delayVariable);
  delayVariable = map (delayVariable, 0, 1023, 0, 10);
  xVariable = analogRead(scaleXAI);
  xVariable = map (xVariable, 0, 1023, 0, 100); 
  offsetX = analogRead(offsetXAI);
  offsetX = map(offsetX, 0, 1023, -100, 100);

  for(yCtr = 0; yCtr < 43; yCtr += 1)  
  {                                 
    posy = analogRead(channelAI);     
    posy = map (posy, 0, 1023, 1023, 0); 
    myArray[yCtr] = (posy/xVariable);      
    delay (delayVariable);          
  }

  yCtr == 0;                       
  nokia.clearDisplay();                      

  for(yCtr = 0; yCtr < 43; yCtr += 1)  
  {
    nokia.drawLine((yCtr*2)-2, myArray[yCtr-1]-offsetX, yCtr*2, myArray[yCtr]-offsetX, BLACK); 

  }
  yCtr == 0;
  
  for(yCtr = 0; yCtr < 85; yCtr += 3){
    nokia.drawPixel(yCtr, (fiveV/xVariable)-offsetX, BLACK); 
    nokia.drawPixel(yCtr, (fiveV/xVariable/2)-offsetX, BLACK); 
    nokia.drawPixel(yCtr, 0-offsetX, BLACK); // Draw 0V Line
  }
  
  nokia.display();                     
  yCtr == 0;                          

} 


