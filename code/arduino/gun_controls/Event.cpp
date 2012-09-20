#include "Arduino.h"
#include "Event.h"

Event::Event(char label, double lowThresh, double highThresh, boolean fromAbove) {
  _label = label;
  _reading = 0;
  _prevReading = 0;
  _lowThresh = lowThresh;
  _highThresh = highThresh;
  _fromAbove = fromAbove;
  _on = false;
  _lastPrintTime = millis();
}

void Event::evaluate(double currentReading) {
  _prevReading = _reading;
  _reading = currentReading;
  
  // For events from above
  if (_fromAbove) {
    if ((_reading >= _highThresh) && (_prevReading < _highThresh)) {
      _on = false;
    }
    if ((_reading < _lowThresh) && (_prevReading >= _lowThresh)) {
      _on = true;
    }
  } else { // events is from below
    if ((_reading >= _highThresh) && (_prevReading < _highThresh)) {
      _on = true;
    }
    if ((_reading < _lowThresh) && (_prevReading >= _lowThresh)) {
      _on = false;
    }
  }
}

char Event::serialOut() {
  if (_on && ((millis() - _lastPrintTime > 20) || (_label == '!'))) {
    _lastPrintTime = millis();
    return _label;
  }
  return NULL;
}
