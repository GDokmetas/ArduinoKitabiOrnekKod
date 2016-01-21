void setup()
{  
Serial.begin(9600);   

}   
void loop() 
{ 
  
 float volts = readVcc();
 Serial.print(volts/1000);
 Serial.println(" VDC");

 float temp = readTemp();
 temp = temp/1000;
 temp = temp + 25.7; //adjustment 

 Serial.print(temp);
 Serial.println(" C");
 delay(1000);
}   

long readVcc() {
  long result;
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2); 
  ADCSRA |= _BV(ADSC); 
  while (bit_is_set(ADCSRA,ADSC));
  result = ADCL;
  result |= ADCH<<8;
  result = 1126400L / result; 
  return result;
}

long readTemp() {
  long result;
 
  ADMUX = _BV(REFS1) | _BV(REFS0) | _BV(MUX3);
  delay(2); 
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA,ADSC));
  result = ADCL;
  result |= ADCH<<8;
  result = (result - 125) * 1075;
  return result;
}
