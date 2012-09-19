/*
  Event.h - Library for accelerometer event processing.
  Created by Valkyrie Savage and Shiry Ginosar in 2012.
  Released into the wild!
*/
#ifndef Event_h
#define Event_h

#include "Arduino.h"

class Event
{
  public:
    Event(char label, double lowThresh, double highThresh);
    void evaluate(double currentReading);
    char serialOut();
  private:
    char _label;
    double _reading;
    double _prevReading;
    double _lowThresh;
    double _highThresh;
    boolean _on;
};

#endif
