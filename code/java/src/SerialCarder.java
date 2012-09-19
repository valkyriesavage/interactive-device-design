

public class SerialCarder extends SerialCommunication {
  
  private int highScore = 0;
	
  public SerialCarder() {
    super();
  }
  
  /**
   * When the Mifare read write program writes to serial
   * an event will be triggered and the data will appear here
   * as a string in currentSerialInfo 
   */
  public void actOnData() {
    sendScore();
	  if (!currentSerialInfo.contains("\n")) return;
	  
	  System.out.println("JAVA got raw data: " + currentSerialInfo);
	  String[] splitInput = currentSerialInfo.split("\\s+");
	  
	  String inData = "";
	  int i = 0;
	  boolean done = false;
	  boolean start = false;
	  while (i < splitInput.length && !done) {
		  if (splitInput[i].equals("24")) {
			  done = true;
		  } else if (splitInput[i].equals("23")) {
			  start = true;
		  } else if (start && !done) {
			  inData = inData + (Integer.parseInt(splitInput[i]) - 30);
		  }
		  i++;
	  }
	  
	  int lastScore;
	  if(inData.isEmpty()) {
		  lastScore = 0;
	  } else {
		  lastScore = Integer.parseInt(inData);
	  }
	  if (lastScore > highScore) {
		  highScore = lastScore;
	  }

	  currentSerialInfo = "";
  }
  
  /**
   * This will write a score onto serial
   * and onto the card
   */
  public void sendScore() {
    sendMessage("" + highScore);
  }
  
  public void setHighScore(int potentialHighScore) {
    if (highScore < potentialHighScore) highScore = potentialHighScore;
  }
}
