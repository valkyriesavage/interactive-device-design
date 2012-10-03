import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.eclipse.jetty.server.Request;
import org.eclipse.jetty.server.handler.AbstractHandler;
 
/*
 * I am talking to javascript
 */
public class ScoreHandler extends AbstractHandler
{
    private SerialCarder destination;

    public void handle(String target,
                       Request baseRequest,
                       HttpServletRequest request,
                       HttpServletResponse response) 
        throws IOException, ServletException
    {
        int score = Integer.getInteger(target.split("/")[1]);
        destination.setHighScore(score);
 
        response.setContentType("text/html;charset=utf-8");
        response.setStatus(HttpServletResponse.SC_OK);
        baseRequest.setHandled(true);
        response.getWriter().println("ok");
    }
    
    public void setDestination(SerialCarder dest) {
      destination = dest;
    }
}