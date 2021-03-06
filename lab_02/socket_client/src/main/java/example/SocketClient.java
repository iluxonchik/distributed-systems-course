package example;

import java.io.*;
import java.net.Socket;


public class SocketClient {

    public static void main( String[] args ) throws IOException {
        // Check arguments
        if (args.length < 3) {
            System.err.println("Argument(s) missing!");
            System.err.printf("Usage: java %s host port file%n", SocketClient.class.getName());
            return;
        }

        String host = args[0];
        // Convert port from String to int
        int port = Integer.parseInt(args[1]);
        // Concatenate arguments using a string builder
        StringBuilder sb = new StringBuilder();
        for (int i = 2; i < args.length; i++) {
            sb.append(args[i]);
            if (i < args.length-1) {
                sb.append(" ");
            }
        }
        String text = sb.toString();

        // Create client socket
        Socket socket = new Socket(host, port);
        System.out.printf("Connected to server %s on port %d %n", host, Integer.valueOf(port));

        // Create stream to send data to server
        DataOutputStream out = new DataOutputStream(socket.getOutputStream());

        // Send text to server as bytes
        out.writeBytes(text);
        out.writeBytes("\n");
        System.out.println("Sent text: " + text);

        // Close client socket
        socket.close();
        System.out.println("Connection closed");

        socket = new Socket(host, port);
        System.out.printf("Connected to server %s on port %d %n", host, Integer.valueOf(port));

        // Get ACK from server
        BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));

        String res;
        while((res = br.readLine()) != null)
            System.out.println(String.format("Reply from server: %s", res));
        br.close();

        // Close client socket
        socket.close();
        System.out.println("Connection closed");

    }
}
