// Code for Mechanical Iris portion of the DorkbotPDX Exquiste Corpse Project (http://dorkbotpdx.org/blog/breedx/exquisite_corpse)
// Brian Richardson (bzzt@knowhere.net)

#include <Servo.h>

#define FULL_OPEN 69
#define STEP_DELAY 8
#define STATE_DELAY 15000

#define ENABLE_PIN 14
#define OPEN_PIN 15

#define DEBOUNCE_DELAY 50

Servo servo1;
int irisState = 0;

void configPin(int pin_index)
{
   pinMode(pin_index, INPUT);
   digitalWrite(pin_index, HIGH);
}

void setup()
{
   servo1.attach(9);
   servo1.write(0);
   servo1.detach();
   delay(STATE_DELAY);

   configPin(ENABLE_PIN);
   configPin(OPEN_PIN);
}

void open_iris()
{
   servo1.attach(9);
   for (int i = 0; i <= FULL_OPEN; i++) {
      servo1.write(i);
      delay(STEP_DELAY);
   }
   irisState = 1;
   servo1.detach();

}

void close_iris()
{
  servo1.attach(9);
   for (int i = FULL_OPEN; i >= 0; i--)
   {
      servo1.write(i);
      delay(STEP_DELAY);
   }
   irisState = 0;
   servo1.detach();
}

// Self running mode
void self_loop()
{
   open_iris();

   delay(STATE_DELAY);

   close_iris();

   delay(STATE_DELAY);
}

// External control mode
void external_loop()
{
   int curr_state = digitalRead(OPEN_PIN);
   // pin high = iris closed
   if (curr_state == HIGH)
   {
      if (irisState != 0)
      {
         close_iris();
      }
   } else {
      // pin low = iris open
      if (irisState != 1)
      {
         open_iris();
      }
   }
}

void loop()
{
   if (digitalRead(ENABLE_PIN) == 0)
   {
      external_loop();
   } else {
      self_loop();
   }
}
