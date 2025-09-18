package outros;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Scanner;

public class Principal {

    public static void main(String[] args) throws SQLException {
        Conexao c = new Conexao();
        Connection con = c.getConnection();
        int op = 0;
        do{
            op = menu();
            try {
                switch (op) {
                    case 1: new AmbulatoriosController().createAmbulatorio(con);
                            break;
                    case 2: new MedicosController().createMedico(con);
                            break;
                    case 3: new AmbulatoriosController().listarAmbulatorio(con);
                            break;
                    case 4: new MedicosController().listarMedicos(con);
                            break;
                    case 5: new MedicosController().listarMedicosAmbulatorios(con);
                            break;
                }
            }catch(SQLException ex) {
                //ex.printStackTrace();
                System.out.println(ex.getMessage());
                continue;
            }
        } while(op>0 && op<6);  
        con.close();
    }    
    
    private static int menu() {
        System.out.println("");
        System.out.println("Informe o número da opção que desejas executar: ");
        System.out.println("1 - Inserir um novo ambulatório");
        System.out.println("2 - Inserir um novo médico");
        System.out.println("3 - Exibir todos os ambulatório");
        System.out.println("4 - Exibir todos os médicos");
        System.out.println("5 - Exibir todos os médicos e seus respectivos ambulatórios");
        System.out.println("Digite qualquer outro valor para sair");
        System.out.print("Sua opção: ");
        Scanner input = new Scanner(System.in);
        return input.nextInt();
    }
}
