void setup() {              
  pinMode(2, OUTPUT); 
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(9, 0);  
}

void loop() {
 // 9 Yazdır.
 digitalWrite(2, 1);
 digitalWrite(3, 1);
 digitalWrite(4, 1);
 digitalWrite(5, 0);
 digitalWrite(6, 0);
 digitalWrite(7, 1);
 digitalWrite(8, 1);
 delay(1000);
 // 8 Yazdır
 digitalWrite(2, 1);
 digitalWrite(3, 1);
 digitalWrite(4, 1);
 digitalWrite(5, 1);
 digitalWrite(6, 1);
 digitalWrite(7, 1);
 digitalWrite(8, 1);
 delay(1000);
 // 7 Yazdır.
 digitalWrite(2, 1);
 digitalWrite(3, 1);
 digitalWrite(4, 1);
 digitalWrite(5, 0);
 digitalWrite(6, 0);
 digitalWrite(7, 0);
 digitalWrite(8, 0);
 delay(1000);
 // 6 Yazdır.
 digitalWrite(2, 1);
 digitalWrite(3, 0);
 digitalWrite(4, 1);
 digitalWrite(5, 1);
 digitalWrite(6, 1);
 digitalWrite(7, 1);
 digitalWrite(8, 1);
 delay(1000);
 // 5 Yazdır.
 digitalWrite(2, 1);
 digitalWrite(3, 0);
 digitalWrite(4, 1);
 digitalWrite(5, 1);
 digitalWrite(6, 0);
 digitalWrite(7, 1);
 digitalWrite(8, 1);
 delay(1000);
 // 4 Yazdır.
 digitalWrite(2, 0);
 digitalWrite(3, 1);
 digitalWrite(4, 1);
 digitalWrite(5, 0);
 digitalWrite(6, 0);
 digitalWrite(7, 1);
 digitalWrite(8, 1);
 delay(1000);
 // 3 Yazdır.
 digitalWrite(2, 1);
 digitalWrite(3, 1);
 digitalWrite(4, 1);
 digitalWrite(5, 1);
 digitalWrite(6, 0);
 digitalWrite(7, 0);
 digitalWrite(8, 1);
 delay(1000);
 // 2 Yazdır.
 digitalWrite(2, 1);
 digitalWrite(3, 1);
 digitalWrite(4, 0);
 digitalWrite(5, 1);
 digitalWrite(6, 1);
 digitalWrite(7, 0);
 digitalWrite(8, 1);
 delay(1000);
 // 1 Yazdır.
 digitalWrite(2, 0);
 digitalWrite(3, 1);
 digitalWrite(4, 1);
 digitalWrite(5, 0);
 digitalWrite(6, 0);
 digitalWrite(7, 0);
 digitalWrite(8, 0);
 delay(1000);
 // 0 Yazdır (ve bum)
 digitalWrite(2, 1);
 digitalWrite(3, 1);
 digitalWrite(4, 1);
 digitalWrite(5, 1);
 digitalWrite(6, 1);
 digitalWrite(7, 1);
 digitalWrite(8, 0);
 delay(4000);
}
 
