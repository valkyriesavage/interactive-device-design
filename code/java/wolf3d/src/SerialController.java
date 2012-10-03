import java.awt.AWTException;
import java.awt.Robot;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;


public class SerialController extends SerialCommunication {

  private Robot robot;
  
  public SerialController() {
    super();
    try {
      robot = new Robot();
    } catch (AWTException e) {
      e.printStackTrace();
    }
    //robot.setAutoDelay(200);
  }
  
  /**
   * Figure out what to do now that we have a bunch of dataz
   */
  public void actOnData() {
    currentSerialInfo.replaceAll("[^LRFB!]", "");
    
    switch(currentSerialInfo.charAt(0)) {
      case 'L':
        turnLeft();
        break;
      case 'R':
        turnRight();
        break;
      case 'F':
        moveForward();
        break;
      case 'B':
        moveBackward();
        break;
      case '!':
        fire();
        break;
      default:
        break;  
    }
    
    currentSerialInfo = currentSerialInfo.substring(1);
  }
  
  /**
   * Fire!
   */
  private void fire() {
    robot.keyPress(KeyEvent.VK_X);
    robot.keyRelease(KeyEvent.VK_X);
  }
  
  /**
   * Turn left
   */
  private void turnLeft() {
    robot.keyPress(KeyEvent.VK_LEFT);
    robot.keyRelease(KeyEvent.VK_LEFT);
  }
  
  /**
   * Turn right
   */
  private void turnRight() {
    robot.keyPress(KeyEvent.VK_RIGHT);
    robot.keyRelease(KeyEvent.VK_RIGHT);
  }
  
  /**
   * Move forward
   */
  private void moveForward() {
    robot.keyPress(KeyEvent.VK_UP);
    robot.keyRelease(KeyEvent.VK_UP);
  }
  
  /**
   * Move backward
   */
  private void moveBackward() {
    robot.keyPress(KeyEvent.VK_DOWN);
    robot.keyRelease(KeyEvent.VK_DOWN);
  }
}
