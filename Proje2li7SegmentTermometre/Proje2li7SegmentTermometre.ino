

SevSeg sevseg;

int tempUnits = celsius; 

int refreshTime = 5000; 

unsigned long timer;
float celsius = 0, kelvin = 0, fahrenheit = 0;

void setup()
{
sevseg.Begin(0,2,3,4,5,6,7,8,9,10,11,12,13);
}

void loop()
{
sevseg.PrintOutput();

kelvin = analogRead(0) * 0.004882812 * 100;

celsius = kelvin – 2.5 – 273.15;

fahrenheit = ((kelvin – 2.5) * 9 / 5) – 459.67;

unsigned long mils=millis();
if (mils-timer>=refreshTime) {
timer=mils;

sevseg.NewNum(tempUnits,(byte) 2);
}
}
