int ogrencinotlari [4] [5] 
{ { 85, 50, 45, 26, 55} , 
  { 65, 44, 22, 56, 90} ,
  { 58, 55, 69, 80, 22} ,
  { 88, 55, 65, 20, 0 } 
};

void setup() {
Serial.begin(9600);
for (int i=0; i<4 ; i++)
{
  Serial.print("Ogrenci:");
  Serial.println(i);
  Serial.print("Notlar: ");
for (int j=0; j<5; j++)
{
  Serial.print(ogrencinotlari[i][j]);
  Serial.print(" ");
}
Serial.println();
}
}
void loop() {

}
