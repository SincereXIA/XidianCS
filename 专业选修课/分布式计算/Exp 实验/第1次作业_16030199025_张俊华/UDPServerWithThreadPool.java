import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

/**
 * UDPServerWithThreadPool 带有线程池的 UDP 服务端主程序
 * @author 张俊华 16030199025
 */
public class UDPServerWithThreadPool {


    public static void main(String args[]){
        // 创建线程池
        ThreadPoolExecutor executor = new ThreadPoolExecutor(5, 30, 20, TimeUnit.MILLISECONDS,
                new ArrayBlockingQueue<Runnable>(10));
        // 定义监听端口
        int serverPort = 6789;
        // 创建UDPSocket
        try (DatagramSocket aSocket = new DatagramSocket(serverPort)) {
            byte[] buffer = new byte[1000];
            while (true) {
                DatagramPacket request = new DatagramPacket(buffer, buffer.length);
                aSocket.receive(request);
                UDPServerThread thread = new UDPServerThread(aSocket, request);
                executor.execute(thread);
                System.out.println("The number of threads in the ThreadPool:" + executor.getPoolSize());
                System.out.println("The number of tasks in the Queue:" + executor.getQueue().size());
                System.out.println("The number of tasks completed:" + executor.getCompletedTaskCount());
            }
        } catch (SocketException e) {
            System.out.println("Socket: " + e.getMessage());
        } catch (IOException e) {
            System.out.println("IO: " + e.getMessage());
        } finally {
            executor.shutdown();
        }
    }
}
