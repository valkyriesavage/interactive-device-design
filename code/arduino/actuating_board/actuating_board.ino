/**
 * Some simple code for writing to an actuator based on serial data.
 *
 * released into the wild by Mark, Shiry, & Valkyrie in 2012
 */

const int ACTUATOR = 13;

void setup() {
  pinMode(ACTUATOR, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    int incomingByte = Serial.read();
    
    if (incomingByte == 0x01) {
      digitalWrite(ACTUATOR, HIGH);
    } else if (incomingByte == 0x00) {
      digitalWrite(ACTUATOR, LOW);
    }
  }
}
