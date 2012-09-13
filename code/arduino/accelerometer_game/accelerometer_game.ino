/**
  *  This is a sketch for reading data from an accelerometer, thresholding it,
  *  and sending events across the serial port when appropriate.
  *
  *  By Valkyrie Savage and Shiry Ginosar in 2012.
  *  Released into the wild!
  */

#include "Axis.h"

// Axes to measure
Axis x('x', 1, 150, 150);
Axis y('y', 2, 150, 150);
Axis z('z', 3, 150, 150);

void setup(){
  Serial.begin(9600);
}

void loop(){
  x.takeReading();
  y.takeReading();
  z.takeReading();
  
  Serial.print(x.serialOut());
  Serial.print(y.serialOut());
  Serial.print(z.serialOut());
  
  delay(100);  // gotta slow this down to human speeds so we don't get crayzeeee
}
