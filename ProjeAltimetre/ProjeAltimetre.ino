
#include <SFE_BMP180.h>
#include <Wire.h>

// BMP180 nesnesi oluştur. 

SFE_BMP180 pressure;

double baseline;

void setup()
{
  Serial.begin(9600);
  Serial.println("BASLATMA");


  if (pressure.begin())
    Serial.println("BMP180 TANINDI");
  else
  {

    Serial.println("BMP180 TANINMADI HATA!!\n\n");
    while(1); 
  }


  
  baseline = getPressure();
  
  Serial.print("Baz Basinc: ");
  Serial.print(baseline);
  Serial.println(" mb");  
}

void loop()
{
  double a,P;
  
  // Basınç oku

  P = getPressure();

  // yüksekliği hesapla

  a = pressure.altitude(P,baseline);
  
  Serial.print("Goreceli Yukseklik: ");
  if (a >= 0.0) Serial.print(" "); // pozitif sayılar için boşluk ekle
  Serial.print(a,1);
  Serial.print(" metre ");
  if (a >= 0.0) Serial.print(" "); // pozitif sayılar için boşluk ekle
  
  delay(500);
}


double getPressure()
{
  char status;
  double T,P,p0,a;



  status = pressure.startTemperature();
  if (status != 0)
  {

    delay(status);

   

    status = pressure.getTemperature(T);
    if (status != 0)
    {


      status = pressure.startPressure(3);
      if (status != 0)
      {
     
        delay(status);

        
        status = pressure.getPressure(P,T);
        if (status != 0)
        {
          return(P);
        }
        else Serial.println("Basinc verisi alma hatasi \n");
      }
      else Serial.println("Hesaplama baslatma hatasi \n");
    }
    else Serial.println("Veri alma hatasi \n");
  }
  else Serial.println("sicaklik hatasi! \n");
}



