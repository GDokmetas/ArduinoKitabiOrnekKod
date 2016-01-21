#include <EEPROM.h>

int address = 0;
byte value;

void setup() {

  Serial.begin(9600);

}

void loop() {

  value = EEPROM.read(address); // Value degerine eeprom hücresindeki degeri ata

  Serial.print(address); // adresi göster
  Serial.print("\t"); //boşluk bırakma
  Serial.print(value, BIN); // Binary olarak value degerini goster 
  Serial.println(); // satır atla

  address = address + 1;
  if (address == EEPROM.length()) { //Eğer adres kapasiteyi aşarsa sıfırla
    address = 0;
  }

  delay(200);
}
