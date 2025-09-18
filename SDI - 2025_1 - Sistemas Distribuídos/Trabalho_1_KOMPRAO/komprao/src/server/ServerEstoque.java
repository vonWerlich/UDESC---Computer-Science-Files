package server;

/*
 * O servidor deve oferecer:
 * - Operações com a base de dados (implementando IDatabase)
  */

 
import java.rmi.*;
import java.rmi.server.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import client.ClientFornecedor;
import utils.EstoqueDatabase;
import utils.Product;

import java.rmi.registry.*;

public class ServerEstoque  implements IEstoque{
    private final String PATH = "database/estoque.csv";
    private Map<String, ClientFornecedor> fornecedores = new HashMap<String,ClientFornecedor>();
    private List<Integer> products = new ArrayList<Integer>();
    private  static final int QTD_PRODUCTS = 15;

    private EstoqueDatabase est;

    public ServerEstoque() {
        est = new EstoqueDatabase(PATH);
    }

    public ServerEstoque(Map<String, String> fornecedores) throws Exception {
        est = new EstoqueDatabase(PATH);

        for (Map.Entry<String, String> f : fornecedores.entrySet()){
            String key = f.getKey();
            String url = f.getValue();
            ClientFornecedor forn = new ClientFornecedor(url);

            this.fornecedores.put(key, forn);
        }
    }

    public Product consultar_produto(String id) throws RemoteException {
        Product p = est.getItem(Integer.valueOf(id));
        return p;
    }

    public boolean comprar_fornecedor(String forn, int id){
        products.add(id);

        if(this.products.size() > QTD_PRODUCTS){
            double values = fornecedores.get(forn).comprar_produtos(products);

            return fornecedores.get(forn).pagar_produtos(values);
        }

        return false;
    }

    public Integer remover_produto(String id) throws RemoteException, NullPointerException {
        if (est.removeItem(Integer.valueOf(id))) {
            int qtd = est.qtdItem(Integer.valueOf(id));

            
            if (comprar_fornecedor("f1", Integer.parseInt(id))){
                System.out.println("Produtos comprados do fornecedor");
            }else{
                products.add(Integer.parseInt(id));
            }
            

            return qtd;
        } 

        return -1;
    }

    public boolean comprar_produtos_fornecedor(String fornecedor, List<Product> products) {
        if(fornecedores.containsKey(fornecedor)){
            List<Integer> list_products_id = new ArrayList<Integer>();
            for(Product p : products) {
                list_products_id.add(p.getId());
            }

            double value = fornecedores.get(fornecedor).comprar_produtos(list_products_id);

            return fornecedores.get(fornecedor).pagar_produtos(value);
        }

        return false;
    }

    public String relatorio_produtos() throws RemoteException {
        return est.toString();
    }

    public static void main(String[] args) {
        Map<String, String> fornecedores = new HashMap<String, String>();
        fornecedores.put("f1", "http://127.0.0.1:9864/WSFornecedor?wsdl");

        List<Product> products = new ArrayList<Product>();

        int PORT= 6606;

        try {
            
            ServerEstoque server = new ServerEstoque(fornecedores);

            try {
                IEstoque stub = (IEstoque) UnicastRemoteObject.exportObject(server, 0);
                Registry registry = LocateRegistry.createRegistry(PORT);

                System.out.println("Servidor Estoque Ligado");

                registry.bind("Estoque", stub);
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        } catch (Exception e){
             ServerEstoque server = new ServerEstoque();

            try {
                IEstoque stub = (IEstoque) UnicastRemoteObject.exportObject(server, 0);
                Registry registry = LocateRegistry.createRegistry(PORT);

                System.out.println("Servidor Estoque Ligado");

                registry.bind("Estoque", stub);
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }

        
    }

}
