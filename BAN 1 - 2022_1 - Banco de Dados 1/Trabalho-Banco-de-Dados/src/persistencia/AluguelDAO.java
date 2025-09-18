package persistencia;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import dados.*;
import exceptions.InsertException;
import exceptions.SelectException;

public class AluguelDAO {
	
	private static AluguelDAO instance = null;
	AluguelDAO aluguelDAO;
	
	private PreparedStatement insert;
	private PreparedStatement delete;
	private PreparedStatement selectByImovel;
	private PreparedStatement selectByCliente;
	private PreparedStatement selectAll;
	private PreparedStatement selectNewId;
	
	private AluguelDAO () throws ClassNotFoundException, SQLException{
		
		Connection conexao = Conexao.getConexao();
		
		//consultas da tabela aluguel
		insert = conexao.prepareStatement("insert into aluguel values (?,?,?,?,?)");
		delete = conexao.prepareStatement("delete from aluguel where id = ?");
		selectByImovel = conexao.prepareStatement("select * from aluguel where id_imovel = ?");
		selectByCliente = conexao.prepareStatement("select * from aluguel where id_cliente = ?");
		selectAll = conexao.prepareStatement("select * from aluguel");
		selectNewId = conexao.prepareStatement("select nextval('id_aluguel')");
	
	}
	

	public static AluguelDAO getInstance () throws ClassNotFoundException, SQLException {
		if (instance == null) {
			instance = new AluguelDAO();
		}
		return instance;
	}
	
	public int selectNewId () throws SelectException {
		try {
			ResultSet rs = selectNewId.executeQuery();
			if (rs.next()) {
				return rs.getInt(1);
			} else {
				return 0;
			}
		} catch (SQLException e) {
			throw new SelectException("Erro ao buscar novo id da tabela aluguel");
		}
	}
	
	public void insert (int id_imovel, int id_cliente, String datainicio, String datatermino) throws InsertException, SelectException {
		try {
			int id = selectNewId();
			insert.setInt(1, id_imovel);
			insert.setInt(2, id_cliente);
			insert.setInt(3, id);
			insert.setString(4, datainicio);
			insert.setString(5, datatermino);
			insert.executeUpdate();
		
		} catch (Exception e) {
			throw new InsertException("Erro ao inserir aluguel");
		}
	}
	
	
	
	
	
}
