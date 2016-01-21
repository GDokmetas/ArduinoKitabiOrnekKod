#include <SPI.h>

#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>



byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 1, 190 };
byte gateway[] = { 192, 168, 1, 1 };
byte subnet[] = { 255, 255, 255, 0 };
EthernetServer server(80);

void setup()
{
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
}

void loop()
{
  EthernetClient client = server.available();
  if (client) {
  
    boolean current_line_is_blank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
     
        if (c == '\n' && current_line_is_blank) {
         
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<h1>Arduino Oyun Merkezi</h1>");
          client.println("<title>Arduino Oyun Merkezi</title>");
          client.println("<object width='550' height='400'>");
          client.println("<param name='movie' value='http://gameswf.weebly.com/uploads/2/0/0/6/20065369/3dmissle.swf'>");
          client.println("<embed src='http://gameswf.weebly.com/uploads/2/0/0/6/20065369/3dmissle.swf' width='1000' height='750'>");
          client.println("</embed>");
          client.println("</object>");
        
          client.println("<body bgcolor='Teal'>");
          client.println("");
          client.println("Gokhan Dokmetas tarafindan duzenlenmistir");
          client.println("Arduino.cc webserver orjinal kodu baz alinmistir");
          break;
        }
        if (c == '\n') {
    
          current_line_is_blank = true;
        } else if (c != '\r') {
        
          current_line_is_blank = false;
        }
      }
    }
    
    delay(1);
    client.stop();
  }
}
