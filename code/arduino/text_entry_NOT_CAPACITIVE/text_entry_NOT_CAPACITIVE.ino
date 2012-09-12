/**
  * A simple program for reading 5-key keyboard text entry from an Arduino.
  *
  * This code is released into the wild by me, Valkyrie Savage, in 2012.  :)
  */

// the four pins used for the keys
const int BUTTONS[] = {2, 3, 4, 5, 7};
const int NUM_BUTTONS = 5;

// the threshold that we consider a touch
const int THRESHOLD = 1;

void setup() {
  for (int pin_idx = 0; pin_idx < NUM_BUTTONS; pin_idx++) {
    configurePin(BUTTONS[pin_idx]);
  }
  Serial.begin(9600);
}

// keep track of timeouts and state changes
int lastBounces[] = {0,0,0,0,0};
int lastStates[] = {LOW,LOW,LOW,LOW,LOW};
int realStates[] = {LOW,LOW,LOW,LOW,LOW};
const int TIMEOUT = 100;

// did we already output this command to serial?
boolean output = false;

void loop() {
  for (int pin_idx = 0; pin_idx < NUM_BUTTONS; pin_idx++) {
    int pin = BUTTONS[pin_idx];
    int hit = digitalRead(pin);

    if (hit != lastStates[pin_idx]) {
      lastBounces[pin_idx] = millis();
    }
    
    if ((millis() - lastBounces[pin_idx]) > TIMEOUT) {
      if (hit && realStates[pin_idx] != hit) {
        // we just changed to this state
        char toSend = 'q';
        switch(pin_idx) {
          case 0:
            toSend = 'l';
            break;
          case 1:
            toSend = 'u';
            break;
          case 2:
            toSend = 'r';
            break;
          case 3:
            toSend = 'd';
            break;
          case 4:
            toSend = 's';
            break;
        }
        Serial.println(toSend);
      }
      realStates[pin_idx] = hit;
    }
    
    lastStates[pin_idx] = hit;
  }
}

// set the pin up to work
void configurePin(int pin) {
  pinMode(pin, INPUT);
  digitalWrite(pin, HIGH);
}
