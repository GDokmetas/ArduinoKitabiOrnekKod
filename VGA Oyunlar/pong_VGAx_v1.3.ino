/*
 Arduino Pong for VGA output - Version 1.3
 written by Roberto Melzi - October the 6th, 2015 
 Arduino software version: 1.6.4 

 Main differencees from version 1.0:
 
    1) two separate paddles for Left and Right players 
    2) newest VGAx libraries used, thus "print" has to be renamed to "printPROGMEM "
    3) minor bugs fixed 
    
 Main differences from version 1.1:
 
    1) faster analogRead()

    By default, analogRead() takes about 100 microseconds to read an analog input.
    The reason is because there is a "prescalar factor" equal to 128 which set the clock frequency of analogRead() at about 125 kHz. 
    Reducing this factor to 16 (for instance) with the following instructions, there is a reading every 18 us (56 kHz). 
    With a prescalar factor equal to 4, there is a reading every 8 us, loosing some precision. With a P.F. = 2 it seems it does not work. 
    A better description can be found here: 
    http://www.microsmart.co.za/technical/2014/03/01/advanced-arduino-adc/

 See it running on YouTube: "Arduino VGA Pong (with colors)" 
 https://www.youtube.com/watch?v=mrRGosn48gw
 VGAx Library By Sandro Maffiodo (version downloaded on August the 17th 2015) here:
 https://github.com/smaffer/vgax
 Post on the Arduino forum:
 http://forum.arduino.cc/index.php?topic=328631.0
 at position #8
*/

#include <VGAX.h>
#include <math.h>
#define FNT_NANOFONT_HEIGHT 6
#define FNT_NANOFONT_SYMBOLS_COUNT 95
#include <VGAXUtils.h>

#define WHEEL_ONE_PIN 3 //analog
#define WHEEL_TWO_PIN 1 //analog
#define BUTTON_ONE_PIN A4 //digital 
#define BUTTON_TWO_PIN A2 //digital 
// NB: pin A0 is used for the audio!

#define PADDLE_HEIGHT 8
#define PADDLE_WIDTH 2
#define RIGHT_PADDLE_X (VGAX_WIDTH-4)
#define LEFT_PADDLE_X 2
#define MAX_Y_VELOCITY 0.1

// Define various ADC prescaler
const unsigned char PS_2 = (1 << ADPS0);
const unsigned char PS_4 = (1 << ADPS1);
const unsigned char PS_8 = (1 << ADPS1 | 1 << ADPS0);
const unsigned char PS_16 = (1 << ADPS2);
const unsigned char PS_32 = (1 << ADPS2) | (1 << ADPS0);
const unsigned char PS_64 = (1 << ADPS2) | (1 << ADPS1);
const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

VGAX vga;
VGAXUtils vgaU;

