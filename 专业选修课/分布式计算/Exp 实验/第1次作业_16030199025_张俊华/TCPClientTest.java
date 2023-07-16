import java.util.ArrayList;

/**
 * TCPClientTest TCP 客户端并发连接测试程序
 * @author 张俊华 16030199025
 */
public class TCPClientTest {

    public static void main(String args[]){
        ArrayList<TCPClientThread> ClientArray  =  new ArrayList<>();
        for(int i = 0; i < 100; i++){
            String msg = "This is Client" +i;
            ClientArray.add(new TCPClientThread(i,msg));
            System.out.println(i);
        }

        for(int i = 0; i < 100; i++){
            ClientArray.get(i).start();
        }
    }
}
