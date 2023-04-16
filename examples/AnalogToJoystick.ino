#include "USBJoystick.h"

Joystick_ *Joystick = new Joystick_(); // it is important to make this instance here. If done in setup() it seems to be too late to work properly. The USB device just doesn't come up right

void setup() {
  // Initialize Joystick Library
  Joystick->setXAxisRange(0, 1024);
  sleep_ms(1000); // on some picos a delay is needed or the OS will go into an exception.
  Joystick->begin(true);
}

void loop() {
    // write one axis from an analog in to a joystick axis
  int xAxis;
  xAxis = analogRead(A0);
  Joystick->setXAxis(xAxis);
  sleep_ms(50);
}