

import processing.serial.*;

Serial gun;
Serial RFID;
int highScore;

int userXPos;
int userYPos;
boolean firing;
char action;

int score = 0;
int enemyXPos;
int enemyYPos;

void setup() 
{
  size(600, 600);
  userXPos = width/2;
  userYPos = height/2;
  newEnemy();
  
  gun = new Serial(this, "/dev/tty.usbserial-FTFOM7O3", 9600);
  RFID = new Serial(this, "/dev/tty.usbserial-FTFOKU5L", 9600);
}

void draw() {
  while (gun.available() > 0 && !firing) {
    action = char(gun.read());
    moveUser();
  }
  if (RFID.available() > 0) {
    highScore = max(highScore, RFID.read());
    RFID.write(highScore);
  }
  
  background(255);

  fill(0);
  rect(userXPos - 15, userYPos - 15, 30, 30);
  
  if(firing && hitEnemy()) {
    fill(0,255,0);
    rect(enemyXPos - 25, enemyXPos - 25, 50, 50);
    newEnemy();
    score++;
  }
    
  fill(255,0,0);
  rect(enemyXPos - 25, enemyYPos - 25, 50, 50);
  moveEnemy();
}

void newEnemy() {
  enemyXPos = int(random(width));
  enemyYPos = int(random(height)); 
}

boolean hitEnemy() {
  firing = false;
  return ((userXPos + 15 > enemyXPos - 25) && (userXPos - 15 < enemyXPos + 25))
          && ((userYPos - 15 < enemyYPos + 25) && (userYPos + 15 > enemyYPos - 25));
}

void moveUser() {
  switch(action) {
    case 'R':
      if (userXPos < width) userXPos+=2;
      break;
    case 'L':
      if (userXPos > 0) userXPos-=2;
      break;
    case 'F':
      if (userYPos < height) userYPos+=2;
      break;
    case 'B':
      if (userYPos > 0) userYPos-=2;
      break;
    case '!':
      firing = true;
      break;
  }
}

void moveEnemy() {
  float r = random(255);
  if (r < 128 && enemyXPos < width) enemyXPos+=5;
  if (r > 128 && enemyXPos > 0) enemyXPos-=5;
  if (r % 2 == 1 && enemyYPos < height) enemyYPos+=5;
  if (r % 2 == 0 && enemyYPos > 0) enemyYPos-=5;
}
