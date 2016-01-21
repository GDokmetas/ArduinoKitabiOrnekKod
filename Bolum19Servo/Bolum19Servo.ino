#include <Servo.h>

Servo servo1;

void setup() {
servo1.attach(9);
}

void loop() {
for (int i=0; i<255; i++)
{
servo1.write(i);
delay(10);
}
servo1.write(0);
delay(800);
}
