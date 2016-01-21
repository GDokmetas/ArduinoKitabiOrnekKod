void setup() {
  
  Serial.begin(9600);
  while (!Serial) {
    ; 
  }

 
  Serial.println("\n\nString Yapicilari:");
  Serial.println();
}

void loop() {
  // String sabiti kullanilmasi
  String stringOne = "Merhaba Dunya"; // Merhaba Dunya Yazar
  Serial.println(stringOne);     

  // Karakter Degerini Stringe Cevirir
  stringOne =  String('a');
  Serial.println(stringOne);       // A yazar

  // String sabitini string nesnesine çevirir ve yazdırır
  String stringTwo =  String("Bu bir Stringdir");
  Serial.println(stringTwo);      // Bu bir stringdir yazdirir.

  // İki string değerini toplamak
  stringOne =  String(stringTwo + " ve buraya yazilmistir.");
  // Bu bir stringdir ve buraya yazilmistir yazdirir. 
  Serial.println(stringOne);

  // İnteger sabiti kullanmak
  stringOne =  String(13);
  Serial.println(stringOne);      // 13 yazdırır.

  // İnteger değeriyle beraber bir temel kullanmak
  stringOne =  String(analogRead(A0), DEC);
  // Herhangi bir rakam yazdırır 300-400 arası analog girişten okunan değer neyse. 
  Serial.println(stringOne);

  // İnteger ve onun onaltılık tabanda yazılması
  stringOne =  String(45, HEX);
  // 2D ifadesini yazdırır. 45'in onaltılık tabandaki karşılığı olur. 
  Serial.println(stringOne);

  // İntegerin binary yani ikilik tabanda yazılması
  stringOne =  String(255, BIN);
  // 11111111 yazdırır. Yani 255 sayısının binary karşılığı.
  Serial.println(stringOne);

  // Long değerini bir temelle kullanış
  stringOne =  String(millis(), DEC);
  // prints "123456" or whatever the value of millis() is:
  Serial.println(stringOne);

  //Float Kullanımı
  stringOne = String(5.698, 3);
  Serial.println(stringOne);

  //Yuvarlama kullanmak için daha az bir ondalık taban sayısı kullanılmıştır.
  stringOne = String(5.698, 2);
  Serial.println(stringOne);

  // Sonsuz Döngü
  while (true);

}
