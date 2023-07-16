import org.apache.activemq.ActiveMQConnectionFactory;

import javax.jms.*;

/**
 * 消息监听控制器
 */
public class ListenerController {

    public static void main(String[] args) throws JMSException {
        String brokerURL = "tcp://localhost:61616";
        ConnectionFactory factory = null;
        Connection connection = null;
        Session session = null;
        Topic topic = null;
        MessageConsumer varianceConsumer = null;
        MessageConsumer averageConsumer = null;
        MessageConsumer outlierConsumer = null;
        MessageConsumer realTimeConsumer = null;
        AverageCalculator averageCalculator = null;
        VarianceCalculator varianceCalculator = null;
        OutliersDetector outliersDetector = null;
        RealTimeChartListener realTimeChartListener = null;


        try {
            factory = new ActiveMQConnectionFactory(brokerURL);
            connection = factory.createConnection();

            session = connection.createSession(false, Session.AUTO_ACKNOWLEDGE);
            topic = session.createTopic("Signal");

            varianceConsumer = session.createConsumer(topic);
            averageConsumer = session.createConsumer(topic);
            outlierConsumer = session.createConsumer(topic);
            realTimeConsumer = session.createConsumer(topic);
            varianceCalculator = new VarianceCalculator();
            averageCalculator = new AverageCalculator();
            outliersDetector = new OutliersDetector();
            realTimeChartListener = new RealTimeChartListener();

            averageConsumer.setMessageListener(averageCalculator);
            varianceConsumer.setMessageListener(varianceCalculator);
            outlierConsumer.setMessageListener(outliersDetector);
            realTimeConsumer.setMessageListener(realTimeChartListener);

            connection.start();
            RealTimeChart.main();
            while (true){
                System.out.println("Mean: "+ AverageCalculator.getMean());
                System.out.println("Var: " + VarianceCalculator.getVariance());
                Thread.sleep(1000);
            }
            // Pause
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            connection.close();
        }
    }

}
