#include <Servo.h>

Servo servo1;
Servo servo2;

void setup() {
  Serial.begin(9600);
  servo1.attach(9);
  servo2.attach(10);
  servo1.write(0);
  servo2.write(0);  
}

void loop() {
 for (int i = 0; i <= 90; i++)
  {
    servo1.write(i);
    servo2.write(i);
  }
  delay(1000);
  for (int i = 89; i > 0; i--)
  {
    servo1.write(i);
    servo2.write(i);
  }
  delay(5000);
}