//data size=570 bytes
const unsigned char fnt_nanofont_data[FNT_NANOFONT_SYMBOLS_COUNT][1+FNT_NANOFONT_HEIGHT] PROGMEM={
{ 1, 128, 128, 128, 0, 128, 0, }, //glyph '!' code=0
{ 3, 160, 160, 0, 0, 0, 0, }, //glyph '"' code=1
//{ 5, 80, 248, 80, 248, 80, 0, },  //glyph '#' code=2
{ 5, 248, 248, 248, 248, 248, 0, },  //glyph '#' code=2 - full rectangle
{ 5, 120, 160, 112, 40, 240, 0, },  //glyph '$' code=3
{ 5, 136, 16, 32, 64, 136, 0, },  //glyph '%' code=4
{ 5, 96, 144, 104, 144, 104, 0, },  //glyph '&' code=5
{ 2, 128, 64, 0, 0, 0, 0, },  //glyph ''' code=6
{ 2, 64, 128, 128, 128, 64, 0, }, //glyph '(' code=7
{ 2, 128, 64, 64, 64, 128, 0, },  //glyph ')' code=8
{ 3, 0, 160, 64, 160, 0, 0, },  //glyph '*' code=9
{ 3, 0, 64, 224, 64, 0, 0, }, //glyph '+' code=10
{ 2, 0, 0, 0, 0, 128, 64, },  //glyph ',' code=11
{ 3, 0, 0, 224, 0, 0, 0, }, //glyph '-' code=12
{ 1, 0, 0, 0, 0, 128, 0, }, //glyph '.' code=13
{ 5, 8, 16, 32, 64, 128, 0, },  //glyph '/' code=14
{ 4, 96, 144, 144, 144, 96, 0, }, //glyph '0' code=15
{ 3, 64, 192, 64, 64, 224, 0, },  //glyph '1' code=16
{ 4, 224, 16, 96, 128, 240, 0, }, //glyph '2' code=17
{ 4, 224, 16, 96, 16, 224, 0, },  //glyph '3' code=18
{ 4, 144, 144, 240, 16, 16, 0, }, //glyph '4' code=19
{ 4, 240, 128, 224, 16, 224, 0, },  //glyph '5' code=20
{ 4, 96, 128, 224, 144, 96, 0, }, //glyph '6' code=21
{ 4, 240, 16, 32, 64, 64, 0, }, //glyph '7' code=22
{ 4, 96, 144, 96, 144, 96, 0, },  //glyph '8' code=23
{ 4, 96, 144, 112, 16, 96, 0, },  //glyph '9' code=24
{ 1, 0, 128, 0, 128, 0, 0, }, //glyph ':' code=25
{ 2, 0, 128, 0, 0, 128, 64, },  //glyph ';' code=26
{ 3, 32, 64, 128, 64, 32, 0, }, //glyph '<' code=27
{ 3, 0, 224, 0, 224, 0, 0, }, //glyph '=' code=28
{ 3, 128, 64, 32, 64, 128, 0, },  //glyph '>' code=29
{ 4, 224, 16, 96, 0, 64, 0, },  //glyph '?' code=30
{ 4, 96, 144, 176, 128, 112, 0, },  //glyph '@' code=31
{ 4, 96, 144, 240, 144, 144, 0, },  //glyph 'A' code=32
{ 4, 224, 144, 224, 144, 224, 0, }, //glyph 'B' code=33
{ 4, 112, 128, 128, 128, 112, 0, }, //glyph 'C' code=34
{ 4, 224, 144, 144, 144, 224, 0, }, //glyph 'D' code=35
{ 4, 240, 128, 224, 128, 240, 0, }, //glyph 'E' code=36
{ 4, 240, 128, 224, 128, 128, 0, }, //glyph 'F' code=37
{ 4, 112, 128, 176, 144, 112, 0, }, //glyph 'G' code=38
{ 4, 144, 144, 240, 144, 144, 0, }, //glyph 'H' code=39
{ 3, 224, 64, 64, 64, 224, 0, },  //glyph 'I' code=40
{ 4, 240, 16, 16, 144, 96, 0, },  //glyph 'J' code=41
{ 4, 144, 160, 192, 160, 144, 0, }, //glyph 'K' code=42
{ 4, 128, 128, 128, 128, 240, 0, }, //glyph 'L' code=43
{ 5, 136, 216, 168, 136, 136, 0, }, //glyph 'M' code=44
{ 4, 144, 208, 176, 144, 144, 0, }, //glyph 'N' code=45
{ 4, 96, 144, 144, 144, 96, 0, }, //glyph 'O' code=46
{ 4, 224, 144, 224, 128, 128, 0, }, //glyph 'P' code=47
{ 4, 96, 144, 144, 144, 96, 16, },  //glyph 'Q' code=48
{ 4, 224, 144, 224, 160, 144, 0, }, //glyph 'R' code=49
{ 4, 112, 128, 96, 16, 224, 0, }, //glyph 'S' code=50
{ 3, 224, 64, 64, 64, 64, 0, }, //glyph 'T' code=51
{ 4, 144, 144, 144, 144, 96, 0, },  //glyph 'U' code=52
{ 3, 160, 160, 160, 160, 64, 0, },  //glyph 'V' code=53
{ 5, 136, 168, 168, 168, 80, 0, },  //glyph 'W' code=54
{ 4, 144, 144, 96, 144, 144, 0, },  //glyph 'X' code=55
{ 3, 160, 160, 64, 64, 64, 0, },  //glyph 'Y' code=56
{ 4, 240, 16, 96, 128, 240, 0, }, //glyph 'Z' code=57
{ 2, 192, 128, 128, 128, 192, 0, }, //glyph '[' code=58
{ 5, 128, 64, 32, 16, 8, 0, },  //glyph '\' code=59
{ 2, 192, 64, 64, 64, 192, 0, },  //glyph ']' code=60
{ 5, 32, 80, 136, 0, 0, 0, }, //glyph '^' code=61
{ 4, 0, 0, 0, 0, 240, 0, }, //glyph '_' code=62
{ 2, 128, 64, 0, 0, 0, 0, },  //glyph '`' code=63
{ 3, 0, 224, 32, 224, 224, 0, },  //glyph 'a' code=64
{ 3, 128, 224, 160, 160, 224, 0, }, //glyph 'b' code=65
{ 3, 0, 224, 128, 128, 224, 0, }, //glyph 'c' code=66
{ 3, 32, 224, 160, 160, 224, 0, },  //glyph 'd' code=67
{ 3, 0, 224, 224, 128, 224, 0, }, //glyph 'e' code=68
{ 2, 64, 128, 192, 128, 128, 0, },  //glyph 'f' code=69
{ 3, 0, 224, 160, 224, 32, 224, },  //glyph 'g' code=70
{ 3, 128, 224, 160, 160, 160, 0, }, //glyph 'h' code=71
{ 1, 128, 0, 128, 128, 128, 0, }, //glyph 'i' code=72
{ 2, 0, 192, 64, 64, 64, 128, },  //glyph 'j' code=73
{ 3, 128, 160, 192, 160, 160, 0, }, //glyph 'k' code=74
{ 1, 128, 128, 128, 128, 128, 0, }, //glyph 'l' code=75
{ 5, 0, 248, 168, 168, 168, 0, }, //glyph 'm' code=76
{ 3, 0, 224, 160, 160, 160, 0, }, //glyph 'n' code=77
{ 3, 0, 224, 160, 160, 224, 0, }, //glyph 'o' code=78
{ 3, 0, 224, 160, 160, 224, 128, }, //glyph 'p' code=79
{ 3, 0, 224, 160, 160, 224, 32, },  //glyph 'q' code=80
{ 3, 0, 224, 128, 128, 128, 0, }, //glyph 'r' code=81
{ 2, 0, 192, 128, 64, 192, 0, },  //glyph 's' code=82
{ 3, 64, 224, 64, 64, 64, 0, }, //glyph 't' code=83
{ 3, 0, 160, 160, 160, 224, 0, }, //glyph 'u' code=84
{ 3, 0, 160, 160, 160, 64, 0, },  //glyph 'v' code=85
{ 5, 0, 168, 168, 168, 80, 0, },  //glyph 'w' code=86
{ 3, 0, 160, 64, 160, 160, 0, },  //glyph 'x' code=87
{ 3, 0, 160, 160, 224, 32, 224, },  //glyph 'y' code=88
{ 2, 0, 192, 64, 128, 192, 0, },  //glyph 'z' code=89
{ 3, 96, 64, 192, 64, 96, 0, }, //glyph '{' code=90
{ 1, 128, 128, 128, 128, 128, 0, }, //glyph '|' code=91
{ 3, 192, 64, 96, 64, 192, 0, },  //glyph '}' code=92
{ 3, 96, 192, 0, 0, 0, 0, },  //glyph '~' code=93
{ 4, 48, 64, 224, 64, 240, 0, },  //glyph '£' code=94
};

