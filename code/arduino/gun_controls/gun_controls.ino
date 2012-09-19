/**
  *  This is a sketch for reading data from an accelerometer and piping it
  *  directly across to serial.
  *
  *  borrowed from http://bildr.org/2011/04/sensing-orientation-with-the-adxl335-arduino/
  */

#include "Event.h"

//Analog read pins
const int xPin = 1;
const int yPin = 2;
const int zPin = 3;
//Digital read pins
const int buttonPin = 2;
const int ledPin = 13; // for debugging

//The minimum and maximum values that came from
//the accelerometer while standing still
//You very well may need to change these
int minVal = 301;
int maxVal = 401;

//to hold the caculated values
double x;
double y;
double z;

//Events to trigger
Event up('B', 290, 308);
Event down('F', 37, 55);
Event left('L', 111, 160);
Event right('R', 293, 318);

// Variables will change:
int lastButtonState = HIGH;   // the previous reading from the input pin
                              // HIGH since this is a pull up button
boolean fired = false; // have we already fired?
// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup(){
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as input
  pinMode(buttonPin, INPUT);
  // connect the commit pin to the pull up resistor
  digitalWrite(buttonPin, HIGH);
}

void loop(){

  //read the analog values from the accelerometer
  int xRead = analogRead(xPin);
  int yRead = analogRead(yPin);
  int zRead = analogRead(zPin);

  //convert read values to degrees -90 to 90 - Needed for atan2
  int xAng = map(xRead, minVal, maxVal, -90, 90);
  int yAng = map(yRead, minVal, maxVal, -90, 90);
  int zAng = map(zRead, minVal, maxVal, -90, 90);

  //Caculate 360deg values like so: atan2(-yAng, -zAng)
  //atan2 outputs the value of -π to π (radians)
  //We are then converting the radians to degrees.
  //These are the rotations about each axis
  x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
  y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);

  up.evaluate(y);
  down.evaluate(y);
  left.evaluate(x);
  right.evaluate(x);
  
  Serial.print(up.serialOut());
  Serial.print(down.serialOut());
  Serial.print(left.serialOut());
  Serial.print(right.serialOut());
  
  /************ Look for button presses ********************/
   // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button 
  // (i.e. the input went from LOW to HIGH),  and you've waited 
  // long enough since the last press to ignore any noise:  

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  } 
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:
    if(reading == LOW && !fired) {
      Serial.print('!');
      digitalWrite(ledPin, HIGH);
      fired = true;
    } else if (reading == HIGH) {
      // when the button is let go, reset the fired flag so
      // we can fire next time the button is pushed.
      fired = false;
      digitalWrite(ledPin, LOW);
    }
  }

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
  /******************************************************/

  delay(100);//just here to slow down the serial output - Easier to read
}

