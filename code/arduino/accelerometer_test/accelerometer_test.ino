/**
  *  This is a sketch for reading data from an accelerometer and piping it
  *  directly across to serial.
  *
  *  borrowed from http://bildr.org/2011/04/sensing-orientation-with-the-adxl335-arduino/
  */

//Analog read pins
const int xPin = 1;
const int yPin = 2;
const int zPin = 3;

//The minimum and maximum values that came from
//the accelerometer while standing still
//You very well may need to change these
int minVal = 301;
int maxVal = 404;

//to hold the caculated values
double x;
double y;
double z;

void setup(){
  Serial.begin(9600);
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
  //We are then converting the radians to degrees
  x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
  y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);

  //Output the caculations
  Serial.print("x: ");
  printDigits(x);
  Serial.print(" | y: ");
  printDigits(y);
  Serial.print(" | z: ");
  printDigits(z);
  Serial.println();

  delay(100);//just here to slow down the serial output - Easier to read
}

void printDigits(int digit) {
  if(digit < 100) {
    Serial.print("0");
  } if (digit < 10) {
    Serial.print("0");
  } Serial.print(digit); 
}
