/*
  Arduino Snake for VGA monitor - by Roberto Melzi. 
  Version 1.1 - October the 10th 2015
  with sound
  Arduino IDE 1.6.4 
*/

#include <VGAX.h>
#include <math.h>
#define FNT_NANOFONT_HEIGHT 6
#define FNT_NANOFONT_SYMBOLS_COUNT 95
#include <VGAXUtils.h>

#define BUTTON_1 A1 //digital 
#define BUTTON_2 A2 //digital 
#define BUTTON_3 A3 //digital 
#define BUTTON_4 A4 //digital 
// NB: pin A0 is used for the audio!

VGAX vga;
VGAXUtils vgaU;

//data size=570 bytes
const unsigned char fnt_nanofont_data[FNT_NANOFONT_SYMBOLS_COUNT][1+FNT_NANOFONT_HEIGHT] PROGMEM={
{ 1, 128, 128, 128, 0, 128, 0, }, //glyph '!' code=0
{ 3, 160, 160, 0, 0, 0, 0, }, //glyph '"' code=1
//{ 5, 80, 248, 80, 248, 80, 0, },  //glyph '#' code=2-
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
static const char str10[] PROGMEM="#"; 
static const char str20[] PROGMEM="Arduino VGA Snake"; 
static const char str21[] PROGMEM="by Roberto Melzi"; 
static const char str22[] PROGMEM="Game Over"; 
static const char str23[] PROGMEM="Score"; 

void setup() {
  vga.begin();
  //randomSeed(1); 
  randomSeed(analogRead(5)); 
}

boolean button1 = 0;
boolean button2 = 0;
boolean button3 = 0;
boolean button4 = 0;
boolean button; 
int counterMenu = 0;
int counterMenu2 = 0; 
int state = 1;
int score = 0; 
int scoreMax = 9; 
int foodX = 60; 
int foodY = 30;
int sx[31];
int sy[31];
int slength = 3;
int wleft = 36; 
int i;
int x; 
int y; 
int direct = 3; 
int speedDelay = 100; 

void foodIni() {
  foodX = random(VGAX_WIDTH - 4 - wleft) + 2 + wleft;  
  foodY = random(VGAX_HEIGHT - 4) + 2;
  // ------------ choose the following for food up to the border ----------------------------------------- 
  // foodX = random(VGAX_WIDTH - 2 - wleft) + 1 + wleft;  
  // foodY = random(VGAX_HEIGHT - 2) + 1;
}

void processInputs() {
  button1 = digitalRead(BUTTON_1); 
  button2 = digitalRead(BUTTON_2);
  button3 = digitalRead(BUTTON_3); 
  button4 = digitalRead(BUTTON_4);
  button = button1 | button2 | button3 | button4; 
}

void drawMenu() {
  counterMenu2++; 
  vga.delay(10); 
  if (counterMenu2 > 50){
    counterMenu++; 
    vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str20, 26, 16, (counterMenu%3) + 1);
    vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str21, 28, 28, (counterMenu%3) + 1);
    counterMenu2 = 0; 
  }
}

void drawBorder() {
    vgaU.draw_line(wleft, 0, VGAX_WIDTH-1, 0, 3);
    vgaU.draw_line(wleft, VGAX_HEIGHT-1, VGAX_WIDTH-1, VGAX_HEIGHT-1, 3);
    vgaU.draw_line(wleft, 0, wleft, VGAX_HEIGHT-1, 3);
    vgaU.draw_line(VGAX_WIDTH-1, 0, VGAX_WIDTH-1, VGAX_HEIGHT, 3);
}

void drawScore() {
  vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str23, 10, 3, 2);
  vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str10, 20, 10, 0);
  if (score == 0) {vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str0, 20, 10, 2);}
  if (score == 1) {vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str1, 20, 10, 2);}
  if (score == 2) {vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str2, 20, 10, 2);}
  if (score == 3) {vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str3, 20, 10, 2);}
  if (score == 4) {vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str4, 20, 10, 2);}
  if (score == 5) {vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str5, 20, 10, 2);}
  if (score == 6) {vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str6, 20, 10, 2);}
  if (score == 7) {vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str7, 20, 10, 2);}
  if (score == 8) {vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str8, 20, 10, 2);}
  if (score == 9) {vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str9, 20, 10, 2);}
  if (score == 10) {vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str0, 20, 10, 2);}
  if (score == 11) {vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str1, 20, 10, 2);}
}

// this is for the beginning game window ---------------------------------------------------------------------------------------
void drawStartScreen() {
   vga.clear(0);
   drawBorder(); 
   drawSnakeIni(); 
   drawScore(); 
   button = 0;
   vga.delay(200);
} 

