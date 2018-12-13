/*
 * Section 3.6.1 describes port numbers below 1024 as being well known — 
 * that is, they provide standard services. Port 17 is known as the quote-of-the-day service. 
 * When a client connects to port 17 on a server, the server responds with a quote for that day.
 * Modify the date server shown in Figure 3.21 so that it delivers a quote of the day
 * rather than the current date. The quotes should be printable ASCII characters and 
 * should contain fewer than 512 characters, although multiple lines are allowed. 
 * Since port 17 is well known and therefore unavailable, have your server listen to port 6017. 
 * The date client shown in Figure 3.22 can be used to read the quotes returned by your server.
 */

import java.net.*;
import java.io.*;
         
public class DateServer {
	public static void main(String[] args) {
		try {
			ServerSocket sock = new ServerSocket(6013);

			/* now listen for connections */ 
			while (true) {
               Socket client = sock.accept();

               PrintWriter pout = new
               PrintWriter(client.getOutputStream(), true);

               /* write the Date to the socket */
               pout.println(new java.util.Date().toString());

               /* close the socket and resume */
               /* listening for connections */
               client.close();
			} 
		}
		catch (IOException ioe) { 
			System.err.println(ioe);
		}
	}
}