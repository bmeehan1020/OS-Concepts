import java.net.*;
import java.io.*;

public class EchoServer {
	public static void main(String[] args) {
		try {
			ServerSocket sock = new ServerSocket(6015);

			// continuously search for client connections
			while(true){
				Socket client = sock.accept();

				InputStreamReader in = new InputStreamReader(client.getInputStream());
				PrintWriter out = new PrintWriter(client.getOutputStream(), true);


				int byteRead;
				while( (byteRead = in.read()) != -1){
					System.out.println("Received data: " + byteRead + " from " + client.toString());
					out.println(byteRead);
				}

				// close socket connection
				sock.close();
			}
		} catch(IOException ioe){
			System.err.println(ioe);
		}
	}
}