static const char str0[] PROGMEM="0"; 
static const char str1[] PROGMEM="1"; 
static const char str2[] PROGMEM="2"; 
static const char str3[] PROGMEM="3"; 
static const char str4[] PROGMEM="4"; 
static const char str5[] PROGMEM="5"; 
static const char str6[] PROGMEM="6"; 
static const char str7[] PROGMEM="7"; 
static const char str8[] PROGMEM="8"; 
static const char str9[] PROGMEM="9"; 
static const char str20[] PROGMEM="#"; 
static const char str10[] PROGMEM="Arduino VGA Pong"; 
static const char str11[] PROGMEM="by Roberto Melzi"; 
static const char str15[] PROGMEM="Red wins!"; 
static const char str16[] PROGMEM="Green wins!"; 
static const char str21[] PROGMEM="########";

void setup() {
  //Serial.begin(9600); 
  vga.begin();
  randomSeed(1);  

  // set up the ADC
  ADCSRA &= ~PS_128;  // remove bits set by Arduino library
  // you can choose a prescaler from above.
  // PS_16, PS_32, PS_64 or PS_128
  ADCSRA |= PS_4;    // set our own prescaler to 4. N.B. PS_2 does not work!!! 

}

unsigned char x,y;
boolean buttonStatus = 0;
boolean buttonOneStatus = 0;
boolean buttonTwoStatus = 0;
int wheelOnePosition; 
int wheelTwoPosition;
int counterMenu = 0;
int counterMenu2 = 0; 
int state = 1;
int rightPaddleY;
int leftPaddleY;
int rightPaddleY0 = 20;
int leftPaddleY0 = 20;
int ballX = 4;
int ballY = 20;
int ballX0 = 20;
int ballY0 = 20; 
float ballPX = 20;
float ballPY = 20; 
float ballVx;
float ballVy;
int frame = 0;
int scoreR = 0;
int scoreL = 0; 
int scoreMax = 8; 
boolean PaddleHit = 0; 

