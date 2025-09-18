package caixa;
/*
    Caixa é o programa que irá consumir as operações do Servidor.
    Caixa não pode falar diretamente com Estoque.
 */

import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

import java.util.Scanner;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

import server.IServidor;

 public class Caixa {

    private int id;
    private String cpf;

    private IServidor stub;
    Scanner s = new Scanner(System.in);

    public Caixa(int port) throws NotBoundException ,RemoteException {
        String HOST = "localhost";

        Registry registry = LocateRegistry.getRegistry(HOST, port);
        stub = (IServidor) registry.lookup("Servidor");
    }

    public String getCpf() {
        return cpf;
    }


    public void inicializada_caixa() {
        System.out.println("Caixa inicializado");

        while (true) {
            System.out.println("Por favor insira o identificador do caixa, o identificador aceita apenas número maiores que zero");
            System.out.println(">");
            id = Integer.parseInt(s.nextLine());

            if(id > 0) {
                System.out.println("Caixa inicializado com sucesso");
                return;
            }else{
                System.out.println("Identificador do caixa invalido, digite um número maior que zero");
            }
        }

    }


    public void inicializar_compra() throws RemoteException{
        String cpf = "";
        while (true) {
            System.out.println("Por favor, insira o seu CPF ");
            System.out.println(">");
            cpf = s.nextLine();

            if(cpf.length() == 11){
                this.cpf = cpf;
                if(stub.inicializar_venda(this.id + ":" + this.cpf)){
                    System.out.println("Operação inicializada com sucesso");
                    return;
                }else{
                    System.out.println("CPF invalido, já está sendo utilizado, por favor insira outro");
                }

            }

            System.out.println("CPF invalido, por favor insira em um formato valído");

        }
    }

    public void qtd_produto(Integer id) throws RemoteException {
        double valor_pagar = 0;

        while(true){
            System.out.println("Digite a quantidade que deseja comprar (de 1 a 10)");
            System.out.println(">");

            int qtd = Integer.parseInt(s.nextLine());

            if (1 <= qtd && qtd <= 10){
                for (int i = 0; i < qtd; i++) {
                    valor_pagar = stub.registrar_produto(this.id + ":" + this.cpf, String.valueOf(id));
                }
                System.out.println("Valor a ser pago atual R$ " + String.format("%.2f", valor_pagar));
                break;
            }else{
                System.out.println("Valor fora faixa, por favor tente de novo");
            }

        }
    }

    public void registrar_produto() throws RemoteException {
        int id = -1;
   
        while(true){
            System.out.println("Digite o id do produto (de 1001 a 1299):");
            System.out.println(">");
    
            id = Integer.parseInt(s.nextLine());

            if (1001 <= id && id <= 1299){

                qtd_produto(id);
                
                break;
            }else{
                System.out.println("Id do produto invalido");
            }

        }

    }

    public double consultar_valor_total(String cliente) throws RemoteException {
        return stub.consultar_valor_total(cliente);
    }

    public void pagar() throws RemoteException {
        double valor_pagar = 0;
        
        while (true) {
            System.out.println("Valor a ser pago: R$ " + consultar_valor_total(this.id + ":" + this.cpf));
            System.out.println("Digite o valor a ser pago:");
            System.out.println(">");

            valor_pagar = Double.parseDouble(s.nextLine());

            if(stub.pagar(this.id + ":" + this.cpf, valor_pagar)){
                System.out.println("Compra finalizada com sucesso");
                return;
            }

            System.out.println("Valor diferente do valor a ser pago, por favor digite o valor a ser pago");
        }
        
    }

     public static void main(String[] args) {
        int PORT = 6605;
        int opcao = -1;

        Scanner s = new Scanner(System.in);

        try {
            Caixa caixa = new Caixa(PORT);
            caixa.inicializada_caixa();

            while (true) {
                System.out.println("Iniciar Operação do Caixa");
                caixa.inicializar_compra();
    
                while (true) {
                    caixa.registrar_produto();
    
                    do {
                        System.out.println("Deseja realizar mais uma compra (1 para sim, 2 para não)");
                        System.out.println(">");
        
                        opcao = Integer.parseInt(s.nextLine());
        
                        if (opcao != 1 && opcao != 2){
                            System.out.println("Opção inválida por favor escolha uma das duas");
                        }
                        
                    } while (opcao != 1 && opcao != 2);
    
                    if (opcao == 2) {
                        caixa.pagar();
                        break;
                    }
    
                }
            }
    

        }catch(Exception ex){
            ex.printStackTrace();
        }
     }
 }
 