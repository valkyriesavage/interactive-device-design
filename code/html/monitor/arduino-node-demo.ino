/*
 Send two channels of A2D data to node.js
 Adapted from
 http://www.arduino.cc/en/Tutorial/Graph
 */

void setup() {
  // initialize the serial communication:
  Serial.begin(9600);
}

void loop() {
  // send the value of analog inputs 0 and 1:
  Serial.print(analogRead(A0));
  Serial.print(" ");
  Serial.println(analogRead(A1)); //note "\n" line end in println

  
  // wait a bit for the analog-to-digital converter 
  // to stabilize after the last reading:
  delay(2);
}