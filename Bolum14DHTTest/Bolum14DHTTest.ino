
/* DHT AYARLARI */ 
#include "DHT.h"
#define DHTPIN 2     // DHT veri ayağının bağlandığı bacağı tanımlayın. 
// Hangi DHT Algılayıcısı kullanılıyorsa onlardan biri seçilmeli
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE); // DHT nesnesi tanımla 
/* DHT AYARLARI */ 


void setup() {
  Serial.begin(9600);
  Serial.println("DHT Sensor Test!");
  dht.begin(); // DHTyi başlat.
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

// Yeni okuma için biraz bekle. 
  float h = dht.readHumidity(); // Nem oku. Floata Aktar.

  float t = dht.readTemperature(); // Sıcaklığı oku ve aktar. 


  // Eğer okuma hatalıysa hata mesajı yolla.
  if (isnan(h) || isnan(t) || ) {
    Serial.println("DHT algilayicisindan veri okunamadi!");
    return;
  }

  // Isı indeksini hesapla.
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("NEM: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("SICAKLIK: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print("Sicaklik Indeksi: ");
  Serial.print(hic);
  Serial.print(" *C ");

}
