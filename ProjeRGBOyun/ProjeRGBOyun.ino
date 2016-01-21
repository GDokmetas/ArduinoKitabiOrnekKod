

#include <Serial.h>




const int redLED = 3;
const int greenLED = 5;
const int blueLED = 6;
const int inPin = 12;


const int DELAY_TIME = 10;
const int MAX_BRIGHT  = 255;


int red = 0;
int green = 170;
int blue = 170;
 

int incR = 1;
int incG = 1;
int incB = 0;



int targetRed;
int targetGreen;
int targetBlue;


boolean buttonPressed;

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  

  randomSeed(analogRead(0));
  
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  
  pinMode(inPin, INPUT);
  
 
  int cycles = random(100, 1000);
  for(int i = 0; i <= cycles; i++){
    setRandomColor();
  }
  targetRed = red;
  targetBlue = blue;
  targetGreen = green;
  
  
  Sesrial.println(targetRed);
  Serial.println(targetGreen);
  Serial.println(targetBlue);
  
  
  analogWrite(redLED, targetRed);
  analogWrite(greenLED, targetGreen);
  analogWrite(blueLED, targetBlue);
  
  
  buttonPressed = false;
  red = 0;
  green = 170;
  blue = 170;

  delay(5000);
}

void setRandomColor()
{
  transition();
}

void transition()
{
  if (red >= MAX_BRIGHT)
    incR = 0;
  else if (red <= 0)
    incR = 1;
  if (green >= MAX_BRIGHT)
    incG = 0;
  else if (green <= 0)
    incG = 1;
  if (blue >= MAX_BRIGHT)
    incB = 0;
  else if (blue <= 0)
    incB = 1;
 
  if (incR)
    red++;
  else
    red--;
  if(incG)
    green++;
  else
    green--;
  if(incB)
    blue++;
  else
    blue--;
}


void setColor()
{
  analogWrite(redLED, red);
  analogWrite(greenLED, green);
  analogWrite(blueLED, blue);

}

void loop() {
 
  if (digitalRead(inPin) == HIGH){
    buttonPressed = true;
    transition();
    setColor();
    delay(DELAY_TIME);
    

  }else{
    if(buttonPressed == false){ 
      analogWrite(redLED, 0);
      analogWrite(greenLED, 0);
      analogWrite(blueLED, 0);
    }
    else if(buttonPressed == true){
      Serial.println(red);
      Serial.println(green);
      Serial.println(blue);
      
      if(red >= (targetRed-30) && red <= (targetRed +30) &&
         green >= (targetGreen -20) && green <= (targetGreen +30) &&
         blue >= (targetBlue -30) && blue <= (targetBlue +30)){
           for(;;){ 
             analogWrite(redLED, 0);
             analogWrite(greenLED, MAX_BRIGHT);
             analogWrite(blueLED, 0);
             delay(100);
             analogWrite(greenLED, 0);
             delay(100);
         }    
    }else{
      for(;;){ 
             analogWrite(redLED, MAX_BRIGHT);
             analogWrite(greenLED, 0);
             analogWrite(blueLED, 0);
             delay(100);
             analogWrite(redLED, 0);
             delay(100);
         }
    }
  }
 }
}
