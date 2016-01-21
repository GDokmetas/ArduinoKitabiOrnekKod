// VGA_Tetris.beta.ino
//
// Arduino Tetris for VGA output - beta Version
// written by Roberto Melzi - December the 21th, 2015 
// Arduino software version: 1.6.4
//
// Version for 4:3 VGA monitor
//
// See it running on YouTube: "Arduino VGA Pong (with colors)" 
// https://www.youtube.com/watch?v=mrRGosn48gw
// VGAx Library By Sandro Maffiodo (version downloaded on August the 17th 2015) here:
// https://github.com/smaffer/vgax
// Post on the Arduino forum:
// http://forum.arduino.cc/index.php?topic=328631.0

#include <math.h>
#define FNT_NANOFONT_HEIGHT 6
#define FNT_NANOFONT_SYMBOLS_COUNT 95
#include <VGAXUtils.h>

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
static const char str10[] PROGMEM="#"; 
static const char str11[] PROGMEM="Arduino VGA Tetris"; 
static const char str12[] PROGMEM="by Roberto Melzi"; 
static const char str13[] PROGMEM="Game"; 
static const char str14[] PROGMEM="Over!"; 

void setup() {
  //Serial.begin(9600);
  vga.begin();
  randomSeed(analogRead(5)); 
}

boolean button = 0;
boolean button_1 = 0;
boolean button_2 = 0;
boolean button_3 = 0;
boolean button_4 = 0;
boolean button_5 = 0;
int block[4][2]={{0,0},{0,0},{0,0},{0,0}};
int blockExt[4][2]={{0,0},{0,0},{0,0},{0,0}};
int blockOld[4][2]={{0,0},{0,0},{0,0},{0,0}};
int blockTmp[4][2]={{0,0},{0,0},{0,0},{0,0}};
int blockTr[4][2]={{0,0},{0,0},{0,0},{0,0}};
int yLine[4] = {0,0,0,0}; 
int yLineTmp[4] = {0,0,0,0}; 
int yCounter = 0; 
int x = 60; 
int y = 6; 
int z = 10; 
int score; 
int noLoop = -1; 
int clock = 1; 
int delta = 0;  
int color = 1; 
int colorOld; 
int blockN; 
int blockNext; 
int busy; 
int noDelete = 0; 
int k = 0; 
int a = 40;
int b = 10; 
int counterMenu = 0; 
unsigned long time = 0;
int fast = 14; //14; 

void processInputs() { //button_5 = digitalRead(A5); can be added for clockwise rotation 
  if(button_1 == 1) {
     button_2 = digitalRead(A2);
     button_3 = digitalRead(A3); 
     button_4 = digitalRead(A4);
     button_1 = 0;
     vga.delay(25);
  }
  else{
     if(button_2 == 1) {
        button_1 = digitalRead(A1);
        button_3 = digitalRead(A3); 
        button_4 = digitalRead(A4);
        button_2 = 0;
        vga.delay(25);
     }
     else{
        if(button_3 == 1) {
           button_1 = digitalRead(A1);
           button_2 = digitalRead(A2); 
           button_4 = digitalRead(A4);
           button_3 = 0;
           vga.delay(25);
        }
        else{
           if(button_4 == 1) {
              button_1 = digitalRead(A1);
              button_2 = digitalRead(A2); 
              button_3 = digitalRead(A3);                                          
              button_4 = 0;
              //vga.delay(25);                                                                    
           }
           else{
              button_1 = digitalRead(A1); 
              button_2 = digitalRead(A2);
              button_3 = digitalRead(A3); 
              button_4 = digitalRead(A4);
           }
        }
     }
  }
  button = button_2 || button_4; 
}

void clearInputs() {
  button_1 = 0; 
  button_2 = 0;
  button_3 = 0; 
  button_4 = 0;
  button = 0; 
}

void drawMenu() {
  while (button_1 == 0 && button_2 == 0 && button_3 == 0 && button_4 == 0) {
     processInputs(); 
     vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str11, 26, 16, (counterMenu%3) + 1);
     vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str12, 28, 28, (counterMenu%3) + 1);
     vga.delay(1000);
     counterMenu++; 
  }
  vga.clear(0);
  drawGameScreen();
  drawScore(score);
}

