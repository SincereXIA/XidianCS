import java.net.*;
import java.io.*;

/**
 * UDP 多线程服务端主程序
 * @author 张俊华 16030199025
 */
public class UDPServer{

    public static void main(String args[]){
        // 设定监听端口
        int serverPort = 6789;

        //建立 UDPSocket
        try (DatagramSocket aSocket = new DatagramSocket(serverPort)) {
            byte[] buffer = new byte[1000];
            while (true) {
                // 读取客户端请求
                DatagramPacket request = new DatagramPacket(buffer, buffer.length);
                aSocket.receive(request);
                // 建立新线程
                UDPServerThread thread = new UDPServerThread(aSocket, request);
                thread.run();
            }
        } catch (SocketException e) {
            System.out.println("Socket: " + e.getMessage());
        } catch (IOException e) {
            System.out.println("IO: " + e.getMessage());
        }
    }
}