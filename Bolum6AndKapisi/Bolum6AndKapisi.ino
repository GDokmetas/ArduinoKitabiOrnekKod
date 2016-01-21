void setup() {
pinMode(2,INPUT_PULLUP);
pinMode(3,INPUT_PULLUP);
pinMode(4,INPUT_PULLUP);
pinMode(5,INPUT_PULLUP);

Serial.begin(9600);
}

void loop() {
if ( (!(digitalRead(2))) && (!(digitalRead(3))) && (!(digitalRead(4))) && (!(digitalRead(5))) )
Serial.println("Tebrikler Dugmelerin Hepsine Basmayi Basardiniz");
delay(100);
}
