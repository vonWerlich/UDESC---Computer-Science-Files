package utils;

import java.io.Serializable;

public class Product implements Serializable{
    private int id;
    private String descricao;
    private double value;
    private int qtd;

    public Product(int id, String descricao, double value, int qtd) {
        this.id = id;
        this.descricao = descricao;
        this.value = value;
        this.qtd = qtd;
    }
    
    public int getId() {
        return id;
    }

    public String getDescricao() {
        return descricao;
    }

    public double getValue() {
        return value;
    }

    public int getQtd() {
        return qtd;
    }

    public void setQtd(int qtd) {
        this.qtd = qtd;
    }

    public void setValue(double value) {
        this.value = value;
    }

    public Boolean removeItem(){
        if (this.qtd > 0){
            this.qtd -= 1;
            return true;
        }

        return false;
    }

    public String standardString(){
        return id + "," + descricao + "," + qtd + "," + String.format("%.2f", value) + "\n";
    }

    @Override
    public boolean equals(Object obj) {
        Product p = (Product) obj;
        return p.id == this.id;
    }

    @Override
    public String toString() {
        return (descricao + "," +  String.format("%.2f", value) + "," + qtd + "\n");
    }
}