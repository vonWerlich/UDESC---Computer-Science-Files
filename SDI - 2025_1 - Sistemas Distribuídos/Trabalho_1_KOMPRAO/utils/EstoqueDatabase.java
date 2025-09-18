package utils;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;
import java.util.HashMap;
import java.util.Map;


public class EstoqueDatabase {
    private Map<Integer, Product> estoqueDatabase = new HashMap<Integer, Product>();

    public EstoqueDatabase(String path) {
        this.estoqueDatabase = this.readMap(path);
    }
 
    public Map<Integer, Product> readMap(String path) {
        Map<Integer, Product> data = new HashMap<Integer, Product>();
        try {
            List<String> lines = Files.readAllLines(Paths.get(path));
            for (String l : lines) {
                String[] values = l.split(";");
                if (!values[0].equals("Codigo")){
                    Product p = new Product(
                        Integer.valueOf(values[0]),
                        values[1],
                        Float.valueOf(values[3]),
                        Integer.valueOf(values[2])
                    );
    
                    data.put(p.getId(), p);
                }
            } 
        } catch (IOException e) {
            System.out.println("Erro ao ler o arquivo " + e.getMessage());
        }

        return data;
    }

    public Product getItem(int id) throws NullPointerException {
        if(estoqueDatabase.containsKey(id)) {
            return estoqueDatabase.get(id);
        }

        throw new NullPointerException("Id inexistente");
    }

    public Boolean removeItem(int id)  throws NullPointerException {
        if (estoqueDatabase.containsKey(id)) {
            Product p = estoqueDatabase.get(id);
    
            return p.removeItem();
        }

        throw new NullPointerException("Id inexistente");
    }

    public Integer qtdItem(int id)  throws NullPointerException {
        if (estoqueDatabase.containsKey(id)) {
            Product p = this.estoqueDatabase.get(id);
    
            return p.getQtd();
        }

        throw new NullPointerException("Id inexistente");

    }

    @Override
    public String toString() {
        StringBuilder res = new StringBuilder("");

        for(Map.Entry<Integer, Product> p : estoqueDatabase.entrySet()){
            res.append(p.getKey()).append(",").append(p.getValue());
        }

        return res.toString();
    }

    public static void main(String[] args) {
        String path = new String("../database/estoque.csv");

        try {
            EstoqueDatabase est = new EstoqueDatabase(path);
            System.out.println(est);

            if (est.removeItem(1001)) {
                System.out.println("Item Removido com Sucesso");
            }else{
                System.out.println("Erro: não foi possivel remover o item");
            }            
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}

