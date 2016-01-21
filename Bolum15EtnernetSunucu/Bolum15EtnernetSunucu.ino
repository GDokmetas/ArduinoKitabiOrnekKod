/*
  Web Server

 A simple web server that shows the value of the analog input pins.
 using an Arduino Wiznet Ethernet shield.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)

 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe

 */

#include <SPI.h>
#include <Ethernet.h>


byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 177);

EthernetServer server(80); // 80 (HTTP) portunda sunucuyu başlat. 

void setup() {

  Serial.begin(9600);



  // Ethernet bağlantısını yap ve sunucuyu başlar. 
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("Server IP:  ");
  Serial.println(Ethernet.localIP());
}


void loop() {

  EthernetClient client = server.available(); // Gelen istemcileri dinle
  if (client) {
    Serial.println("Yeni Istemci");
    // Boş satırla HTTP isteği sona erer.
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
       // HTTP isteği bitince cevap yolla. 
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  
          client.println("Refresh: 5");  // Sayfa yenileme
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // output the value of each analog input pin
          
            int sensorReading = analogRead(A0);
            float mv = ( sensorReading/1024.0)*1000;
            float cel = mv/10;
            client.print("SICAKLIK: ");
            String cel2 = String(cel);
            client.print(cel2);
            Serial.print(cel2);
            client.print(" C");
            client.println("<br />");
        
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          
          currentLineIsBlank = false;
        }
      }
    }
    // Tarayıcıya verileri alması için zaman ver 
    delay(1);
    // bağlantiyi bitir.
    client.stop();
    Serial.println("istemci cikti");
  }
}

