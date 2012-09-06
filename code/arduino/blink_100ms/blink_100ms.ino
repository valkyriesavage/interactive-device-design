/*
  Blink
  Turns on an LED on for 100ms, then off for 100ms, FOREVER.
 
  This example code is adopted from the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;
int timer_ms = 100;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(timer_ms);               // wait for some time
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(timer_ms);               // wait for some time
}
