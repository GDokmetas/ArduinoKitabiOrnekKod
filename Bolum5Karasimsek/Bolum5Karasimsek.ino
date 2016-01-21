/* 
 *  Arduino UNO ile karaşimşek devresi
 *  10 adet ledi belli bir sıra ile yakar 
 */

void setup() {
pinMode(2,OUTPUT);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
pinMode(7,OUTPUT);
pinMode(8,OUTPUT);
pinMode(9,OUTPUT);
pinMode(10,OUTPUT);
pinMode(11,OUTPUT);

}

void loop() {
 int hiz=75; // Hız değişkeni
digitalWrite(2,HIGH); delay(hiz); digitalWrite(2,LOW);
// Her bir led yakılıp söndürülür
digitalWrite(3,HIGH); delay(hiz); digitalWrite(3,LOW);

digitalWrite(4,HIGH); delay(hiz); digitalWrite(4,LOW);

digitalWrite(5,HIGH); delay(hiz); digitalWrite(5,LOW);

digitalWrite(6,HIGH); delay(hiz); digitalWrite(6,LOW);

digitalWrite(7,HIGH); delay(hiz); digitalWrite(7,LOW);

digitalWrite(8,HIGH); delay(hiz); digitalWrite(8,LOW);

digitalWrite(9,HIGH); delay(hiz); digitalWrite(9,LOW);

digitalWrite(10,HIGH); delay(hiz); digitalWrite(10,LOW);

digitalWrite(11,HIGH); delay(hiz); digitalWrite(11,LOW);
//Şimdi tersine yakıyoruz

digitalWrite(10,HIGH); delay(hiz); digitalWrite(10,LOW);

digitalWrite(9,HIGH); delay(hiz); digitalWrite(9,LOW);

digitalWrite(8,HIGH); delay(hiz); digitalWrite(8,LOW);

digitalWrite(7,HIGH); delay(hiz); digitalWrite(7,LOW);

digitalWrite(6,HIGH); delay(hiz); digitalWrite(6,LOW);

digitalWrite(5,HIGH); delay(hiz); digitalWrite(5,LOW);

digitalWrite(4,HIGH); delay(hiz); digitalWrite(4,LOW);

digitalWrite(3,HIGH); delay(hiz); digitalWrite(3,LOW);

}
