import java.io.*;
import java.net.Socket;
import java.net.SocketException;

/**
 * TCPClientThread TCP 客户端线程
 * @author 张俊华 16030199025
 */
public class TCPClientThread extends Thread {
    private String msg;
    private int num;

    /**
     *
     * @param num 线程编号
     * @param msg 待发送的消息
     */
    TCPClientThread(int num, String msg){
        this.msg = msg ;
        this.num = num;
    }
    
    public void run() {
        String userInput = msg;
        String echoMessage = null;

        BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
        Socket socket = null;
        try {
            socket = new Socket("127.0.0.1", 6790);
            System.out.println("Client "+num+" Connected to Server");

            InputStream inStream = socket.getInputStream();
            OutputStream outStream = socket.getOutputStream();
            BufferedReader in = new BufferedReader(new InputStreamReader(inStream));
            PrintWriter out = new PrintWriter(outStream);
            out.println(userInput);
            out.flush();
            echoMessage = in.readLine();
            System.out.println("Echo from server: " + echoMessage);
            socket.close();
        } catch (SocketException e){
            System.out.println("Socket: " + e.getMessage());
        } catch (IOException e){
            System.out.println("IO: " + e.getMessage());
        }
    }
}
