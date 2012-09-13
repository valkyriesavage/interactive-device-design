/*
  Axis.cpp - Library for accelerometer axis processing
  Created by Valkyrie Savage and Shiry Ginosar in 2012
  Released into the wild!
*/

#include "Arduino.h"
#include "Axis.h"

Axis::Axis(char label, int pin, int lowThresh, int highThresh) {
  _pin = pin;
  _label = label;
  _minValue = 100000;
  _maxValue = -100000;
  _reading = 0;
  _prevReading = 0;
  _lowThresh = lowThresh;
  _highThresh = highThresh;
  _on = false;
}

void Axis::takeReading() {
  _prevReading = _reading;
  _reading = analogRead(_pin);
  
  if ((_reading >= _highThresh) && (_prevReading < _highThresh)) {
    _on = true;
  }
  if ((_reading < _lowThresh) && (_prevReading >= _lowThresh)) {
    _on = false;
  }
  
  if(_reading < _minValue) _minValue = _reading;
  if(_reading > _maxValue) _maxValue = _reading;
}

String Axis::serialOut() {
  if (_on) {
    return _label + "";
  }
  return "";
}
