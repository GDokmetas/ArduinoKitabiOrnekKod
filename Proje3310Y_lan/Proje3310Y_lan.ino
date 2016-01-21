#include <LCD5110_Graph.h>
LCD5110 myGLCD(8,9,10,11,12); extern unsigned char SmallFont[]; extern unsigned char TinyFont[];
int endgame = 10;
int zx[300] = {26, 25, 24, 23, 22}; int zy[300] = {20, 20, 20, 20, 20};
int len=5; int navi=4; int x,y,mx,my;
long pM = 0; long per = 75;
 
void setup()
{
myGLCD.InitLCD(); myGLCD.setFont(SmallFont);
for (int u=5; u <= 300-1; u++) {zx[u]=-1;zy[u]=-1;}
mx=random(84); my=random(44);mx=random(84); my=random(44);
}
 
void loop()
{
 
int b0=analogRead(A0);
int b1=analogRead(A1);
if ((b0 < 400)and(navi!=4)) {navi=3;}
if ((b0 > 600)and(navi!=3)) {navi=4;}
if ((b1 < 400)and(navi!=1)) {navi=2;}
if ((b1 > 600)and(navi!=2)) {navi=1;}
if (zx[0] < 0) {endgame=0;}
if (zx[0] > 83) {endgame=0;}
if (zy[0] < 0) {endgame=0;}
if (zy[0] > 49) {endgame=0;}
 
 
unsigned long cM = millis();
if(cM - pM > per) {pM = cM; myGLCD.clrScr();
 
for (int i=1; i < len; i++) { myGLCD.drawRect(zx[i], zy[i], zx[i]+1, zy[i]+1); }
 
x=zx[0]; y=zy[0]; for (int t=len; t > 0; t--) { zx[t]=zx[t-1]; zy[t]=zy[t-1]; }
switch (navi) {case 1: y--; break; case 2: y++; break; case 3: x--; break; case 4: x++; break; }
zx[0]=x; zy[0]=y; myGLCD.drawRect(zx[0], zy[0], zx[0]+1, zy[0]+1);
 
 
 
 
myGLCD.drawRect(mx, my, mx+1, my+1);
 
if (((x==mx)or(x+1==mx)or(x-1==mx)) and ((y==my)or(y+1==my)or(y-1==my))) {len=len+10; per=per-5; mx=random(84); my=random(44);}
 
myGLCD.update();
 
}
 
 
if (endgame == 0) {myGLCD.clrScr();
myGLCD.print("OYUN BITTI:(", CENTER, 12); myGLCD.print("puan:", 15, 22);myGLCD.printNumI(len*2, 50, 22); myGLCD.update();delay(8000);}
}