void drawSnakeIni() {
   for (int i = 0; i < slength ; i++) {
      sx[i] = 80 + i;
      sy[i] = 30; 
      vga.putpixel(sx[i], sy[i], 2);
   }
   vga.putpixel(foodX, foodY, 1);
}

// re-inizialize new match -------------------------------------------------------------------------------------------------------
void newMatch(){
  score = 0;
  slength = 3; 
  i = slength - 1;  
  vga.clear(0);  
  drawBorder();
  drawScore(); 
  vga.putpixel(foodX, foodY, 1);
}

// This is the main loop of the game ------------------------------------------------------------
void loop() {
  
  processInputs(); 
  
  if(state == 1) { 
     drawMenu();
     vga.delay(10);
     processInputs(); 
     if (button == 1){ 
        button = 0;
        vga.clear(0);
        drawStartScreen(); 
        state = 2; 
     }
  }
  
 if(state == 2){
     if(score == scoreMax || score == 0){
        processInputs(); 
     }
     if (button == 1){ 
        score = 0;
        drawScore(); 
        button = 0;
        button1 = 0;
        button2 = 0;
        button3 = 0;
        button4 = 0;
        direct = 3; 
        x = -1;
        y = 0; 
        i = slength - 1; 
        state = 3; 
     }
  }
  
  if(state == 3) { 

     processInputs(); 
    
//-------------------- change direction --------------------------------------------
     if (direct == 1){
        if (button2 == 1){ x = 0; y = -1; direct = 2; button4 = 0;}
        if (button4 == 1){ x = 0; y = +1; direct = 4;}
     }
     else {
        if (direct == 2){
           if (button1 == 1){ x = +1; y = 0; direct = 1; button3 = 0;}
           if (button3 == 1){ x = -1; y = 0; direct = 3;}
        }
        else {
           if (direct == 3){
              if (button2 == 1){ x = 0; y = -1; direct = 2; button4 = 0;}
              if (button4 == 1){ x = 0; y = +1; direct = 4;}
           }
           else { 
              if (direct == 4){
                 if (button1 == 1){ x = +1; y = 0; direct = 1; button3 = 0;}
                 if (button3 == 1){ x = -1; y = 0; direct = 3;}
              }
           }
        }
     }

//----------------------- delete tail --------------------------------------     
     vga.putpixel(sx[i], sy[i], 0);
     if ( i == slength - 1){
        sx[i] = sx[0] + x; 
        sy[i] = sy[0] + y; 
     }
     else {
        sx[i] = sx[i + 1] + x; 
        sy[i] = sy[i + 1] + y; 
     }

//--------------------- out from border ------------------------------------    
/*
     if(sx[i] < wleft + 1) {sx[i] = VGAX_WIDTH - 2;}
     if(sx[i] > VGAX_WIDTH - 2) {sx[i] = wleft + 1;}
     if(sy[i] < 1) {sy[i] = VGAX_HEIGHT - 2;}
     if(sy[i] > VGAX_HEIGHT - 2) {sy[i] = 1;}
*/     
//--------------------- check eating food -----------------------------------
     if ( sx[i] == foodX && sy[i] == foodY){ 
     //if (vga.getpixel(sx[i], sy[i]) == 1 ){
        vga.tone(660);  
        vga.delay(30); 
        vga.noTone(); 
        foodIni(); 
        vga.putpixel(foodX, foodY, 1);
        slength = slength + 3; 
        score++; 
        if (score > scoreMax) {
           speedDelay = speedDelay - 20;
           vga.tone(880);  
           vga.delay(30); 
           vga.noTone(); 
           newMatch();
        }
        drawScore(); 
     }

//----------------------- increase head and Game Over -------------------------------------
     if (vga.getpixel(sx[i], sy[i]) == 0 || vga.getpixel(sx[i], sy[i]) == 1 ){
        vga.putpixel(sx[i], sy[i], 2); 
     }
     else //------------------ Game Over --------------------------------------------------
     {
        vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str22, 58, 24, 1);
        vga.delay(300);
        vga.tone(660); 
        vga.delay(200);
        vga.tone(330);
        vga.delay(200);
        vga.tone(165); 
        vga.delay(200);
        vga.tone(82);
        vga.delay(200);
        vga.noTone(); 
        //vga.delay(1000); 
        button == 0; 
        while(button == 0){processInputs();}
        speedDelay = 100; 
        newMatch();
        drawSnakeIni();
     }
     
     i--;
     if ( i < 0){i = slength - 1;}
 
     vga.delay(speedDelay); 

  }
} 

