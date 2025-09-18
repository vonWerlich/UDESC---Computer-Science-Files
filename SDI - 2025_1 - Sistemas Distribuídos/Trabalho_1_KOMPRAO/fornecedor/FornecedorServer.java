package fornecedor;

import javax.jws.WebMethod;
import javax.jws.WebService;
import javax.jws.soap.SOAPBinding;
import javax.jws.soap.SOAPBinding.Style;

@WebService
@SOAPBinding(style = Style.RPC)
public interface FornecedorServer {
    @WebMethod
    double comprarProdutos(String produtos[]);

    @WebMethod
    boolean pagarProdutos(double valor);
} 

