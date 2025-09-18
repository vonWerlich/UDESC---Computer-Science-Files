package outros;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author rebeca
 */
public class AmbulatoriosController {
    
    public void createAmbulatorio(Connection con) throws SQLException {
        Scanner input = new Scanner(System.in);
        System.out.println("Insira os seguintes dados para a criar um novo Ambulatório: ");
        System.out.print("nroa: ");
        int nroa = input.nextInt();
        System.out.print("capacidade: ");
        int capacidade = input.nextInt();
        System.out.print("andar: ");
        int andar = input.nextInt();
        AmbulatoriosBean ab = new AmbulatoriosBean(nroa, capacidade, andar);
        AmbulatoriosModel.create(ab, con);
        System.out.println("Ambulatório criado com sucesso!!");
    }

    void listarAmbulatorio(Connection con) throws SQLException {
        HashSet all = AmbulatoriosModel.listAll(con);
        Iterator<AmbulatoriosBean> it = all.iterator();
        while(it.hasNext()) {
            System.out.println(it.next().toString());
        }
    }
}
