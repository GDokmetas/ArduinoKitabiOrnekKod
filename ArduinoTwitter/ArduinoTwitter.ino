
#include <LiquidCrystal.h>
#include <Servo.h> 

#define USART_RX_BUFFER_SIZE  (150)
 
Servo myservo;  

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

long loop_start;
int bytei; 
int col; 
int input_pin = 0;
int new_tweet_status = 0;
int servo_switch_pin = 7; 
int servo_pin = 9; 
int sensor_delay;
char inmsg[200];
int servo_tick = 10;


void setup() {

  lcd.begin(16, 2);

  lcd.clear();
  lcd.noAutoscroll();  

  myservo.attach(servo_pin);  
  pinMode(servo_switch_pin, OUTPUT);
  digitalWrite(servo_switch_pin, HIGH);
  myservo.write(0);
  delay(250);  
  digitalWrite(servo_switch_pin, LOW);  
  Serial.begin(9600);
  delay(5000); 
}

void loop()
{
  loop_start = millis();

  Serial.print("status\n");
  while (Serial.available() == 0 && (millis() < loop_start+10000)) {}
  if (Serial.available()) {
    delay(100);
    
  
    read_to_buffer();
    
  

    lcd.setCursor(0,1);
    
    
    if (inmsg[0] == 'T') {
      if (new_tweet_status == 0) {
        new_tweet_status = 1;
        // myservo.write(0);
        digitalWrite(servo_switch_pin, HIGH);
        for (bytei=0; bytei < 101; bytei++) {
          myservo.write(bytei);
          delay(10);
        }
        delay(50);
      }
      
      digitalWrite(servo_switch_pin, LOW);
      lcd.print("   ");
      for (bytei=1 ; bytei<14 ; bytei++) {
        if (inmsg[bytei] != '\0') { 
          lcd.write(inmsg[bytei]);
        } else {
          lcd.print(' ');
        }
      } 
    } else {
      if (new_tweet_status == 1) {
        new_tweet_status = 0;      
        // myservo.write(90);      
        digitalWrite(servo_switch_pin, HIGH);      
        for (bytei=100; bytei >=0; bytei--) {
          myservo.write(bytei);
          delay(15);
        }
        delay(50);
        digitalWrite(servo_switch_pin, LOW);      
      }
      lcd.print("#gokhandokmetas");
    }
      
  } else {
    lcd.setCursor(0,0);
    lcd.print("Durum mesaji yok");
    lcd.setCursor(0,1);
    lcd.print("       :(       ");
    
  }
  
  delay(500);
  
  
  Serial.print("tweet\n");
  while (Serial.available() == 0 && (millis() < loop_start+8000)) {}
  if (Serial.available()) {
    delay(150); 
    

    read_to_buffer();
  
    clear_row(0); 
    
    
    bytei=0;
       
    while (inmsg[bytei+15] != '\0') {
     
      
      sensor_delay = analogRead(input_pin); 
      sensor_delay = 1024-sensor_delay;
      sensor_delay = sensor_delay/2;
      sensor_delay += 50; // (scaled to range 100-300)   
      // sensor_delay = 150; 
      lcd.setCursor(0,0);
      for (col = 0; col < 16; col++) {
        lcd.write(inmsg[bytei + col]);
      }
  
   
      bytei++;
      delay(sensor_delay);
    // } 
    }  
  } else {
    lcd.setCursor(0,1);
    lcd.print("Cevap yok");
   
  }
}

void clear_buffer()
{
  for (bytei=0;bytei<150;bytei++) {
    inmsg[bytei] = '\0';
  }
}

void read_to_buffer()
{
  clear_buffer();
  bytei = 0;
  while (Serial.available() > 0) {
    inmsg[bytei] = Serial.read();
    bytei++;
  }
  if (bytei == 127 || bytei == 128)
  while (Serial.available() > 0) {
    inmsg[bytei] = Serial.read();
    bytei++;
  }
  
  bytei = 0;
}  

void clear_row(int r)
{
  lcd.setCursor(0,r);
  lcd.print("               ");
  lcd.setCursor(0,r);
}  


