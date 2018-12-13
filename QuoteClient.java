import java.net.*;
import java.io.*;

public class QuoteClient 
{
	public static void main(String[] args) {
		try {
			// make connection to server socket
			Socket sock = new Socket("127.0.0.1", 6017);

			InputStream in = sock.getInputStream();
			BufferedReader bin = new BufferedReader(new InputStreamReader(in));

			// read quote-of-the-day from socket
			String line;
			while ((line = bin.readLine()) != null){
				System.out.println(line);
			}

			// close socket connection
			sock.close();
		} catch(IOException ioe){
			System.err.println(ioe);
		}
	}
}