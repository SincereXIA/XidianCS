import javax.jms.Message;
import javax.jms.MessageListener;
import javax.jms.ObjectMessage;

public class OutliersDetector implements MessageListener {


    OutliersDetector(){
        super();
    }

    public void onMessage(Message message) {
        try {
            Double mean = AverageCalculator.getMean();
            Double sigma = Math.sqrt(VarianceCalculator.getVariance());
            Double num = (Double) ((ObjectMessage)message).getObject();
            if(num > mean + 3*sigma || num < mean - 3 * sigma){
                System.err.println("Catch Outlier! : " + num);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

}