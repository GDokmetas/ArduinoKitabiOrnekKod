// Arduino Bomber for VGA output - Version 1.0 
// written by Rob Cai - June the 8th, 2015 
// see: "Arduino Bomber with Colors and Sound" on YouTube
// https://www.youtube.com/watch?v=dtfNhh6GZ-s
// VGAx Library By Sandro Maffiodo here:
// https://github.com/smaffer/vgax
// Arduino software version: 1.6.4 

#include <VGAX.h>
#include <math.h>
#define FNT_NANOFONT_HEIGHT 6
#define FNT_NANOFONT_SYMBOLS_COUNT 95

//data size=570 bytes
const unsigned char fnt_nanofont_data[FNT_NANOFONT_SYMBOLS_COUNT][1+FNT_NANOFONT_HEIGHT] PROGMEM={
{ 1, 128, 128, 128, 0, 128, 0, }, //glyph '!' code=0
{ 3, 160, 160, 0, 0, 0, 0, }, //glyph '"' code=1
{ 5, 32, 160, 240, 120, 32, 32, },  //glyph '#' = 'planeR' code=2
{ 3, 80, 32, 112, 112, 32, 0, },  //glyph '$' = 'bomb' code=3
{ 5, 32, 40, 120, 240, 32, 32, },  //glyph '%' = 'planeL' code=4
{ 5, 96, 144, 104, 144, 104, 0, },  //glyph '&' code=5
{ 5, 248, 248, 248, 248, 248, 248, },  //glyph ''' = 'rectangle 5 x 6' code=6
{ 5, 0, 0, 0, 24, 248, 248, }, //glyph '(' = bomberL code=7
{ 5, 0, 0, 0, 192, 248, 248, },  //glyph ')'= bomberR code=8
{ 1, 128, 128, 128, 128, 128, 128, },  //glyph '*'= bomberCenter code=9
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

VGAX vga;

static const char str0[] PROGMEM="#  $";
static const char str1[] PROGMEM="#"; //planeR
static const char str2[] PROGMEM="%"; //planeL
static const char str3[] PROGMEM="$"; //bomb
static const char str4[] PROGMEM="'"; //rectangle 5 x 6
static const char str6[] PROGMEM="("; //BomberL
static const char str7[] PROGMEM="*"; //BomberCenter
static const char str8[] PROGMEM=")"; //BomberR
static const char str9[] PROGMEM="'''''''"; //clear 'Hit' banner 
static const char str10[] PROGMEM="Hit !!!"; //'Hit' banner
static const char str11[] PROGMEM="Arduino VGA Bomber"; 
static const char str12[] PROGMEM="by Roberto Melzi"; 
static const char str13[] PROGMEM="VGAx library"; 
static const char str14[] PROGMEM="by Sandro Maffiodo"; 
static const char str15[] PROGMEM="Game Over!!!"; 

#define BUTTON_PIN 0  //NB: by default, this pin (A0) is used in the VGAx library to generate the audio. 
                      //    It is better to connect the button to another pin, for instance pin 2 (A2) and use the next line insted.
//#define BUTTON_PIN 2 
#define WHEEL_PIN 1 

void circle(float a, float b, float r, int c){
  float pi = 3.14159265; 
  int divisions = int(1.1*pi*r/2); 
  for (int i = 0; i <= divisions; i++){
    float x = r*cos(pi/2*i/divisions);
    float y = r*sin(pi/2*i/divisions); 
    int x0 = int(a + x);
    int y0 = int(b + y); 
    if(x0 > 0 && x0 < VGAX_WIDTH && y0 > 0 && y0 < VGAX_HEIGHT){
      vga.putpixel(x0, y0, c); 
    }
    x0 = int(a + x);
    y0 = int(b - y); 
    if(x0 > 0 && x0 < VGAX_WIDTH && y0 > 0 && y0 < VGAX_HEIGHT){
      vga.putpixel(x0, y0, c); 
    }
    x0 = int(a - x);
    y0 = int(b + y); 
    if(x0 > 0 && x0 < VGAX_WIDTH && y0 > 0 && y0 < VGAX_HEIGHT){
      vga.putpixel(x0, y0, c); 
    }
    x0 = int(a - x);
    y0 = int(b - y); 
    if(x0 > 0 && x0 < VGAX_WIDTH && y0 > 0 && y0 < VGAX_HEIGHT){
      vga.putpixel(x0, y0, c); 
    }
  }
}

void line(float x1, float y1, float x2, float y2, int c){
  int divisions = int(1.1*1*sqrt(pow((y2 - y1),2) + pow((x2 - x1),2))); 
  for (int i = 0; i <= divisions; i++){
    int x = int(x1 + i*(x2 - x1)/divisions);
    int y = int(y1 + i*(y2 - y1)/divisions);
    if(x > 0 && x < VGAX_WIDTH && y > 0 && y < VGAX_HEIGHT){
      vga.putpixel(x, y, c); 
    }
  }
}

void cls(){
   vga.clear(0);
}

void setup() {
  //Serial.begin(9600); // this gives flickers...
  vga.begin();
}

unsigned char x,y;
boolean buttonStatus = 0;
int wheelPosition = 512;
int BomberX = VGAX_WIDTH/2; 
float bombX = 10;
float bombY = 20.0; 
float bombV0 = 1.2;
float bombV0y = 0;  
float bombX0 = VGAX_WIDTH/2; 
float bombY0 = 0; 
float aereoX = 10;
float aereoY = 20.0;
float Vaereo = 2.0; 
int ricarica = 0; 
int aereoColpito = 0;
int bombaColpita = 1; 
int t = 0; 
int score = 40; 
int level = 0; 
int frame = 0;
int state = 1;
int shot = 2; 
float aereoX_0;
float aereoY_0;
float bombX_0; 
float bombY_0; 
int planeX;
int planeY;
int planeX0;
int planeY0; 
int BomberX0; 
float radius; 
float x0;
float y0;
float x1;
float y1;
int color; 
int counter = -1; 
int counterMenu = 0;
int counterMenu2 = 0; 

void processInputs() {
  wheelPosition = analogRead(WHEEL_PIN);
  buttonStatus = (analogRead(BUTTON_PIN) > 512); 
}

void drawMenu() {
  counterMenu2++; 
  vga.delay(10); 
  if (counterMenu2 > 50){
    counterMenu++; 
    vga.print((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str11, 20, 12, (counterMenu%3) + 1);
    vga.print((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str12, 30, 22, ((counterMenu + 1)%3) + 1);
    vga.print((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str13, 20, 32, (counterMenu%3) + 1);
    vga.print((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str14, 30, 42, ((counterMenu + 2)%3) + 1);
    counterMenu2 = 0; 
  }
}

void drawDemo() {
  counter++; 
  if(counter < 70){
     radius = counter; 
     x0 = int(VGAX_WIDTH/2); 
     y0 = int(VGAX_HEIGHT/2); 
     color = counter%3 + 1; 
     vga.tone(110 + 4*counter);
     //vga.delay(20);
     circle(x0, y0, radius, color); 
  }
  if(counter == 70){
     vga.clear(0);
  }
  if (counter > 70 and counter < 234){
    x0 = VGAX_WIDTH/2; 
    y0 = VGAX_HEIGHT/2; 
    x1 = int((counter - 70)*sin(6.28*(counter - 71)/120) + VGAX_WIDTH/2); 
    y1 = int((counter - 70)*cos(6.28*(counter - 71)/120) + VGAX_HEIGHT/2); 
    color = counter%3 + 1; 
    line(x0, y0 ,x1 ,y1 ,color); 
    vga.tone(165 + 3*(counter - 70));
    //vga.delay(20);
  }
  if(counter == 234){
     vga.clear(0);
     counter = -1; 
  }
}

// this is the main function to draw the game screen 
void drawGameScreen() {
      //draw plane ----------------------------------------------  
      if(Vaereo > 0 && planeX != planeX0) {
      vga.print((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str4, planeX0, planeY0, 0);
      vga.print((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str1, planeX, planeY, 1);
      }
      if(Vaereo < 0 && planeX != planeX0) {
      vga.print((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str4, planeX0, planeY0, 0);
      vga.print((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str2, planeX, planeY, 1);
      }
      //draw bomb -----------------------------------------------
      vga.print((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str3, bombX_0, bombY_0, 0);
      vga.print((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str3, bombX, bombY, 2);
      // draw score line ----------------------------------------
      line(VGAX_WIDTH - 99,1,VGAX_WIDTH-score-1,1,0);  
      vga.putpixel(VGAX_WIDTH - 100,1,(level + 2)%3 + 1);
      line(VGAX_WIDTH,1,VGAX_WIDTH-score,1,3);  
      //draw ground ---------------------------------------------
      line(VGAX_WIDTH,VGAX_HEIGHT-1,1,VGAX_HEIGHT-1, 2); 
      //draw bombard --------------------------------------------
      BomberX = (((1024 - wheelPosition) / 8) * (VGAX_WIDTH - 12))/ 128 + 6;
      vga.print((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str6, BomberX0 - 5, VGAX_HEIGHT - 7, 0);
      vga.print((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str7, BomberX0 , VGAX_HEIGHT - 7, 0);
      vga.print((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str8, BomberX0 + 1, VGAX_HEIGHT - 7, 0);
      vga.print((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str6, BomberX - 5, VGAX_HEIGHT - 7, 3);
      vga.print((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str7, BomberX , VGAX_HEIGHT - 7, 3);
      vga.print((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str8, BomberX + 1, VGAX_HEIGHT - 7, 3);
      // draw shot ----------------------------------------------
      if ( ricarica == shot - 1) {
         line(BomberX0,VGAX_HEIGHT-8,BomberX0,0,0);
      }
      if ( ricarica == shot) {
         line(BomberX,VGAX_HEIGHT-8,BomberX,0,1);
      }
}

void loop() {
  
  processInputs(); 
  
  if(state == 1) {
     drawMenu();
     vga.delay(10);
  }
  
  if (buttonStatus == 1 && state == 1){
     buttonStatus == 0; 
     vga.clear(0);
     state = 2; 
  }
  
  if(state == 2) {

     // this is exectuted just after a shot -----------------------
     if (ricarica == shot) {  
        if (BomberX > aereoX - 2 - level && BomberX < aereoX + 2 + level) { // plane is hit ------------------
           aereoX = -10; 
           score += 8;
           vga.tone(110);
           vga.delay(60); 
           vga.noTone();
         }
         if (BomberX > (bombX - 2 ) && BomberX < (bombX + 2)) { // bomb is hit ----------------
            bombX0 = 2*VGAX_WIDTH;
            bombY0 = -100.; 
            bombV0 = 0;  
            score += 8; 
            vga.tone(165);
            vga.delay(60); 
            vga.noTone(); 
          }
     }     
            
     // plane has escaped ----------------------------------------------------
     if(aereoX > VGAX_WIDTH || aereoX < 0) {
        score += -4 - level; 
        Vaereo = random(200)/100.0 + 2 + 2*level; 
        aereoY = random(VGAX_HEIGHT*2/3*100)/100.0 + 2; 
        if(random(1000) > 500)
           {aereoX = 10;} 
        else {
           aereoX = VGAX_WIDTH-10; 
           Vaereo = -Vaereo; 
        }
     }
     
     // plane position -------------------------------------------------------
     aereoX += Vaereo;
        
     // bomb position and trajectory -----------------------------------------
        bombX = bombX0 + bombV0*t;            
        bombY = bombY0 + bombV0y*t + t*t/(48 - 18*level);
        if(bombY > VGAX_HEIGHT - 5 || bombX < 0 || bombX > VGAX_WIDTH){
          if(bombX >= BomberX - 6 && bombX < BomberX + 6){
             //Bomber has been hit -------------------------------------------
             vga.print((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str10, 50, 10, 1);
             vga.tone(880); 
             vga.delay(200);
             vga.tone(440); 
             vga.delay(200);
             vga.tone(220);
             vga.delay(200);
             vga.tone(110); 
             vga.delay(200);
             vga.noTone(); 
             vga.print((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str9, 50, 10, 0);
             vga.print((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str9, 51, 10, 0);
             score += -30; 
          }
          bombY0 = aereoY + 4;
          bombX0 = aereoX;
          bombV0 = Vaereo - level + random(-100,100)/100.; 
          bombV0y = level + random(200)/100.; 
          t = 0;
       }
       else
       {t = t + 1;}
     
       // check the shot ---------------------------------------------------------
       if(ricarica != 0 ) {
          ricarica += -1; 
       }
       if ( buttonStatus == 1 && ricarica == 0) {
          score += -1; 
          ricarica = shot; 
          BomberX0 = BomberX;
          buttonStatus = 0; 
        }
         
        // check score state and Game Over --------------------------------------
        if(score < 0) {
           buttonStatus == 0; 
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
           state = 3;
        }
        if (score > 100) {
          score = 50;
          vga.tone(440);
          vga.delay(100); 
          vga.tone(880);
          vga.delay(100); 
          vga.noTone(); 
          level++; 
        }
     
     planeX = int(aereoX);
     planeY = int(aereoY); 
     
     drawGameScreen(); 
     //vga.delay(10);
     
     aereoX_0 = aereoX;
     aereoY_0 = aereoY;
     bombX_0 = bombX;
     bombY_0 = bombY; 
     planeX0 = int(aereoX);
     planeY0 = int(aereoY); 
     BomberX0 = BomberX; 
   }     
   
   if(state == 3){
     vga.print((byte*)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str15, 40, 20, 1);
     vga.delay(200); 
     if(buttonStatus == 1){
        score = 40; 
        level = 0;
        vga.clear(0); 
        buttonStatus = 0; 
        counter = -1; 
        state = 4;
     }
   }
   
  if (state == 4){
     drawDemo(); 
  }
  
  if (buttonStatus == 1 && state == 4){
     buttonStatus == 0; 
     vga.clear(0);
     vga.noTone();
     vga.delay(200); 
     counterMenu = 0; 
     state = 1; 
  }
}
