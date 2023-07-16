import javax.jms.Message;
import javax.jms.MessageListener;
import javax.jms.ObjectMessage;

public class VarianceCalculator implements MessageListener {

    public static Double variance;
    Double sum2;
    long nums;

    VarianceCalculator(){
        super();
        variance = 0.0;
        sum2 = 0.0;
        nums =0;
    }

    public void onMessage(Message message) {
        try {
            Double num = (Double) ((ObjectMessage)message).getObject();
            Double mean = AverageCalculator.getMean();
            sum2 += Math.pow(num - mean, 2.0);
            nums += 1;
            //System.out.println("num: "+ num + " mean: "+mean);
        } catch (Exception e) {
            e.printStackTrace();
        }
        variance = sum2/nums;
    }

    public static Double getVariance(){
        return variance;
    }

}