
int rainSensePin= 0;
int alertPin= 8; 
int curCounter= 0;
 
void setup(){
Serial.begin(9600);
pinMode(alertPin, OUTPUT);
pinMode(rainSensePin, INPUT);
}
void loop(){
int rainSenseReading = analogRead(rainSensePin);
Serial.println(rainSenseReading); 
delay(250); 

if (curCounter >= 30){ 
digitalWrite(alertPin, HIGH); 
}
 

if (rainSenseReading <300){ 
curCounter++; 
}
else if (rainSenseReading >300) { 
digitalWrite(alertPin, LOW); 
curCounter = 0; 
}
delay(1000);
}