void drawScore(int i) {
    if (i > 39){
       score = 0;
       i = 0; 
       fast = fast - 4; 
       if (fast < 3) {fast = 2;}
    }
    vgaU.draw_line(20, 10, 20, 50, 3); 
    vgaU.draw_line(20, 50, 20, 50 - i, 1); 
    vgaU.draw_line(19, 10, 22, 10, 3); 
    vgaU.draw_line(19, 50, 22, 50, 3); 
}
    
void drawBorder() {
   // total screen size = 120/60
   // tetris game board: width = 30; heigh = 60
   vgaU.draw_line(44,0,78,0,3);
   vgaU.draw_line(44,59,78,59,3);
   vgaU.draw_line(44,0,44,59,3);
   vgaU.draw_line(78,0,78,60,3);
}

// --------------------- this is for the beginning game window ------------------------ 
void drawStartScreen() {
   drawBorder(); 
   drawGameScreen(); 
   button = 0;
   vga.delay(200);
} 

// ---------------------- this is the main function to draw the game screen -----------
void drawGameScreen() {
  drawBorder(); 
}

// ----------------------- Tetriminos definition --------------------------------------
void blockDef(int i) {
  if (i == 1){
  // O
  block[0][0] = 0;
  block[0][1] = 0;
  block[1][0] = 1;
  block[1][1] = 0;
  block[2][0] = 0;
  block[2][1] = 1;
  block[3][0] = 1;
  block[3][1] = 1;
  color = 1; 
  }
  if (i == 2){
  // L
  block[0][0] = -1;
  block[0][1] = 0;
  block[1][0] = 0;
  block[1][1] = 0;
  block[2][0] = 1;
  block[2][1] = 0;
  block[3][0] = -1;
  block[3][1] = 1;
  color = 2; 
  }
  if (i == 3){
  // J
  block[0][0] = -1;
  block[0][1] = 0;
  block[1][0] = 0;
  block[1][1] = 0;
  block[2][0] = 1;
  block[2][1] = 0;
  block[3][0] = 1;
  block[3][1] = 1;
  color = 3; 
  }
  if (i == 4){
  // I
  block[0][0] = -1;
  block[0][1] = 0;
  block[1][0] = 0;
  block[1][1] = 0;
  block[2][0] = 1;
  block[2][1] = 0;
  block[3][0] = 2;
  block[3][1] = 0;
    color = 1; 
  }
  if (i == 5){
  // S
  block[0][0] = -1;
  block[0][1] = 0;
  block[1][0] = 0;
  block[1][1] = 0;
  block[2][0] = 0;
  block[2][1] = 1;
  block[3][0] = 1;
  block[3][1] = 1;
  color = 2; 
  }
  if (i == 6){
  // Z
  block[0][0] = -1;
  block[0][1] = 1;
  block[1][0] = 0;
  block[1][1] = 1;
  block[2][0] = 0;
  block[2][1] = 0;
  block[3][0] = 1;
  block[3][1] = 0;
  color = 3; 
  }
  if (i == 7){
  // T
  block[0][0] = -1;
  block[0][1] = 0;
  block[1][0] = 0;
  block[1][1] = 0;
  block[2][0] = 0;
  block[2][1] = 1;
  block[3][0] = 1;
  block[3][1] = 0;
  color = 1; 
  }
}

// -------------------------- expansion for 4:3 monitors ------------------------------ 
void blockExtension() {
   for (int i = 0; i < 4; i++){
      blockExt[0][0] = block[0][0]*3;
      blockExt[0][1] = block[0][1]*2;
      blockExt[1][0] = block[1][0]*3;
      blockExt[1][1] = block[1][1]*2;
      blockExt[2][0] = block[2][0]*3;
      blockExt[2][1] = block[2][1]*2;
      blockExt[3][0] = block[3][0]*3;
      blockExt[3][1] = block[3][1]*2;
   }
}
 
