#include "Arduino.h"
#include "Event.h"

Event::Event(char label, double lowThresh, double highThresh) {
  _label = label;
  _reading = 0;
  _prevReading = 0;
  _lowThresh = lowThresh;
  _highThresh = highThresh;
  _on = false;
}

void Event::evaluate(double currentReading) {
  _prevReading = _reading;
  _reading = currentReading;
  
  // In our callibration, events always happen when crossing from above
  if ((_reading >= _highThresh) && (_prevReading < _highThresh)) {
    _on = false;
  }
  if ((_reading < _lowThresh) && (_prevReading >= _lowThresh)) {
    _on = true;
  }
}

char Event::serialOut() {
  if (_on) {
    return _label;
  }
  return NULL;
}
