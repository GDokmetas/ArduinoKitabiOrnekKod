#include <AFMotor.h> 
#define trigPin 12 
#define echoPin 13   // Ultrasonik sensör ayakları
AF_DCMotor motorsag(1,MOTOR12_8KHZ);  // Motorları tanımla
AF_DCMotor motorsol(2, MOTOR12_8KHZ);
#include <Servo.h>
Servo basservo;
const int enbuyuk = 50;  // Mesafe sabiti. 
const bool TRUE = 1; // Lojik değer sabitleri. 
const bool FALSE =0;
const int enyakinnesne = 20; // En yakın cisim sabiti (Değiştirebilirsiniz.)
const int motorhiz = 100; // Motor Hız sabiti 0-255 Arası olabilir.
void setup() {
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
motorsag.setSpeed(motorhiz); 
motorsol.setSpeed (motorhiz); // Motor hız kontrol. 
basservo.attach(9); // Servo 9. ayak. Karttaki Servo 2 kısmı
// Debug Serial
Serial.begin(9600);
basservo.write(90); // Servo başı sabitle. 
delay(200);
}

void loop() {
basservo.write(90); 
solmotor.run(RELEASE);
sagmotor.run(RELEASE);
delay(100);
bool sagengel = bastarama(0,10); // Sağ Tarafı Tara 0-10 derece arası
bool onengel = bastarama(80,110); // Ön Tarafı Tara 80-110 derece arası
bool solengel = bastarama(170,180); //Sol tarafı tara 170-180 derece arası
// Bu fonksiyonlardan dönen değerler bool değişkenlerine yüklenir.
if (onengel==FALSE) // Önde engel yoksa ileri götür. 
{
  motorsag.run(FORWARD);
  motorsol.run(FORWARD);
  delay(400);
}

if (onengel==TRUE) // Eğer önde engel varsa 
{
 if(solengel == TRUE && sagengel == TRUE) // Her bir yanda engel varsa
{
  motorsol.run(BACKWARD); // Geri götür
  motorsag.run(BACKWARD);
  delay(500);
  motorsol.run(FORWARD); // Sola çevir 
  motorsag.run(BACKWARD);
  delay(400);
}
  
  else if(solengel==TRUE) // Solda engel varsa sağa dön
{
  motorsol.run(FORWARD);
  motorsag.run(BACKWARD);
  delay(400);
}
 else if(sagengel==TRUE) // Sağda engel varsa sola dön
 {
  motorsol.run(BACKWARD);
  motorsag.run(FORWARD);
  delay(400);
 }
}


}


bool bastarama(byte ilkaci, byte sonaci) // Sırayla tarama işlemini yap ve en yakın objeyi esas al
{
int sonolcum = enbuyuk;
basservo.write(ilkaci);
delay(100);
for (int i=ilkaci; i<sonaci; i+=1)
{
 
 int olcum = uzaklik();
 basservo.write(i);
 delay(5);
 if (olcum<sonolcum)
 sonolcum=olcum;
}


bool sondurum;
if (sonolcum<enyakinnesne)
sondurum=1;
else
sondurum=0;
return sondurum;
}


long uzaklik ()  // Ultrasonik uzaklık hesaplaması
{
   long duration, distance; // Ölçüme başla
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  return distance;
}

