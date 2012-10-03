/**
 * Some simple code for reading a sensor and printing it over serial.
 *
 * released into the wild by Mark, Shiry, & Valkyrie in 2012
 */

const int HUMIDITY_SENSOR = 3;

void setup() {
  pinMode(SENSOR, INPUT); 
}

void loop() {
  Serial.write(analogRead(HUMIDITY_SENSOR));
  delay(10);
}
