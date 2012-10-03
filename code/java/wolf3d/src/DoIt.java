import org.eclipse.jetty.server.Server;



public class DoIt {

  public static void main(String[] args) throws Exception {
    SerialCarder scoreKeeper = new SerialCarder();
    scoreKeeper.initialize("/dev/tty.usbserial-FTFOKU5L"); 
    
    SerialController gameGun = new SerialController();
    gameGun.initialize("/dev/tty.usbserial-FTFOM7O3"); 
    
    Server server = new Server(8888);
    ScoreHandler handler = new ScoreHandler();
    handler.setDestination(scoreKeeper);
    server.setHandler(handler);
    
    server.start();
    server.join();
    /*JFrame frame = new JFrame();
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.setSize(300,300);
    JButton button = new JButton("Ok, I'm done");
    frame.getContentPane().add(button);
    frame.setVisible(true);*/
  }
}