void parameterIni() {
  ballVx = random(50., 80.)/500. + (scoreL + scoreR)/35;  
  ballVy = random(40.)/1000. - 0.02;
}

void processInputs() {
  buttonOneStatus = digitalRead(BUTTON_ONE_PIN); 
  buttonTwoStatus = digitalRead(BUTTON_TWO_PIN);
  wheelOnePosition = analogRead(WHEEL_ONE_PIN);
  wheelTwoPosition = analogRead(WHEEL_TWO_PIN);
  buttonStatus = buttonOneStatus || buttonTwoStatus;  
}

void drawMenu() {
  counterMenu2++; 
  vga.delay(10); 
  if (counterMenu2 > 50){
    counterMenu++; 
    vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str10, 26, 16, (counterMenu%3) + 1);
    vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str11, 28, 28, (counterMenu%3) + 1);
    counterMenu2 = 0; 
  }
}

void drawBorder() {
    vgaU.draw_line(0,0,VGAX_WIDTH-1,0,3);
    vgaU.draw_line(0,VGAX_HEIGHT-1,VGAX_WIDTH-1,VGAX_HEIGHT-1,3);
    vgaU.draw_line(0,0,0,VGAX_HEIGHT-1,3);
    vgaU.draw_line(VGAX_WIDTH-1,0,VGAX_WIDTH-1,VGAX_HEIGHT,3);
}

void drawScore() {
    vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str20, 52, 4, 0);
    vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str20, 64, 4, 0); 
    if(scoreL == 0) {vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str0, 52, 4, 1);}
    if(scoreR == 0) {vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str0, 64, 4, 2);}
    if(scoreL == 1) {vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str1, 52, 4, 1);}
    if(scoreR == 1) {vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str1, 64, 4, 2);}
    if(scoreL == 2) {vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str2, 52, 4, 1);}
    if(scoreR == 2) {vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str2, 64, 4, 2);}
    if(scoreL == 3) {vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str3, 52, 4, 1);}
    if(scoreR == 3) {vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str3, 64, 4, 2);}
    if(scoreL == 4) {vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str4, 52, 4, 1);}
    if(scoreR == 4) {vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str4, 64, 4, 2);}
    if(scoreL == 5) {vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str5, 52, 4, 1);}
    if(scoreR == 5) {vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str5, 64, 4, 2);}
    if(scoreL == 6) {vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str6, 52, 4, 1);}
    if(scoreR == 6) {vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str6, 64, 4, 2);}
    if(scoreL == 7) {vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str7, 52, 4, 1);}
    if(scoreR == 7) {vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str7, 64, 4, 2);}
    
    if(scoreL == scoreMax) {
       vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str8, 52, 4, 1);
       vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str15, 12, 24, 1);
       ballX = VGAX_WIDTH - 6; 
       buttonStatus = 0; 
       while(buttonStatus == 0){
          processInputs(); 
          ballY = ((wheelOnePosition / 8) * (VGAX_HEIGHT-PADDLE_HEIGHT-1))/ 128 + 4;
          drawGameScreen(); 
       }
       parameterIni();
       drawStartScreen(); 
       state = 2; 
    }
    if(scoreR == scoreMax) {
       vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str8, 64, 4, 2);
       vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str16, 66, 24, 2);
       ballX = 4; 
       buttonStatus = 0; 
       while(buttonStatus == 0){
          processInputs(); 
          ballY = ((wheelTwoPosition / 8) * (VGAX_HEIGHT-PADDLE_HEIGHT-1))/ 128 + 4;
          drawGameScreen(); 
       }
       parameterIni();
       drawStartScreen(); 
       state = 2; 
    }
}

