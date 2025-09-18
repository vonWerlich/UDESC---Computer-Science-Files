package outros;

import java.sql.Connection;
import java.sql.SQLException;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Scanner;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author rebeca
 */
public class MedicosController {
    public void createMedico(Connection con) throws SQLException {
        Scanner input = new Scanner(System.in);
        System.out.println("Insira os seguintes dados para a criar um novo Médico: ");
        System.out.print("codm: ");
        int codm = input.nextInt();
        System.out.print("nome: ");
        String nome = input.next();
        System.out.print("idade: ");
        int idade = input.nextInt();
        System.out.print("especialidade: ");
        String especialidade = input.next();    
        System.out.print("cpf: ");
        long cpf = input.nextLong();        
        System.out.print("cidade: ");
        String cidade = input.next();         
        System.out.print("nroa: ");
        int nroa = input.nextInt();
        
        MedicosBean mb = new MedicosBean(codm, nome, idade, especialidade, cpf, cidade, nroa);
        MedicosModel.create(mb, con);
        System.out.println("Médico criado com sucesso!!");     
    }

    void listarMedicos(Connection con) throws SQLException {
        HashSet all = MedicosModel.listAll(con);
        Iterator<MedicosBean> it = all.iterator();
        while(it.hasNext()) {
            System.out.println(it.next().toString());
        }
    }

    void listarMedicosAmbulatorios(Connection con) throws SQLException {
        HashSet all = MedicosModel.listAllWithAmbulatorios(con);
        Iterator<MedicosBean> it = all.iterator();
        while(it.hasNext()) {
            System.out.println(it.next().toString());
        }
    }
}
