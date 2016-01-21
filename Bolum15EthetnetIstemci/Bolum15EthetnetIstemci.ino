

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // Mac adresini ayarla.

char server[] = "www.google.com";    // bağlanacağımız sunucu google.com

//DHCP ile adres alinmazsa bu adresi belirle ve kullan
IPAddress ip(192, 168, 0, 177);

EthernetClient client; // Sunucuyu tanımla. IP adresi ve sunucunun portu ile

void setup() {
  // Seri iletişimi aç
  Serial.begin(9600);
 
  

  // bağlantıyı başlat.
  if (Ethernet.begin(mac) == 0) {
    Serial.println("DHCP Ayarlanmasi Yapilamadi");
//DHCP ayarlanması olmadığında sabit bir IP ile başlat. 
    Ethernet.begin(mac, ip);
  }
  // Ayarlanması için süre tanı
  delay(1000);
  Serial.println("baglaniyor...");

  // Eğer bağlantıyı alırsa cevap ver.
  if (client.connect(server, 80)) {
    Serial.println("baglanildi");
    // HTTP istegi yolla
    client.println("GET /search?q=arduino HTTP/1.1");
    client.println("Host: www.google.com");
    client.println("Connection: close");
    client.println();
  }
  else {
    // eğer baglanmazsa
    Serial.println("baglanilamadi...");
  }
}

void loop()
{
// Gelen bayt mevcutsa bunu yazdır. 
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // Baglanti biterse baglantiyi kes. 
  if (!client.connected()) {
    Serial.println();
    Serial.println("baglanti kesiliyor.");
    client.stop();

    // Birşey yapma. 
    while (true);
  }
}


