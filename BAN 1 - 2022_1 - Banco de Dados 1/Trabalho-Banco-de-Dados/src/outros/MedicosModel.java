package outros;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.HashSet;
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
public class MedicosModel {

    static void create(MedicosBean m, Connection con) throws SQLException {
        PreparedStatement st;
            st = con.prepareStatement("INSERT INTO medicos (codm, nome, idade, especialidade, cpf, cidade, nroa) "
                    + "VALUES (?,?,?,?,?,?,?)");
            st.setInt(1, m.getCodm());
            st.setString(2, m.getNome());
            st.setInt(3, m.getIdade());
            st.setString(4, m.getEspecialidade());
            st.setLong(5, m.getCpf());
            st.setString(6, m.getCidade());
            st.setInt(7, m.getNroa());
            st.execute();
            st.close();
    }
    
    static HashSet listAll(Connection con) throws SQLException {
        Statement st;
        HashSet list = new HashSet();
            st = con.createStatement();
            String sql = "SELECT codm, nome, idade, especialidade, cpf, cidade, nroa FROM medicos";
            ResultSet result = st.executeQuery(sql);
            while(result.next()) {
                list.add(new MedicosBean(result.getInt(1), result.getString(2), result.getInt(3), 
                result.getString(4), result.getLong(5), result.getString(6), result.getInt(7)));
            }
        return list;
    }    

    static HashSet listAllWithAmbulatorios(Connection con) throws SQLException {
        Statement st;
        HashSet list = new HashSet();
        st = con.createStatement();
        String sql = "SELECT codm, nome, idade, especialidade, cpf, cidade, medicos.nroa, andar, capacidade FROM medicos NATURAL JOIN ambulatorios";
        ResultSet result = st.executeQuery(sql);
        while(result.next()) {
            MedicosBean mb = new MedicosBean(result.getInt(1), result.getString(2), result.getInt(3),
                    result.getString(4), result.getLong(5), result.getString(6), result.getInt(7));
            AmbulatoriosBean a = new AmbulatoriosBean(result.getInt(7), result.getInt(8), result.getInt(9));
            mb.setAmbulatorio(a);
            list.add(mb);
        }
        return list;
    }
}
