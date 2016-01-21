/* Trafik Işığı Uygulaması
 *  Bu program 3 adet lambayı belli sürelerde yakıp söndürür
 *  
 */

 void setup()
 {
    pinMode(8,OUTPUT); // Kırmızı 
    pinMode(9,OUTPUT); // Sarı
    pinMode(10,OUTPUT); //Yeşil
 }

void loop()
{
    digitalWrite(8,HIGH); //Kırmızı Yak
    delay(3000);
    digitalWrite(9,HIGH); // Sarı yak
    delay(1000);
    digitalWrite(8,LOW); //Kırmızı Söndür
    digitalWrite(9,LOW); //Sarı Söndür
    digitalWrite(10,HIGH); //Yeşil Yak
    delay(3000);
    digitalWrite(9,HIGH); //Sarı yak
    delay(1000);
    digitalWrite(10,LOW); //Yeşil Söndür
    digitalWrite(9,LOW); //Sarı Söndür 
}

