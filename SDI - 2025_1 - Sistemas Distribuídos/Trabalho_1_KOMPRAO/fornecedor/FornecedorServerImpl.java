package fornecedor;

import javax.jws.WebService;

import utils.EstoqueDatabase;

import java.util.ArrayList;
import java.util.List;

@WebService(endpointInterface = "fornecedor.FornecedorServer")
public class FornecedorServerImpl implements FornecedorServer{
    private final String PATH = "database/estoque.csv";

    private EstoqueDatabase est;

    private double total_value = 0;

    public FornecedorServerImpl() {
        est = new EstoqueDatabase(PATH);
    }

    public double comprarProdutos(String produtos[]){
        Send carrier = new Send();
        List<String> messages = new ArrayList<String>();

        double total_value = 0;

        for(String p : produtos){
            System.out.println(p);
            total_value +=  Math.round(est.getItem(Integer.parseInt(p)).getValue() * 1000.0) / 1000.0;
            messages.add(est.getItem(Integer.parseInt(p)).standardString());
        }

        this.total_value = total_value;

        try {
            carrier.sendCarrier(messages);
        } catch (Exception e) {
            System.out.println("Não foi possível enviar os produtos para a transportadora");
        }

        return total_value;
    }


    public boolean pagarProdutos(double valor){
        return total_value == valor;
    }

}
