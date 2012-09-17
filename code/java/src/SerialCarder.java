

public class SerialCarder extends SerialCommunication {
  
  public SerialCarder() {
    super();
  }
  
  /**
   * Figure out what to do now that we have a bunch of dataz
   */
  public void actOnData() {
    // do nothing
  }
  
  public void sendScore(int score) {
    sendMessage("" + score);
  }
}
