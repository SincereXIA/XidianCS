import java.util.ArrayList;

/**
 * UDPClientTest UDP客户端并发连接测试程序
 * @author 张俊华 16030199025
 */
public class UDPClientTest {

    public static void main(String args[]){
        ArrayList<UDPClientThread> ClientArray  =  new ArrayList<>();
        for(int i = 0; i < 2; i++){
            ClientArray.add(new UDPClientThread("The Thread" + i));
            System.out.println(i);
        }

        for(int i = 0; i < 2; i++){
            ClientArray.get(i).start();
        }
    }
}
