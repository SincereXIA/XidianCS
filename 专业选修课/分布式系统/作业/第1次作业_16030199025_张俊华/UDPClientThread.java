import java.net.*;
import java.io.*;

public class UDPClientThread extends  Thread{

    private String msg;

    UDPClientThread(String msg){
        this.msg = msg;
    }


    public void run(){
// args give message contents and server hostname
        DatagramSocket aSocket = null;
        try {
            aSocket = new DatagramSocket();

            InetAddress aHost = InetAddress.getByName("127.0.0.1");
            int serverPort = 6789;
            for (int i = 0; i < 100; i++){
                byte[] m = (msg+ "part" +i).getBytes();
                DatagramPacket request = new DatagramPacket(m, m.length, aHost, serverPort);
                aSocket.send(request);
                byte[] buffer = new byte[1000];
                DatagramPacket reply = new DatagramPacket(buffer, buffer.length);
                aSocket.receive(reply);
                System.out.println("Reply: " + new String(reply.getData()));
                sleep(1000);
            }

        } catch (SocketException e){
            System.out.println("Socket: " + e.getMessage());
        } catch (IOException e){
            System.out.println("IO: " + e.getMessage());
        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            if(aSocket != null) aSocket.close();
        }
    }
}