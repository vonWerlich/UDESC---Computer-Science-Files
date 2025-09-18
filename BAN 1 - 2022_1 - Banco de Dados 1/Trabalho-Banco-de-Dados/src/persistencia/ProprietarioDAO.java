package persistencia;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import dados.Proprietario;
import exceptions.DeleteException;
import exceptions.InsertException;
import exceptions.SelectException;

public class ProprietarioDAO {

	private static ProprietarioDAO instance = null;
	ProprietarioDAO proprietarioDAO;
	
	private PreparedStatement insert;
	private PreparedStatement delete;
	private PreparedStatement select;
	private PreparedStatement selectAll;
	private PreparedStatement selectNewId;
	
	private ProprietarioDAO () throws ClassNotFoundException, SQLException{
		
		Connection conexao = Conexao.getConexao();
		
		//consultas da tabela imovel
		insert = conexao.prepareStatement("insert into proprietario values (?,?,?)");
		delete = conexao.prepareStatement("delete from proprietario where id = ?");
		select = conexao.prepareStatement("select * from proprietario where id = ?");
		selectAll = conexao.prepareStatement("select * from proprietario");
		selectNewId = conexao.prepareStatement("select nextval('id_proprietario')");
	
	}
	

	public static ProprietarioDAO getInstance () throws ClassNotFoundException, SQLException {
		if (instance == null) {
			instance = new ProprietarioDAO();
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
			throw new SelectException("Erro ao buscar novo id da tabela proprietario");
		}
	}
	
	public void insert (Proprietario proprietario) throws InsertException, SelectException {
		try {
			proprietario.setId(selectNewId());
			insert.setInt(1, proprietario.getId());
			insert.setString(2, proprietario.getNomeprop());
			insert.setString(3, proprietario.getTelefone());
			insert.executeUpdate();
		
		} catch (Exception e) {
			throw new InsertException("Erro ao inserir proprietário");
		}
	}
	
	public void delete (Proprietario proprietario) throws DeleteException {
		
		try {
			delete.setInt(1, proprietario.getId());
			delete.executeUpdate();
			
		} catch (Exception e) {
			throw new DeleteException("Erro ao deletar proprietário");
		}
	}
	
	//retorna um único imóvel
	public Proprietario select (int id_prop) throws SelectException {
		Proprietario prop = null;
		
		try {
			select.setInt(1, id_prop);
			ResultSet rs = select.executeQuery();
			
			if (rs.next()) {
				prop = new Proprietario();
				prop.setId(rs.getInt("id"));
				prop.setNomeprop(rs.getString("nomeprop"));
				prop.setTelefone(rs.getString("telefone"));
			}
			return prop;
		} catch (SQLException e) {
			throw new SelectException ("Não foi possível encontrar o proprietario");
		}
	}
	
	//retorna todos os imóveis
	public List<Proprietario> selectAll () throws SelectException {
		List<Proprietario> props = new ArrayList<Proprietario>();
		Proprietario prop = null;
		
		try {
			ResultSet rs = selectAll.executeQuery();
			while (rs.next()) {
				prop = new Proprietario();
				prop.setId(rs.getInt("id"));
				prop.setNomeprop(rs.getString("nomeprop"));
				prop.setTelefone(rs.getString("telefone"));
				
				props.add(prop);
				}
			return props;
			} catch (SQLException e) {
				throw new SelectException("Erro ao buscar proprietários");
			}
	}

}
