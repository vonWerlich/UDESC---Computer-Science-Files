package fornecedor;
import com.rabbitmq.client.ConnectionFactory;
import com.rabbitmq.client.Connection;
import com.rabbitmq.client.Channel;

import java.util.ArrayList;
import java.util.List;

public class Send {
    private final static String QUEUE_NAME = "sdi_queue";
    private final static String HOST = "localhost";

    private Connection connection;
    private Channel channel;

    public Send(){}

    private List<String> joinMessages(List<String> produtos){
        List<String> res = new ArrayList<String>();

        int numMessages = produtos.size() / 10;
        int resMessages = produtos.size() % 10; // resto das mensagens a serem enviadas

        int cont = 0;
        String message = "";

        for (int i = 0; i < numMessages; i++) {
            for (int j = 0; j < 10; j++) {
                message += produtos.get(cont);
                cont++;
            }

            res.add(message);
            message = "";
        }

       
        for (int j = 0; j < resMessages; j++) {
                message += produtos.get(cont);
                cont++;
        }

        res.add(message);

        return res;
    }

    public void sendCarrier(List<String> produtos) throws Exception{
        List<String> messages = this.joinMessages(produtos);


        this.channelConnect();

        channel.queueDeclare(QUEUE_NAME, false, false, false, null);
        for (String m : messages) {
            channel.basicPublish("", QUEUE_NAME, null, m.getBytes("UTF-8"));
        }
        System.out.println(" [x] Send '" + messages + "'");

        this.channelClose();
    }

    private void channelConnect() throws Exception {
        ConnectionFactory factory = new ConnectionFactory();
        factory.setHost(this.HOST);
        this.connection = factory.newConnection();
        this.channel = connection.createChannel();
    }

    private void channelClose() throws Exception {
        this.channel.close();
        this.connection.close();
    }

    public static void main(String[] args) {
        Send s = new Send();
        List<String> products = new ArrayList<String>();

        products.add("1000;Mostarda 1kg;54;29.11");
        products.add("1001;Presunto 1kg;87;28.34");
        products.add("1002;Peixe 200g;21;10.06");
        products.add("1003;Suco 200g;30;13.49");
        products.add("1004;Molho de Tomate 500g;74;14.38");
        products.add("1005;Detergente 500ml;31;23.6"); 
        products.add("1006;Cerveja 200g;78;11.77");
        products.add("1007;Óleo 1kg;20;35.11");
        products.add("1008;Alho 3L;18;45.98");
        products.add("1009;Queijo 3L;23;20.82");
        products.add("1010;Uva 2L;34;43.1");
        products.add("1011;Abacaxi 1kg;55;7.43");
        products.add("1012;Biscoito 750ml;92;36.18");
        products.add("1013;Farinha 3L;28;30.74");
        products.add("1014;Amaciante 750ml;97;13.69");
        products.add("1015;Melão 200g;53;24.8");

        try {
            s.sendCarrier(products);
        } catch (Exception e) {
            System.err.println("Não foi possível enviar para a fila");
        }
    }

}