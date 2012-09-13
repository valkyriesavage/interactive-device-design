/**
 * This is for graphing the output of the accelerometer's (described in the
 * Arduino sketch accelerometer_test) three axes.  It is a utility which can
 *
 * 1) graph all 3 axes
 * 2) visualize whether data exceeds given thresholds
 * 3) allow changing of those thresholds
 *
 * This code depends upon the control library for processing:
 *   http://code.google.com/p/controlp5/downloads/detail?name=controlP5-1.5.1.zip
 *   Just download that zip, and unzip it to a libraries/ folder inside your Processing
 *   sketchbook (like in Arduino).
 */

import processing.serial.*;
import controlP5.*;

Serial myPort;

int deg0 = 0;
int deg360 = 360;

ControlP5 cp5;

int LOW = 0;
int HIGH = 1;

color firstThresh = color(255,0,0);
color secondThresh = color(0,255,0);
color base = color(0,0,255);
color data = color(255);

color fg = color(0,91,255,40);
color bg = color(30,144,255,40);

int horzPos = 1;

int graphWid = 600;
int graphHt = 600;

Axis x, y, z;
 
void setup () {
  size(graphWid + deg360, graphHt);        
 
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
  
  // set up the nonsense for thresholding
  cp5 = new ControlP5(this);

  x = new Axis(0, graphHt/3, 'x');
  y = new Axis(graphHt/3, 2*graphHt/3, 'y');
  z = new Axis(2*graphHt/3, graphHt, 'z');

  // prepare for pretty data!
  cleanSlate();
}

void cleanSlate() {
  background(0);
  x.draw();
  y.draw();
  z.draw();
}

void draw () {
  if (horzPos >= graphWid) {
    horzPos = 1;
    cleanSlate();
  }
  horzPos++;
  
  x.draw();
  y.draw();
  z.draw();
}


void controlEvent(ControlEvent theControlEvent) {
  if(theControlEvent.isFrom(x.label())) {
    x.newThreshes(int(theControlEvent.getController().getArrayValue(LOW)),
                  int(theControlEvent.getController().getArrayValue(HIGH)));
  } else if(theControlEvent.isFrom(y.label())) {
    y.newThreshes(int(theControlEvent.getController().getArrayValue(LOW)),
                  int(theControlEvent.getController().getArrayValue(HIGH)));
  } else if(theControlEvent.isFrom(z.label())) {
    z.newThreshes(int(theControlEvent.getController().getArrayValue(LOW)),
                  int(theControlEvent.getController().getArrayValue(HIGH)));
  } 
}

// string format is x: vvv | y: vvv | z: vvv
int xBeg = "x: ".length();
int xEnd = "x: vvv".length(); 
int yBeg = "x: vvv | y: ".length();
int yEnd = "x: vvv | y: vvv".length();
int zBeg = "x: vvv | y: vvv | z: ".length();
int zEnd = "x: vvv | y: vvv | z: vvv".length();

void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');
 
  if (inString != null) {
    inString = trim(inString);
   
    float xIn = float(inString.substring(xBeg, xEnd)); 
    x.newReading(xIn);

    float yIn = float(inString.substring(yBeg, yEnd)); 
    y.newReading(yIn);

    float zIn = float(inString.substring(zBeg, zEnd)); 
    z.newReading(zIn);
    
    horzPos++;
  }
}

class Axis {
  int screenBoundLower, screenBoundUpper;
  String label;
  float lastReading;
  float currentReading;
  
  float[] threshes = {0,0};
  boolean on = false;
  
  Range threshRange;
 
  Axis(int screenBoundLower, int screenBoundUpper, char label) {
    this.screenBoundLower = screenBoundLower;
    this.screenBoundUpper = screenBoundUpper;
    this.label = label + "Threshes";
    
    int defaultLow = 50;
    int defaultHigh = 100;
    
    threshRange = cp5.addRange(this.label)
                     .setPosition(graphWid, (screenBoundLower+screenBoundUpper)/2 - 20)
                     .setSize(deg360,40)
                     .setHandleSize(20)
                     .setRange(deg0,deg360)
                     .setRangeValues(defaultLow,defaultHigh)
                     .setColorForeground(fg)
                     .setColorBackground(bg)  
                     ;
    threshes[LOW] = defaultLow;
    threshes[HIGH] = defaultHigh;
  }
  
  void draw() {
    stroke(base);
    line(0, screenBoundUpper, width, screenBoundUpper);
    stroke(firstThresh);
    point(horzPos, map(threshes[LOW], deg0, deg360, screenBoundLower+1, screenBoundUpper-1));
    stroke(secondThresh);
    point(horzPos, map(threshes[HIGH], deg0, deg360, screenBoundLower+1, screenBoundUpper-1));
    
    if (crossedThresh(LOW)) stroke(firstThresh);
    else if (on) stroke(secondThresh);
    else stroke(base);
    point(horzPos, map(currentReading, deg0, deg360, screenBoundLower, screenBoundUpper));
  }
  
  void newReading(float newReading) {    
    lastReading = currentReading;
    currentReading = newReading;
    
    if (crossedFromAbove(LOW)) {
      on = false;
    } else if (crossedFromBelow(HIGH)) {
      on = true;
    }
  }
  
  boolean crossedFromBelow(int THRESH) {
    return lastReading < threshes[THRESH] && currentReading >= threshes[THRESH];
  }
  
  boolean crossedFromAbove(int THRESH) {
    return lastReading >= threshes[THRESH] && currentReading < threshes[THRESH];
  }
  
  boolean crossedThresh(int THRESH) {
    return currentReading >= threshes[THRESH];
  }
  
  void newThreshes(float lowThresh, float highThresh) {
    threshes[LOW] = lowThresh;
    threshes[HIGH] = highThresh;
  }
  
  String label() { return label; }
}
