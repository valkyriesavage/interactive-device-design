import org.eclipse.jetty.server.Server;


public class DoIt {

  public static void main(String[] args) throws Exception {
    SerialCarder scoreKeeper = new SerialCarder();
    scoreKeeper.initialize("/dev/tty.usbserial-FTFOM7O3");
    
    SerialController gameGun = new SerialController();
    gameGun.initialize("/dev/tty.usbserial-FTFOM7O3");
    
    Server server = new Server(8888);
    ScoreHandler handler = new ScoreHandler();
    server.setHandler(handler);

    server.start();
    server.join();
    
    int highScore = 0;
    
    while (true /* card is not tapped */) {
      // wait for card to tap
      if (false /* first card tap */) {
        // read highScore from tap
      }
      if (handler.score > 0) {
        // write greater of (score, highScore) to card
      }
    }
  }
}
