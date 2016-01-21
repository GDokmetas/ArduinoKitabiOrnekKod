int dizi [5];
void setup() {
Serial.begin(9600);
dizi [0] = 55;
dizi [1] = 65;
dizi [2] = 10;
dizi [3] = 58;
dizi [4] = 2000;

for (int i=0 ; i<5 ; i++)
Serial.println(dizi[i]);
}

void loop() {

}
