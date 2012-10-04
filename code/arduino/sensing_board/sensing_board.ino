/**
 * Some simple code for reading a sensor and printing it over serial.
 *
 * released into the wild by Mark, Shiry, & Valkyrie in 2012
 */

const int HUMIDITY_SENSOR = 0;
const int LED = 13;

const int ON_LENGTH = 20;

int onFor = 0;

void setup() {
  Serial.begin(9600);
  pinMode(HUMIDITY_SENSOR, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    int incoming = Serial.read();
    digitalWrite(LED, HIGH);
    onFor = 0;
  }
  
  if(onFor > ON_LENGTH) {
    digitalWrite(LED, LOW);
  }
  Serial.println(analogRead(HUMIDITY_SENSOR));
  delay(10);
  onFor++;
}
