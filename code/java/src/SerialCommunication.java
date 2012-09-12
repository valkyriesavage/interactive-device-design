import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;

import java.awt.AWTException;
import java.awt.Robot;
import java.awt.event.KeyEvent;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Enumeration;

/**
 * This code was inspired by the Internet and stolen from the Midas code.
 */

public class SerialCommunication implements SerialPortEventListener {
  SerialPort serialPort;

  private static final String PORT_NAMES[] = { 
      "/dev/tty.usbmodemfa131", // Mac, Arduino Uno
      "/dev/tty.usbmodemfa121", // Mac, Arduino Uno
      "/dev/tty.usbmodem12341", // Mac, Teensy
      "/dev/tty.", // Mac, Boarduino
      "/dev/ttyACM0", // Linux, Arduino Uno
      "COM3", // Windows
  };
  /** Buffered input stream from the port */
  private InputStream input;
  /** The output stream to the port */
  private OutputStream output;
  /** Milliseconds to block while waiting for port open */
  private static final int TIME_OUT = 2000;
  /** Default bits per second for COM port. */
  private static final int DATA_RATE = 9600;

  private String currentSerialInfo = new String();
  
  private Robot robot;

  public void initialize() throws AWTException {
    // random stuff setup
    robot = new Robot();
    robot.setAutoDelay(200);

    CommPortIdentifier portId = null;
    // the following line is useful for computers with AMD processors. it's
    // stupid.
    // System.setProperty("gnu.io.rxtx.SerialPorts", "/dev/ttyACM0");

    @SuppressWarnings("rawtypes")
    Enumeration portEnum = CommPortIdentifier.getPortIdentifiers();

    // iterate through, looking for the port
    while (portEnum.hasMoreElements()) {
      CommPortIdentifier currPortId = (CommPortIdentifier) portEnum
          .nextElement();
      for (String portName : PORT_NAMES) {
        if (currPortId.getName().equals(portName)) {
          portId = currPortId;
          break;
        }
      }
    }

    if (portId == null) {
      System.out.println("Could not find COM port.");
      return;
    }

    try {
      // open serial port, and use class name for the appName.
      serialPort = (SerialPort) portId
          .open(this.getClass().getName(), TIME_OUT);

      // set port parameters
      serialPort.setSerialPortParams(DATA_RATE, SerialPort.DATABITS_8,
          SerialPort.STOPBITS_1, SerialPort.PARITY_NONE);

      // open the streams
      input = serialPort.getInputStream();
      output = serialPort.getOutputStream();

      // add event listeners
      serialPort.addEventListener(this);
      serialPort.notifyOnDataAvailable(true);

    } catch (Exception e) {
      System.err.println(e.toString());
    }
  }

  /**
   * This should be called when you stop using the port. This will prevent port
   * locking on platforms like Linux.
   */
  public synchronized void close() {
    if (serialPort != null) {
      serialPort.removeEventListener();
      serialPort.close();
    }
  }

  public synchronized void sendMessage(String message) {
    try {
      output.write(message.getBytes());
    } catch (IOException e) {
      e.printStackTrace();
    }
  }

  /**
   * Handle an event on the serial port. Read the data and print it.
   */
  public synchronized void serialEvent(SerialPortEvent oEvent) {
    if (oEvent.getEventType() == SerialPortEvent.DATA_AVAILABLE) {
      byte actions[] = new byte[6];
      try {
        input.read(actions, 0, 6);

        // Displayed results are codepage dependent
      } catch (Exception e) {
        System.err.println(e.toString());
        return;
      }

      currentSerialInfo = (currentSerialInfo + new String(actions));
    }
  }
  
  /**
   * Figure out what to do now that we have a bunch of dataz
   */
  private void actOnData() {
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
        System.out.println("What???");  
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
