import javax.jms.Message;
import javax.jms.MessageListener;
import javax.jms.ObjectMessage;

/**
 * 均值计算
 */
public class AverageCalculator implements MessageListener {

    public static Double mean;
    Double sum;
    long nums;

    AverageCalculator(){
        super();
        mean = 0.0;
        sum = 0.0;
        nums =0;
    }

    public void onMessage(Message message) {
        try {
            sum += (Double) ((ObjectMessage)message).getObject();
            nums += 1;
        } catch (Exception e) {
            e.printStackTrace();
        }
        mean = sum/nums;
    }

    public static Double getMean(){
        return mean;
    }

}