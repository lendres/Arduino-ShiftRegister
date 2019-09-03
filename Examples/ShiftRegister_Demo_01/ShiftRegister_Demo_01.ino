#include "ShiftRegister.h"

/*
Hardware connections:

  Shift register:

    Plug in the chip so it bridges the center "canyon"
    on the breadboard.

    The shift register has 16 pins. They are numbered
    counterclockwise starting at the pin 1 mark (notch
    in the end of the chip). See the datasheet above
    for a diagram.

    74HC595 pin     LED pin     Arduino pin

    1  (QB)     LED 2 +
    2  (QC)     LED 3 +
    3  (QD)     LED 4 +
    4  (QE)     LED 5 +
    5  (QF)     LED 6 +
    6  (QG)     LED 7 +
    7  (QH)     LED 8 +
    8  (GND)                GND

    9  (QH*)
    10 (SRCLR*)             5V
    11 (SRCLK)              Digital 3
    12 (RCLK)               Digital 4
    13 (OE*)                GND
    14 (SER)                Digital 2
    15 (QA)     LED 1 +
    16 (VCC)                5V
*/


// Shift register pins.
int dataPin   = 2; 
int clockPin  = 3;
int latchPin  = 4;

ShiftRegister lights(8, dataPin, clockPin, latchPin);

void setup()
{
}

void loop()
{
  // We're going to use the same functions we played with back
  // in circuit 04, "Multiple LEDs", we've just replaced
  // digitalWrite() with a new function called shiftWrite()
  // (see below). We also have a new function that demonstrates
  // binary counting.

  // To try the different functions below, uncomment the one
  // you want to run, and comment out the remaining ones to
  // disable them from running.

  oneOnAtATime();
}

/*
oneOnAtATime()

This function will step through the LEDs, lighting one at at time.
*/

void oneOnAtATime()
{
  // Time (milliseconds) to pause between LEDs.
  int delayTime = 200;

  // step through the LEDs, from 0 to 7

  for(int i = 3; i < 8; i++)
  {
    lights.set(i, HIGH);
    delay(delayTime);       // pause to slow down the sequence
    lights.set(i, LOW);
  }
}
