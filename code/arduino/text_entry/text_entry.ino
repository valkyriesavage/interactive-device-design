/**
  * A simple program for reading chorded keyboard text entry from an Arduino.
  *
  * This code is released into the wild by me, Valkyrie Savage, in 2012.  :)
  */

// the four pins used for the keys
const int KEYS[] = {2, 3, 4, 5, 6};
const int NUM_KEYS = 5;

// the threshold that we consider a touch
const int THRESHOLD = 1;

void setup() {
  for (int pin_idx = 0; pin_idx < NUM_KEYS; pin_idx++) {
    configurePin(KEYS[pin_idx]);
  }
  Serial.begin(9600);
}

// a timer to keep track of timeouts
int timer = 0;
const int TIMEOUT = 50;

// the hit code that we can decode letters from
int code = 0;

// did we already output this letter to serial?
boolean output = false;

void loop() {
  int hitsThisLoop = 0;
  for (int pin_idx = 0; pin_idx < NUM_KEYS; pin_idx++) {
    int pin = KEYS[pin_idx];
    if (hit(pin)) {
      code |= 1 << pin_idx;
      hitsThisLoop |= 1;
    }
  }

  // only count towards timeout if we are getting data
  if (code > 0)  {
    timer++;
  }
  if (hitsThisLoop == 0) {
    // we need to reset when the user lifts all his/her fingers
    output = false;
    timer = 0;
  }

  if (timer > TIMEOUT) {
    if(!output) {
      Serial.print(decode(code));  
      output = true;
    }
    code = 0;
    timer = 0;
  }
}

// taken from labs.teague.com/projects/ChordedKeyboard
char LETTERS[] = {
  '-',
  ' ',
  0x08,
  'n',
  '\n', // 4
  'o',
  'c',
  'r',
  'a', // 8
  'p',
  'e',
  't',
  'd', // 12
  's',
  'g',
  'n',
  'b', // 16
  'q',
  'f',
  'y',
  'm', // 20
  'x',
  'j',
  'z',
  'l', // 24
  'w',
  'k',
  'v',
  'h', // 28
  'u',
  'i',
  '...' // everything pressed (cancel).
};

char decode(int code) {
  return LETTERS[code];
}

// set the pin up to work with the capacitive library
void configurePin(int pin) {
  pinMode(pin, INPUT);
}

// determine whether the pin is hit
boolean hit(int pin) {
  return readCapacitivePin(pin) > THRESHOLD;
}

// shamelessly borrowed from arduino.cc/playground/Code/CapacitiveSensor
// readCapacitivePin
//  Input: Arduino pin number
//  Output: A number, from 0 to 17 expressing
//  how much capacitance is on the pin
//  When you touch the pin, or whatever you have
//  attached to it, the number will get higher
uint8_t readCapacitivePin(int pinToMeasure) {
  // Variables used to translate from Arduino to AVR pin naming
  volatile uint8_t* port;
  volatile uint8_t* ddr;
  volatile uint8_t* pin;
  // Here we translate the input pin number from
  //  Arduino pin number to the AVR PORT, PIN, DDR,
  //  and which bit of those registers we care about.
  byte bitmask;
  port = portOutputRegister(digitalPinToPort(pinToMeasure));
  ddr = portModeRegister(digitalPinToPort(pinToMeasure));
  bitmask = digitalPinToBitMask(pinToMeasure);
  pin = portInputRegister(digitalPinToPort(pinToMeasure));
  // Discharge the pin first by setting it low and output
  *port &= ~(bitmask);
  *ddr  |= bitmask;
  delay(1);
  // Make the pin an input with the internal pull-up on
  *ddr &= ~(bitmask);
  *port |= bitmask;
  // Now see how long the pin to get pulled up
  int cycles = 17;
  for(int i = 0; i < 16; i++){
    if (*pin & bitmask){
      cycles = i;
      break;
    }
  }
  // Discharge the pin again by setting it low and output
  //  It's important to leave the pins low if you want to 
  //  be able to touch more than 1 sensor at a time - if
  //  the sensor is left pulled high, when you touch
  //  two sensors, your body will transfer the charge between
  //  sensors.
  *port &= ~(bitmask);
  *ddr  |= bitmask;

  return cycles;
}
