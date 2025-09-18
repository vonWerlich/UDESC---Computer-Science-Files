package client;

import java.net.URL;

import javax.xml.namespace.QName;
import javax.xml.ws.Service;

import fornecedor.FornecedorServer;

import java.util.ArrayList;
import java.util.List;

import utils.Product;

public  class ClientFornecedor {
    private FornecedorServer server;

    public ClientFornecedor(String URL) throws Exception{
        URL url = new URL(URL);
        QName qname = new QName("http://fornecedor/", "FornecedorServerImplService");
        Service service = Service.create(url, qname);

        server = service.getPort(FornecedorServer.class);
    }

    private String[] products_to_array_ids(List<Integer> products) {
        List<String> list_ids = new ArrayList<String>();

        for(Integer p_id: products) {
            list_ids.add(Integer.toString(p_id));
        }

        System.out.println(list_ids.stream().toArray(String[]::new));
        return list_ids.stream().toArray(String[]::new);
    }

    public double comprar_produtos(List<Integer> products ){
        return server.comprarProdutos(products_to_array_ids(products));
    }

    public boolean pagar_produtos(double valor){
        return server.pagarProdutos(valor);
    }

    public static void main(String[] args) {
        try {
            String URL = "http://127.0.0.1:9879/WSFornecedor?wsdl";

            ClientFornecedor client = new ClientFornecedor(URL);

            List<Integer> products = new ArrayList<Integer>();

            // int id, String descricao, double value, int qtd
            /*
                1000;Mostarda 1kg;54;29.11
                1001;Presunto 1kg;87;28.34
                1002;Peixe 200g;21;10.06  
            */
            
            for (int i = 1000; i < 1016; i++) {
                products.add(i);
            }

            System.out.println(client.comprar_produtos(products));

            double value = 15 * 29.11;

            System.out.println(client.pagar_produtos(value));

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

}
