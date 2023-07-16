import javax.xml.crypto.Data;
import java.io.*;
import java.net.*;

/**
 * UDP 服务端线程
 * @author 张俊华 16030199025
 */
public class UDPServerThread extends Thread {
    private DatagramSocket socket = null;
    private DatagramPacket packet = null;

    /**
     *
     * @param socket UDPSocket
     * @param packet 收到的 UDP 数据包，用于获取消息，获取回送地址和端口
     */
    UDPServerThread(DatagramSocket socket, DatagramPacket packet){
        this.socket = socket;
        this.packet = packet;
    }

    public void run(){
        try {
                DatagramPacket reply = new DatagramPacket(packet.getData(),
                        packet.getLength(), packet.getAddress(), packet.getPort());
                // 回送消息
                socket.send(reply);
        } catch (SocketException e){
            System.out.println("Socket: " + e.getMessage());
        } catch (IOException e) {
            System.out.println("IO: " + e.getMessage());
        }
    }
}
