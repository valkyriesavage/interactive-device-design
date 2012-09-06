/**
  * Code for reading rotary position off the rotary bracelet and changing LED brightness.
  *
  * Released into the wild by Valkyrie, Shiry, Mark, and Peggy on September 5, 2012.
  */
  
const int LED = 13;
const int R0 = 2;
const int R1 = 3;
const int R2 = 4;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(R0, INPUT);
  pinMode(R1, INPUT);
  pinMode(R2, INPUT);
}

void loop() {
  int power = 0;
  // read the pins
  if(digitalRead(R0)) power += 127;
  if(digitalRead(R1)) power += 63;
  if(digitalRead(R2)) power += 31;
  analogWrite(LED, power);
  
  delay(100);
}
