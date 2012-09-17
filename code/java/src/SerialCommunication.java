import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Enumeration;

/**
 * This code was inspired by the Internet and stolen from the Midas code.
 */

public abstract class SerialCommunication implements SerialPortEventListener {
  SerialPort serialPort;

  /** Buffered input stream from the port */
  private InputStream input;
  /** The output stream to the port */
  private OutputStream output;
  /** Milliseconds to block while waiting for port open */
  private static final int TIME_OUT = 2000;
  /** Default bits per second for COM port. */
  private static final int DATA_RATE = 9600;

  protected String currentSerialInfo = new String();
  

  public void initialize(String portName) {

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
      if (currPortId.getName().equals(portName)) {
        portId = currPortId;
        break;
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
   * Handle an event on the serial port. Read the data and act on it.
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
    
    actOnData();
  }
  
  public abstract void actOnData();

}
