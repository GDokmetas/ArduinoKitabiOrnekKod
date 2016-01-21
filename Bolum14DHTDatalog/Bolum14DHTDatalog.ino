#include <SPI.h>
#include <SD.h>


/* DHT AYARLARI */ 
#include "DHT.h"
#define DHTPIN 4     // DHT veri ayağının bağlandığı bacağı tanımlayın. 
// Hangi DHT Algılayıcısı kullanılıyorsa onlardan biri seçilmeli
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE); // DHT nesnesi tanımla 
/* DHT AYARLARI */ 


const int chipSelect = 10; //SD CS/SS bacağı

void setup() {
  Serial.begin(9600);
  Serial.println("DHT Sensor Test!");
  dht.begin(); // DHTyi başlat.

  
  Serial.println("SD KART YUKLENIYOR");  // KART KONTROL
  if (!SD.begin(chipSelect)) {
  Serial.println("SD KART TANINMADI");
  }
  Serial.println("SD KART TANINDI VE HAZIR");

  if (!SD.exists("datalog.txt"))  // Eğer dosya yoksa yenisini oluştur
  { 
  SD.open("datalog.txt");
  Serial.println("Yeni Datalog.txt Dosyası Acildi"); 
  }
  else 
  { Serial.println("Datalog.txt Bulundu"); } // TXT dosyası Kontrolü

  
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

// Yeni okuma için biraz bekle. 
  float h = dht.readHumidity(); // Nem oku. Floata Aktar.

  float t = dht.readTemperature(); // Sıcaklığı oku ve aktar. 


  // Eğer okuma hatalıysa hata mesajı yolla.
  if (isnan(h) || isnan(t) ) {
    Serial.println("DHT algilayicisindan veri okunamadi!");
    return;
  }

  // Isı indeksini hesapla.
  float hic = dht.computeHeatIndex(t, h, false);
  // Seri Port Yazdirma Bölümü
  Serial.print("NEM: ");
  Serial.print(h);
  Serial.println(" %\t");
  Serial.print("SICAKLIK: ");
  Serial.print(t);
  Serial.println(" *C ");
  Serial.print("Sicaklik Indeksi: ");
  Serial.print(hic);
  Serial.println(" *C ");
  
  // SD KAYDETME BÖLÜMÜ
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  dataFile.print("Zaman: "); dataFile.print(millis()/1000); // Geçen süreyi kaydet. (millis program başından itibaren geçen ms değerini verir.)
  dataFile.print(" Sicaklik: "); dataFile.print(t); // Sıcaklık Kaydet
  dataFile.print(" Nem: ") ; dataFile.println(h);  // Nem kaydet
  dataFile.close(); // Kapat ve Kaydet
  
}