// this is for the beginning game window ---------------------------------------------------------------------------------------
void drawStartScreen() {
   //vga.clear(0);
   vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str20, 52, 4, 0);
   vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str20, 64, 4, 0); 
   vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str0, 52, 4, 1);
   vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str0, 64, 4, 2);
   vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str21, 12, 24, 0);
   vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str21, 66, 24, 0);
   vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str21, 11, 24, 0);
   vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str21, 65, 24, 0);
   drawBorder(); 
   drawGameScreen(); 
   buttonStatus = 0;
   vga.delay(200);
} 

// this is the main function to draw the game screen ----------------------------------------------------------------------------
void drawGameScreen() {
    
    //draw right paddle
    rightPaddleY = ((wheelOnePosition / 8) * (VGAX_HEIGHT-PADDLE_HEIGHT-1))/ 128 + 1;
    x = RIGHT_PADDLE_X; 
    if (rightPaddleY != rightPaddleY0 || PaddleHit == 1){
      vgaU.draw_line(x,rightPaddleY0,x,rightPaddleY0+PADDLE_HEIGHT,0);
      vgaU.draw_line(x+1,rightPaddleY0,x+1,rightPaddleY0+PADDLE_HEIGHT,0);
      vgaU.draw_line(x,rightPaddleY,x,rightPaddleY+PADDLE_HEIGHT,2);
      vgaU.draw_line(x+1,rightPaddleY,x+1,rightPaddleY+PADDLE_HEIGHT,2);
    }
    
    //draw left paddle
    leftPaddleY = ((wheelTwoPosition / 8) * (VGAX_HEIGHT-PADDLE_HEIGHT-1))/ 128 + 1;
    x = LEFT_PADDLE_X;
    if (leftPaddleY != leftPaddleY0 || PaddleHit == 1){
       vgaU.draw_line(x,leftPaddleY0,x,leftPaddleY0+PADDLE_HEIGHT,0);
       vgaU.draw_line(x+1,leftPaddleY0,x+1,leftPaddleY0+PADDLE_HEIGHT,0);
       vgaU.draw_line(x,leftPaddleY,x,leftPaddleY+PADDLE_HEIGHT,1);
       vgaU.draw_line(x+1,leftPaddleY,x+1,leftPaddleY+PADDLE_HEIGHT,1);
    }
    
    //draw net
    for(int i=1; i<VGAX_HEIGHT - 4; i+=6) {
      vgaU.draw_line(VGAX_WIDTH/2,i,VGAX_WIDTH/2,i+3, 3);
    }
     
    //draw ball
    if ((ballX != ballX0) || (ballY != ballY0)){
       vga.putpixel(ballX0, ballY0, 0);
       vga.putpixel(ballX0, ballY0 + 1, 0);
       vga.putpixel(ballX0 + 1, ballY0, 0);
       vga.putpixel(ballX0 + 1, ballY0 + 1, 0);
       vga.putpixel(ballX, ballY, 3);
       vga.putpixel(ballX, ballY + 1, 3);
       vga.putpixel(ballX + 1, ballY, 3);
       vga.putpixel(ballX + 1, ballY + 1, 3);
    }

    ballX0 = ballX;
    ballY0 = ballY; 
    leftPaddleY0 = leftPaddleY;
    rightPaddleY0 = rightPaddleY; 
}

