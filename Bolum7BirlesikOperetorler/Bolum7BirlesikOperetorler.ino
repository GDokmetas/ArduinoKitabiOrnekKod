int x = 0;

void setup() {
Serial.begin(9600);
x++;
Serial.println(x);
x+=50;
Serial.println(x);
x--;
Serial.println(x);
x-=10;
Serial.println(x);
x*=20;
Serial.println(x);
x/=10;
Serial.println(x);
x%=2;
Serial.println(x);
}

void loop() {


}
