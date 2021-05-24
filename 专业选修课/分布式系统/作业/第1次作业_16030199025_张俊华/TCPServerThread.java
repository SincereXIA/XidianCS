import java.io.*;
import java.net.Socket;

/**
 * TCPServerThread TCP服务端线程
 * @author 张俊华 16030199025
 */
public class TCPServerThread extends Thread {

    private Socket socket = null;

    /**
     *
     * @param socket 服务socket
     */
    TCPServerThread(Socket socket) {
        this.socket = socket;
    }

    public void run(){
        InputStream is=null;
        InputStreamReader isr=null;
        BufferedReader br=null;
        OutputStream os=null;
        PrintWriter pw=null;
        try {
            is = socket.getInputStream();
            isr = new InputStreamReader(is);
            br = new BufferedReader(isr);
            os = socket.getOutputStream();
            pw = new PrintWriter(os);
            String info=null;
            // 获取客户端消息
            info=br.readLine();
            System.out.println("Message from client:"+info);
            // 回送消息
            pw.println(info);
            pw.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }finally{
            try {
                if(pw!=null)
                    pw.close();
                if(os!=null)
                    os.close();
                if(br!=null)
                    br.close();
                if(isr!=null)
                    isr.close();
                if(is!=null)
                    is.close();
                if(socket!=null)
                    socket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
