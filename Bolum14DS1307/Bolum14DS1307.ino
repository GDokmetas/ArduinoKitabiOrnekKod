

#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

void setup () {
  Serial.begin(57600); // Baud Rate 57600 dikkat edin. 
  
#ifdef AVR
  Wire.begin();
#else
  Wire1.begin(); 
#endif

  rtc.begin();
  
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Bu fonksiyon ile saat devresinin saati kodun derlendiği zamana göre
  // ayarlanır ve bilgisayar saati ile arasında çok küçük bir farkla saat çalışmaya başlar. Saat bir kere ayarlandıktan
  // sonra bir daha ayarlamaya gerek yoktur. 
  
  if (! rtc.isrunning()) { // Eğer RTC çalışmıyorsa 
    Serial.println("RTC Çalışmıyor");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // 
  }
}

void loop () {
    DateTime now = rtc.now();
    
    Serial.print(now.year(), DEC); // Yılı Yazdır. 
    Serial.print('/');
    Serial.print(now.month(), DEC); // Ayı Yazdır. 
    Serial.print('/');
    Serial.print(now.day(), DEC); // Günü Yazdır. 
    Serial.print(' ');
    Serial.print(now.hour(), DEC); // Saati Yazdir
    Serial.print(':');
    Serial.print(now.minute(), DEC); // Dakikayı yazdır. 
    Serial.print(':');
    Serial.print(now.second(), DEC); // Saniyeyi yazdır. 
    Serial.println();

    Serial.println();
    delay(3000);
}
