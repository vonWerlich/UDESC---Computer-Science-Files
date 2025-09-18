package transportadora;

import java.io.IOException;
import java.util.concurrent.TimeoutException;

import com.rabbitmq.client.*;

public class Recv {
    private final static String QUEUE_NAME = "sdi_queue";
    private final static String HOST = "localhost";

    public static void main(String[] args) throws IOException, TimeoutException{
        
        System.out.println("Queue Server");
        ConnectionFactory factory = new ConnectionFactory();
        factory.setHost(HOST);
        Connection connection = factory.newConnection();
        Channel channel = connection.createChannel();

        channel.queueDeclare(QUEUE_NAME, false, false, false, null);
        System.out.println(" [*] Waiting for messages. To exit press CTRL+C");

        Consumer consumer = new DefaultConsumer(channel) {
            @Override
            public void handleDelivery(String consumerTag, Envelope envelope, AMQP.BasicProperties properties, byte[] body) throws IOException{
                String message = new String(body, "UTF-8");
                System.out.println(" [x] Received:\n '\t" + message + "'");
             }
        };
        channel.basicConsume(QUEUE_NAME, true, consumer);
    }
}
