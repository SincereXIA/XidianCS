import org.apache.activemq.ActiveMQConnectionFactory;

import javax.jms.*;
import java.util.Random;

/**
 * 随机信号产生器
 */
public class RandomSignalGenerator {

    private static String brokerURL = "tcp://localhost:61616";
    private static ConnectionFactory factory;
    private Connection connection;
    private Session session;
    private MessageProducer producer;
    private Topic topic;

    public RandomSignalGenerator(String topicName) throws JMSException {

        factory = new ActiveMQConnectionFactory(brokerURL);
        connection = factory.createConnection();

        session = connection.createSession(false, Session.AUTO_ACKNOWLEDGE);
        topic = session.createTopic(topicName);
        producer = session.createProducer(topic);

        connection.start();
    }

    public void close() throws JMSException {
        if (connection != null) {
            connection.close();
        }
    }

    public static void main(String[] args) throws JMSException, InterruptedException {
        RandomSignalGenerator generator = new RandomSignalGenerator("Signal");
        generator.sendMessage(20,10);
        generator.close();
    }

    public void sendMessage(double a, double b) throws JMSException, InterruptedException {

        Random random = new Random();
        while (true){
            Double sig =  Math.sqrt(b)*random.nextGaussian()+a;
            Message sigMessage = session.createObjectMessage(sig);
            producer.send(sigMessage);
            System.out.println(sig);
            Thread.sleep(10);
        }
    }

}
