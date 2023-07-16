import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

/**
 * TCPServerWithThreadPool 带有线程池的TCPServer 主程序
 * @author 张俊华 16030199025
 */
public class TCPServerWithThreadPool {

    public static void main(String arg[]){
        // 创建线程池
        ThreadPoolExecutor executor = new ThreadPoolExecutor(5, 30, 20, TimeUnit.MILLISECONDS,
                new ArrayBlockingQueue<Runnable>(10));
        // 监听端口
        int serverPort = 6790;
        try {
            // 建立监听 Socket
            ServerSocket listenSocket=new ServerSocket(serverPort);
            Socket socket;
            System.out.println("TCP TCPServerWithThreadPool init success!");
            int count = 0;
            while(true){
                // 响应 TCP 请求
                socket=listenSocket.accept();
                count++;
                System.out.println("The total number of clients is " + count + ".");
                // 提交线程池处理
                executor.submit(new TCPServerThread(socket));
                System.out.println("The number of threads in the ThreadPool:" + executor.getPoolSize());
                System.out.println("The number of tasks in the Queue:" + executor.getQueue().size());
                System.out.println("The number of tasks completed:" + executor.getCompletedTaskCount());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
