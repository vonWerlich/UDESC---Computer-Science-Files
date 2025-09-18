package fornecedor;

import javax.xml.ws.Endpoint;

public class FornecedorServerPublisher {
    public static void main(String[] args) {
        System.out.println("Beginning to publish FornecedorService now");
        Endpoint.publish("http://127.0.0.1:9864/WSFornecedor", new FornecedorServerImpl());
        System.out.println("Done publishing");
    }
}
