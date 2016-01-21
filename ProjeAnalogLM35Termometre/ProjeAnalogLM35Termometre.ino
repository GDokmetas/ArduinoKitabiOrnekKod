#include <Servo.h>
 
Servo myservo;
 
void setup() {
 
myservo.attach(11);
Serial.begin(9600);
 
int sicaklik;
 
int sicaklikpin=0;  //Sensörümüzün bağlı olduğu analog pin
 
float gerilim;
 
 
}
 
void loop() {
 
gerilim =analogRead(sicaklikpin); //sensör değerini oku
gerilim=(gerilim/1023)*5000;    //dönüşümler yapılarak derece cinsinden
sicaklik=gerilim / 10;                 //değer elde edilip sicaklik değişkenine atılıyor
sicaklik = map(val, 0, 39, 0, 179); ///// burası çok önemli çünkü 0-39 derece arasını tanımladık isterseniz değeri değiştirebilirsiniz .
 
Serial.println(val);
myservo.write(temp);
delay(1000);
 
}
