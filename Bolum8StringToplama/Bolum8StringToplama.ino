void setup() {
Serial.begin(9600);
}

void loop() {
String String1 = "Arduino ile Stringler";
String String2 = "Bu da ikinci String Verisi";
String String3;
Serial.println("Stringler ile Toplama islemi");
Serial.print("String 1:");
Serial.println(String1);
Serial.print("String 2:");
Serial.println(String2);
Serial.println("String1+String2");
String3 = String1 + String2;
Serial.println(String3);
Serial.println("String + Integer");
String3 = String1 + 255556;
Serial.println(String3);
Serial.println("String + String Sabiti");
String3 = String1 + "Bu da String Sabiti";
Serial.println(String3);
while(1);

}
