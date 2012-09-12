import processing.serial.*;

Serial myPort;

char[][] letters = {  {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P'},
                      {'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ' '},
                      {' ', ' ', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ' '}  };
int lineLength = 10;
int numLines = 3;
int letterWidth = 10;

int xPos = 0;
int yPos = 0;

char selectedChar = '?';
String createdString = "";

PFont f;
  
void setup() {
  size(400,200);
  myPort = new Serial(this, Serial.list()[0], 9600);
  myPort.bufferUntil('\n');
  background(255);
  f = createFont("Courier New", 20, true);
}

void draw() {
  background(255);
  
  fill(255, 0, 0);
  ellipse((xPos*letterWidth)+160-letterWidth/2, (yPos+1)*40-letterWidth/2, letterWidth, letterWidth);
  
  textFont(f, 16);
  fill(0);
  textAlign(CENTER);
  text(letters[0], 0, 10, width/2, 40);
  text(letters[1], 0, 10, width/2, 80);
  text(letters[2], 0, 10, width/2, 120);
  text(createdString, width/2, 160);
}

void serialEvent(Serial myPort) {
  String inString = myPort.readStringUntil('\n');
  println(inString);
  if (inString != null) {
    inString = trim(inString);
    char data = inString.charAt(0);
    switch(data) {
      case 'r':
        xPos = (xPos+1)%lineLength;
        break;
      case 'l':
        xPos = (xPos-1+lineLength)%lineLength;
        break; 
      case 'u':
        yPos = (yPos+1)%numLines;
        break; 
      case 'd':
        yPos = (yPos-1+numLines)%numLines;
        break; 
      case 's':
        createdString += selectedChar;
        break; 
    }
    selectedChar = letters[yPos][xPos];
  }
}
