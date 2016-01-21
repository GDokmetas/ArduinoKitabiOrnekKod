char* Strng[]={"Birinci Cumle", "Ikinci Cumle", "Ucuncu Cumle",
"Dorduncu Cumle", "Besinci Cumle","Altinci Cumle"};

void setup(){
Serial.begin(9600);
}

void loop(){
for (int i = 0; i < 6; i++){
   Serial.println(Strng[i]);
   delay(500);
   }
}