void blockRotation(int clock){
  for (int i = 0; i < 4; i++){
     blockOld[0][0] = block[0][0];
     blockOld[0][1] = block[0][1];
     blockOld[1][0] = block[1][0];
     blockOld[1][1] = block[1][1];
     blockOld[2][0] = block[2][0];
     blockOld[2][1] = block[2][1];
     blockOld[3][0] = block[3][0];
     blockOld[3][1] = block[3][1];
  }
  for (int i = 0; i < 4; i++){
     block[0][0] = blockOld[0][1]*clock;
     block[0][1] = -blockOld[0][0]*clock;
     block[1][0] = blockOld[1][1]*clock;
     block[1][1] = -blockOld[1][0]*clock;
     block[2][0] = blockOld[2][1]*clock;
     block[2][1] = -blockOld[2][0]*clock;
     block[3][0] = blockOld[3][1]*clock;
     block[3][1] = -blockOld[3][0]*clock;
  }
}
void blockTranslation(int x, int y) {
   for (int i = 0; i < 4; i++){
      blockTr[0][0] = blockExt[0][0] + x;
      blockTr[0][1] = blockExt[0][1] + y;
      blockTr[1][0] = blockExt[1][0] + x;
      blockTr[1][1] = blockExt[1][1] + y;
      blockTr[2][0] = blockExt[2][0] + x;
      blockTr[2][1] = blockExt[2][1] + y;
      blockTr[3][0] = blockExt[3][0] + x;
      blockTr[3][1] = blockExt[3][1] + y;
   }
}

void delBlock(){
  if (noDelete == 1) {noDelete = 0;} 
  else {
      for (int i = 0; i < 4; i++){
         vgaU.draw_line(blockTr[i][0],blockTr[i][1],blockTr[i][0] + 3,blockTr[i][1],0);
         vgaU.draw_line(blockTr[i][0],blockTr[i][1] + 1,blockTr[i][0] + 3,blockTr[i][1] + 1,0);   
      }
   }
}

void drawBlock(){
  for (int i = 0; i < 4; i++){
     vgaU.draw_line(blockTr[i][0],blockTr[i][1],blockTr[i][0] + 3,blockTr[i][1], color);
     vgaU.draw_line(blockTr[i][0],blockTr[i][1] + 1,blockTr[i][0] + 3,blockTr[i][1] + 1, color);   
  }
  for (int i = 0; i < 4; i++){
     blockTmp[0][0] = blockTr[0][0];
     blockTmp[0][1] = blockTr[0][1];
     blockTmp[1][0] = blockTr[1][0];
     blockTmp[1][1] = blockTr[1][1];
     blockTmp[2][0] = blockTr[2][0];
     blockTmp[2][1] = blockTr[2][1];
     blockTmp[3][0] = blockTr[3][0];
     blockTmp[3][1] = blockTr[3][1];
  }
}

void drawBlockTmp(){
  for (int i = 0; i < 4; i++){
     vgaU.draw_line(blockTmp[i][0],blockTmp[i][1],blockTmp[i][0] + 3,blockTmp[i][1], color);
     vgaU.draw_line(blockTmp[i][0],blockTmp[i][1] + 1,blockTmp[i][0] + 3,blockTmp[i][1] + 1, color);   
  }
}

void checkBlock(){ 
  busy = 0;  
  for (int i = 0; i < 4; i++){
     busy = busy + vga.getpixel(blockTr[i][0], blockTr[i][1]) + vga.getpixel(blockTr[i][0] + 2, blockTr[i][1]);
  }
}

void replaceBlock(){
     blockExtension(); 
     blockTranslation(x, y); 
     checkBlock();
     if (busy == 0){
        drawBlock(); 
     }
     else // ---------- else is run if the block cannot get down  ----------------- 
     {
        drawBlockTmp(); 
        checkForFullLine(); // ---- check il the line is filled when the block cennot get down anymore ---------------------- 
        noLoop = 0; 
        noDelete = 1; 
        if (y < 6) {
           gameOver();
        }
     }
     vga.delay(50);
}

void gameOver(){
   noLoop = -1; 
   score = 0;
   fast = 14;
   clearInputs(); 
   time = 0; 
   while (button_1 == 0 && button_2 == 0 && button_3 == 0 && button_4 == 0) {
      processInputs(); 
      vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str13, 92, 30, 1);
      vga.printPROGMEM((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str14, 92, 38, 1);
      vga.delay(200);
   }
   vga.clear(0); 
   
}

void drawBlockNext(){ // ----- draw nenx block on the right side -------------------------------- 
     blockExtension(); 
     blockTranslation(100, 10); 
     vgaU.draw_line(95, 8, 112, 8, 0);
     vgaU.draw_line(95, 9, 112, 9, 0);
     vgaU.draw_line(95, 10, 112, 10, 0);
     vgaU.draw_line(95, 11, 112, 11, 0);
     vgaU.draw_line(95, 12, 112, 12, 0);
     vgaU.draw_line(95, 13, 112, 13, 0);
     vgaU.draw_line(95, 14, 112, 14, 0);
     vgaU.draw_line(95, 15, 112, 15, 0);
     drawBlock(); 
}

