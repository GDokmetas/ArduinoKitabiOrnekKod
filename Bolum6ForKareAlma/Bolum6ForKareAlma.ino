void setup() {
Serial.begin(9600);
for (int i=0; i<=20; i++) 
{
  Serial.print(i);  //önce sayıyı yazdır. 
  Serial.print("   "); //Boşluk koy
  Serial.println(i*i); //Sonra karesini yazdır. 
}
}

void loop() {

}