// This is the main loop of the game ------------------------------------------------------------
void loop() {
  
  processInputs(); 
  
  if(state == 1) { 
     drawMenu();
     vga.delay(10);
     processInputs(); 
     if (buttonStatus == 1){ 
        buttonStatus = 0;
        vga.clear(0);
        ballY = ((wheelTwoPosition / 8) * (VGAX_HEIGHT-PADDLE_HEIGHT-1))/ 128 + 4;
        drawStartScreen(); 
        state = 2; 
     }
  }
  
 if(state == 2){
     //buttonStatus = 0; 
     if(scoreR == scoreMax || scoreR == 0){
        processInputs(); 
        ballY = ((wheelTwoPosition / 8) * (VGAX_HEIGHT-PADDLE_HEIGHT-1))/ 128 + 4;
        drawGameScreen(); 
     }
     if(scoreL == scoreMax){
        processInputs(); 
        ballY = ((wheelOnePosition / 8) * (VGAX_HEIGHT-PADDLE_HEIGHT-1))/ 128 + 4;
        drawGameScreen(); 
     }
     if (buttonStatus == 1){ 
        ballPX = ballX; 
        ballPY = ballY;
        parameterIni(); 
        scoreL = 0;
        scoreR = 0;
        drawScore(); 
        buttonStatus = 0;
        state = 3; 
     }
  }
  
  if(state == 3) { 
    
     ballPX += ballVx;
     ballPY += ballVy;
     ballX = int(ballPX);
     ballY = int(ballPY);
    
     if(ballPY <= 1 || ballPY >= VGAX_HEIGHT - 2 ) {
        ballVy = -ballVy;
        ballPY += ballVy;
        ballY = int(ballPY);
        vga.tone(880);
        vga.delay(30); 
        vga.noTone(); 
     }; 
     
     // left paddle hit -------------------------------------------------
     if(ballVx < 0 && ballX == LEFT_PADDLE_X+PADDLE_WIDTH -1 && ballY >= leftPaddleY - 1 && ballY <= leftPaddleY + PADDLE_HEIGHT) { 
        ballVx = -ballVx;
        ballVy += 0.2 * ((ballY - leftPaddleY + 1) - (PADDLE_HEIGHT / 2)) / (PADDLE_HEIGHT / 2);
        vga.tone(660);  
        vga.delay(30); 
        vga.noTone(); 
        drawScore();
        PaddleHit = 1; 
     }
     //right paddle hit --------------------------------------------------
     if(ballVx > 0 && ballX == RIGHT_PADDLE_X - 1 && ballY >= rightPaddleY - 1 && ballY <= rightPaddleY + PADDLE_HEIGHT) { 
        ballVx = -ballVx;
        ballVy += 0.2 * ((ballY - rightPaddleY + 1) - (PADDLE_HEIGHT / 2)) / (PADDLE_HEIGHT / 2);
        vga.tone(660); 
        vga.delay(30); 
        vga.noTone(); 
        drawScore();
        PaddleHit = 1; 
     }
     
     //limit vertical speed
     if(ballVy > MAX_Y_VELOCITY) ballVy = MAX_Y_VELOCITY;
     if(ballVy < -MAX_Y_VELOCITY) ballVy = -MAX_Y_VELOCITY;
     
     if(ballX <= 0) { // ball out from left ------------------------------------------
        vga.tone(220);
        vga.delay(200); 
        vga.noTone(); 
        scoreR++; 
        drawScore();  
        ballX = 4;   
       PaddleHit = 1;  
        while(buttonTwoStatus == 0){
           processInputs(); 
           ballY = ((wheelTwoPosition / 8) * (VGAX_HEIGHT-PADDLE_HEIGHT-1))/ 128 + 4;
           drawGameScreen(); 
           PaddleHit = 0; 
        }
        ballPX = ballX; 
        ballPY = ballY;
        parameterIni(); 
        drawBorder();
     }
     if(ballX >= VGAX_WIDTH - 2) { // ball out from right ------------------------------------------
        vga.tone(220);
        vga.delay(200); 
        vga.noTone(); 
        scoreL++; 
        drawScore();      
        ballX = VGAX_WIDTH - 6;   
        PaddleHit = 1; 
        while(buttonOneStatus == 0){
           processInputs(); 
           ballY = ((wheelOnePosition / 8) * (VGAX_HEIGHT-PADDLE_HEIGHT-1))/ 128 + 4;
           drawGameScreen(); 
           PaddleHit = 0; 
        }
        ballPX = ballX; 
        ballPY = ballY;
        parameterIni(); 
        drawBorder(); 
        ballVx = -ballVx;
     }
          
     drawGameScreen(); 
     
     PaddleHit = 0; 
  }
}
