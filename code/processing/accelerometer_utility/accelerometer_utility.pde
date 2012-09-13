/**
 * This is for graphing the output of the accelerometer's (described in the
 * Arduino sketch accelerometer_test) three axes.  It is a utility which can
 *
 * 1) graph all 3 axes
 * 2) visualize whether data exceeds given thresholds
 * 3) allow changing of those thresholds
 */

import processing.serial.*;
 
Serial myPort;
float xReading = 0;
float yReading = 0;
float zReading = 0;

int deg0 = 0;
int deg360 = 360;

int[] xThreshes = {0,0};
int[] yThreshes = {0,0};
int[] zThreshes = {0,0};

color firstThresh = color(255,0,0);
color secondThresh = color(0,255,0);
color base = color(0,0,255);

int horzPos = 1;
 
void setup () {
  size(900, 600);        
 
  // List all the available serial ports
  println(Serial.list());
  // I know that the first port in the serial list on my mac
  // is always my  Arduino, so I open Serial.list()[0].
  // Open whatever port is the one you're using.
  myPort = new Serial(this, Serial.list()[0], 9600);
  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');
  // set inital background:
  background(0);
}

void draw () {
  if (horzPos == width) {
    horzPos = 1;
    background(0);
    stroke(firstThresh);
    line(0, xThreshes[0], width, xThreshes[0]);
    line(0, yThreshes[0] + height/3, width, yThreshes[0] + height/3);
    line(0, zThreshes[0] + 2*height/3, width, zThreshes[0] + 2*height/3);
    stroke(secondThresh);
    line(0, xThreshes[1], width, xThreshes[1]);
    line(0, yThreshes[1] + height/3, width, yThreshes[1] + height/3);
    line(0, zThreshes[1] + 2*height/3, width, zThreshes[1] + 2*height/3);
    stroke(base);
    line(0, height/3, width, height/3);
    line(0, 2*height/3, width, 2*height/3);
  }
  
  line(horzPos, height/3, horzPos, xReading);
  line(horzPos, 2*height/3, horzPos, yReading);
  line(horzPos, height, horzPos, zReading);
  
  if(xReading > xThreshes[0]) {
    stroke(secondThresh);
    line(horzPos, height/3, horzPos, xReading);
  }
  if(yReading > yThreshes[0]) {
    stroke(secondThresh);
    line(horzPos, 2*height/3, horzPos, yReading);  
  }
  if(zReading > zThreshes[0]) {
    stroke(secondThresh);
    line(horzPos, height, horzPos, zReading);  
  }
}
 
void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');
 
  if (inString != null) {
    inString = trim(inString);
    // convert to an int and map to the screen height:
    // the format for the string is x: vvv | y: vvv | z: vvv
    // where vvv is a three-digit integer representing the value
    int xBeg = "x: ".length();
    int xEnd = "x: vvv".length();
    float xIn = float(inString.substring(xBeg, xEnd)); 
    xIn = map(xIn, deg0, deg360, 0, height/3);
    xReading = xIn;
    
    int yBeg = "x: vvv | y: ".length();
    int yEnd = "x: vvv | y: vvv".length();
    float yIn = float(inString.substring(yBeg, yEnd)); 
    yIn = map(yIn, deg0, deg360, 0, height/3);
    yReading = yIn;
    
    int zBeg = "x: vvv | y: vvv | z: ".length();
    int zEnd = "x: vvv | y: vvv | z: vvv".length();
    float zIn = float(inString.substring(zBeg, zEnd)); 
    zIn = map(zIn, deg0, deg360, 0, height/3);
    zReading = zIn;
    
    horzPos++;
  }
}