void checkBlockTranslation(){
     x = x + delta; 
     blockExtension(); 
     blockTranslation(x, y); 
     checkBlock();
     if (busy == 0){
        drawBlock(); 
     }
     else
     {
        x = x - delta; 
        blockExtension(); 
        blockTranslation(x, y); 
        drawBlock(); 
     }
     vga.delay(50);
}

void checkBlockRotation(){
     //x = x + delta; 
     blockExtension(); 
     blockTranslation(x, y); 
     checkBlock();
     if (busy == 0){
        drawBlock(); 
     }
     else
     {
        clock = +1;
        blockRotation(clock); 
        blockExtension(); 
        blockTranslation(x, y); 
        drawBlock(); 
     }
     vga.delay(50);
}

void checkForFullLine() { // --------------------- check if the line is full and must be deleted --------------
   for (int i = 0; i < 4; i++){
      for (int j = 45; j < 76; j += 3) {
         if (vga.getpixel(j, blockTmp[i][1]) >0){k++; }
      }
      if (k == 11) { // ---- line is full and must be deleted ----------------------------------------------------------
         vgaU.draw_line(45, blockTmp[i][1], 78, blockTmp[i][1], 0); 
         vgaU.draw_line(45, blockTmp[i][1] + 1, 78, blockTmp[i][1] + 1, 0);   
         yLineTmp[yCounter] = blockTmp[i][1]; 
         yLine[yCounter] = blockTmp[i][1]; 
         yCounter++; 
      }
      k = 0; 
    }
    if (yLineTmp[yCounter - 1] < yLine[0]) { // ------------ qui va capito se va < o > (penso >) ----------------------
       for (int i = 0; i < yCounter; i++) { // ------------- inversion ---------------------------------------
          yLine[i] = yLineTmp[yCounter - i - 1]; 
       }
    }
    for (int i = 0; i < yCounter; i++){   // ----------- block translation to lower position -------------- 
      for (int y = yLine[i] - 2; y > 0; y = y - 2) {
         for (int x = 45; x < 76; x += 3) {
            colorOld = vga.getpixel(x, y); 
            if (colorOld > 0) {
               vgaU.draw_line(x, y , x + 3, y , 0);
               vgaU.draw_line(x, y + 1, x + 3, y + 1, 0);
               vgaU.draw_line(x, y + 2, x + 3, y + 2, colorOld);
               vgaU.draw_line(x, y + 3, x + 3, y + 3, colorOld);
            } 
         }
      }
   }
   if (yCounter != 0) {score = score + 2*int(pow(2, yCounter));} 
   drawScore(score); 
   yCounter = 0; 
}

//-----------------------------------------------------------------------------------------------
//--------------------- This is the main loop of the game ---------------------------------------
//-----------------------------------------------------------------------------------------------

void loop() {
  processInputs(); 
  if (noLoop < 1){ // --------------- to generate new Tetraminos --------------------------------
     blockN = blockNext; 
     if (noLoop == -1 ) { // -------------- only ath the game beginning  ------------------------
        drawMenu(); 
        while (button_1 == 0 && button_2 == 0 && button_3 == 0 && button_4 == 0) {
           blockN = int(random(7)) + 1;
           processInputs(); 
        }
     }
     drawGameScreen();
     drawScore(score);
     blockNext = int(random(8));
     blockDef(blockNext);
     drawBlockNext();
     blockDef(blockN);
     x = 57; 
     y = 3; 
     button_1 = 1; 
     noLoop = 1; 
  }
  if (button_2 == 1){ // ------------------------ rotation -------------------------
     if (button_2 == 1){clock = -1;}
     //if (button_5 == 1){clock = 1;}
     delBlock();
     blockRotation(clock); 
     checkBlockRotation(); 
  }
  if (button_1 == 1 || button_3 == 1){ // ------- translation ----------------------
     if (button_1 == 1){delta = 3;}
     if (button_3 == 1){delta = -3;}
     delBlock();
     checkBlockTranslation();
  }
  time++; 
  if (time % fast > fast - 2 || button_4 == 1){ // --- Tetraminos falling ----------
     if (fast < 3) {fast = 2;}
     y = y + 2;
     delBlock(); 
     replaceBlock(); 
  }
  vga.delay(10 + 2*fast);
}


