#include <SoftwareSerial.h>
 
int bluetoothTx = 2; // D2
int bluetoothRx = 3; // D3
 
int led = 12;
 
int buttonPin1 = 7;
int buttonPin2 = 8;
int button1State = 0;
int button2State = 0;
 
int dataFromBt;
 
boolean lightBlink = false;
 
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
 
void setup()
{
 Serial.begin(9600); //
 
 bluetooth.begin(115200); // 
 bluetooth.print("$"); // 
 bluetooth.print("$");
 bluetooth.print("$"); //
 delay(100); //
 bluetooth.println("U,9600,N"); // 
 // 
 bluetooth.begin(9600); // 
 pinMode(led, OUTPUT);
 pinMode(buttonPin1, INPUT);
 pinMode(buttonPin2, INPUT);
}
 
void loop()
{
 
 if(bluetooth.available()) // 
 {
 // 
 //Serial.println((char)bluetooth.read());
 
 dataFromBt = bluetooth.read();
 
 if(dataFromBt == '1'){
 Serial.println("led on");
 digitalWrite(led, HIGH);
 bluetooth.print("1");
 }
 if(dataFromBt == '0'){
 Serial.println("led off");
 digitalWrite(led, LOW);
 bluetooth.print("0");
 }
 if(dataFromBt == 'b'){
 Serial.println("a");
 lightBlink = true;
 }else{
 lightBlink = false;
 }
 
 }
 
 if(Serial.available()) 
 {
 
 bluetooth.print((char)Serial.read());
 }
 

 if(lightBlink){
 digitalWrite(led, HIGH);
 bluetooth.print("1");
 Serial.println("HIGH");
 delay(500);
 digitalWrite(led, LOW);
 bluetooth.print("0");
 Serial.println("LOW");
 delay(500);
 }
}
