/*
  Axis.h - Library for acceleromter reading and processing.
  Created by Valkyrie Savage and Shiry Ginosar in 2012.
  Released into the wild!
*/
#ifndef Axis_h
#define Axis_h

#include "Arduino.h"

class Axis
{
  public:
    Axis(char label, int pin, int lowThresh, int highThresh);
    void takeReading();
    String serialOut();
  private:
    int _pin;
    char _label;
    int _minValue;
    int _maxValue;
    int _reading;
    int _prevReading;
    int _lowThresh;
    int _highThresh;
    boolean _on;
};

#endif
