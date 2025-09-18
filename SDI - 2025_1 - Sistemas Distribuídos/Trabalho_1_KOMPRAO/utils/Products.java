package utils;

import java.util.ArrayList;
import java.util.List;


public class Products {
    private double totalValue;
    private List<Product> products = new ArrayList<Product>();

    public Products() {
        totalValue = 0;
    }

    public List<Product> getProducts() {
        return this.products;
    }

    public double getTotalValue() {
        return totalValue;
    }

    public void add(Product p) throws Exception{
        if(p.getValue() > 0) {
            int index = products.indexOf(p);
            // p.setValue((double) Math.round(p.getValue() * 100.0) / 100.0);
            if(index != -1){
                Product p_aux = products.get(index);
                int qtd = p_aux.getQtd() + 1;

                p_aux.setQtd(qtd);
            }else{
                products.add(p);
            }
            totalValue += Math.round(p.getValue() * 1000.0) / 1000.0;
        }else{
            throw new Exception("O produto não pode ter o valor negativo");
        }
    }

    @Override
    public String toString() {
        String res = "";

        res = "\tValor Total R$ " + String.format("%.2f", totalValue) + "\n\n";

        for(Product p : products) {
            res += "\t\t * " + p.toString();
        }

        return res;
    }

}
