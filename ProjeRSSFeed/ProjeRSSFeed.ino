
int startstring = 0;    
int charcount = 0;    
       
#include  <LiquidCrystal.h> 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
         Serial.begin(9600);     
         lcd.begin(16,2);          
         lcd.setCursor(0,0);     
         pinMode(13, OUTPUT);
}

void loop() {
        char incomingByte = 0;  
       
         if (Serial.available() > 0) {       
                 digitalWrite(13, HIGH);
                 incomingByte = Serial.read();
                 if ((incomingByte == '~') && (startstring == 1)){          
                   startstring = 0;                                                               
                   delay(5000);                                                                    
                   lcd.clear();                                                                      
                   charcount = 0;                                                                 
                   lcd.setCursor(0,0);                                                      
                 }
                 if (startstring == 1){                                                            
                   if (charcount <= 30){                                                       
                     lcd.print(incomingByte);                                               
                     charcount = charcount++;                                           
                     }
                   }
                   if (charcount == 31){                                                         
                     delay(500);
                     lcd.clear();                                                                      
                     lcd.setCursor(0,0);                                                        
                     lcd.print(incomingByte);                                               
                     charcount = 1;                                                                 
                   }
                  
                 if (incomingByte == '~'){                                                   
                  
                   startstring = 1;                                                                
                 }
         }
                 digitalWrite(13, LOW);
                 delay(10);                                                                           
             } 
