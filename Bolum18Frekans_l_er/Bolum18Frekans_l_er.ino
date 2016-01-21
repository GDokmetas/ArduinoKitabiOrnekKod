volatile unsigned long timerCounts;
volatile boolean counterReady;


unsigned long overflowCount;
unsigned int timerTicks;
unsigned int timerPeriod;

void startCounting (unsigned int ms) 
  {
  counterReady = false;         // zaman hazır değil
  timerPeriod = ms;             // zaman periyodu ms
  timerTicks = 0;               // kesme tezgâhını sıfırla
  overflowCount = 0;            // taşma yok

  // Timer 1 ve 2 yi sıfırla
  TCCR1A = 0;             
  TCCR1B = 0;              
  TCCR2A = 0;
  TCCR2B = 0;

  // Timer 1 5. bacaktaki olayları sayar
  TIMSK1 = bit (TOIE1);   // Taşma halinde kesmeyi aç
  TCCR2A = bit (WGM21) ;   
  OCR2A  = 124;            
  // Timer 2 – Eşleşmede kesmeyi aç
  TIMSK2 = bit (OCIE2A);   // Timer 2 kesmesini aç

  TCNT1 = 0;      // İki zamanlayıcıyı sıfırla
  TCNT2 = 0;     

  GTCCR = bit (PSRASY);          
  TCCR2B =  bit (CS20) | bit (CS22) ;  
  TCCR1B =  bit (CS10) | bit (CS11) | bit (CS12);
  }  

ISR (TIMER1_OVF_vect)
  {
  ++overflowCount;               
  }  // end of TIMER1_OVF_vect


ISR (TIMER2_COMPA_vect) 
  {
  unsigned int timer1CounterValue;
  timer1CounterValue = TCNT1;  // see datasheet, page 117 (accessing 16-bit registers)
  unsigned long overflowCopy = overflowCount;

  
  if (++timerTicks < timerPeriod) 
    return;  // not yet

  if ((TIFR1 & bit (TOV1)) && timer1CounterValue < 256)
    overflowCopy++;


  TCCR1A = 0;    
  TCCR1B = 0;    

  TCCR2A = 0;    
  TCCR2B = 0;    

  TIMSK1 = 0;    
  TIMSK2 = 0;    
  
  timerCounts = (overflowCopy << 16) + timer1CounterValue;  
  counterReady = true;              
  }  

void setup () 
  {
  Serial.begin(115200);       
  Serial.println("Frequency Counter");
  } 

void loop () 
  {
  
  byte oldTCCR0A = TCCR0A;
  byte oldTCCR0B = TCCR0B;
  TCCR0A = 0;    
  TCCR0B = 0;    
  
  startCounting (500);  
  while (!counterReady) 
     { }  

  
  float frq = (timerCounts *  1000.0) / timerPeriod;

  Serial.print ("Frequency: ");
  Serial.print ((unsigned long) frq);
  Serial.println (" Hz.");
  
  
  TCCR0A = oldTCCR0A;
  TCCR0B = oldTCCR0B;
  
  
  delay(200);
  }   

