package persistencia;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import dados.Imovel;
import exceptions.DeleteException;
import exceptions.InsertException;
import exceptions.SelectException;

public class ImovelDAO {
	
	private static ImovelDAO instance = null;
	ImovelDAO imovelDAO;
	
	private PreparedStatement insert;
	private PreparedStatement delete;
	private PreparedStatement select;
	private PreparedStatement selectAll;
	private PreparedStatement selectNewId;
	private PreparedStatement selectMenorPreco;
	private PreparedStatement insertImoProp;
	
	private ImovelDAO () throws ClassNotFoundException, SQLException{
		
		Connection conexao = Conexao.getConexao();
		
		//consultas da tabela imovel
		insert = conexao.prepareStatement("insert into imovel values (?,?,?,?,?)");
		delete = conexao.prepareStatement("delete from imovel where id = ?");
		select = conexao.prepareStatement("select * from imovel where id = ?");
		selectAll = conexao.prepareStatement("select * from imovel");
		selectNewId = conexao.prepareStatement("select nextval('id_imovel')");
		selectMenorPreco = conexao.prepareStatement("select * from imovel where preco = (select min(preco) from imovel)");
		
		//consultas da tabela imovelproprietario
		insertImoProp = conexao.prepareStatement("insert into imovelproprietario values (?,?)");
	
	}
	

	public static ImovelDAO getInstance () throws ClassNotFoundException, SQLException {
		if (instance == null) {
			instance = new ImovelDAO();
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
			throw new SelectException("Erro ao buscar novo id da tabela imóvel");
		}
	}
	
	public void insert (Imovel imovel) throws InsertException, SelectException {
		try {
			imovel.setId(selectNewId());
			insert.setInt(1, imovel.getId());
			insert.setDouble(2, imovel.getArea());
			insert.setDouble(3, imovel.getPreco());
			insert.setString(4, imovel.getDescricao());
			insert.setString(5, imovel.getCep());
			insert.executeUpdate();
		
		} catch (Exception e) {
			throw new InsertException("Erro ao inserir aluno");
		}
	}
	
	public void delete (Imovel imovel) throws DeleteException {
		
		try {
			delete.setInt(1, imovel.getId());
			delete.executeUpdate();
			
		} catch (Exception e) {
			throw new DeleteException("Erro ao deletar pessoa");
		}
	}
	
	//retorna um único imóvel
	public Imovel select (int id_imovel) throws SelectException {
		Imovel imovel = null;
		
		try {
			select.setInt(1, id_imovel);
			ResultSet rs = select.executeQuery();
			
			if (rs.next()) {
				imovel = new Imovel();
				imovel.setId(rs.getInt("id"));
				imovel.setArea(rs.getDouble("area"));
				imovel.setPreco(rs.getDouble("preco"));
				imovel.setDescricao(rs.getString("descricao"));
				imovel.setCep(rs.getString("cep"));
			}
			return imovel;
		} catch (SQLException e) {
			throw new SelectException ("Não foi possível encontrar o aluno");
		}
	}
	
	//retorna todos os imóveis
	public List<Imovel> selectAll () throws SelectException {
		List<Imovel> imoveis = new ArrayList<Imovel>();
		Imovel imovel = null;
		
		try {
			ResultSet rs = selectAll.executeQuery();
			while (rs.next()) {
				imovel = new Imovel();
				imovel.setId(rs.getInt("id"));
				imovel.setArea(rs.getDouble("area"));
				imovel.setPreco(rs.getDouble("preco"));
				imovel.setDescricao(rs.getString("descricao"));
				imovel.setCep(rs.getString("cep"));
				
				imoveis.add(imovel);
				}
			return imoveis;
			} catch (SQLException e) {
				throw new SelectException("Erro ao buscar imóveis");
			}
	}
	
	public List<Imovel> selectMenores () throws SelectException {
		List<Imovel> imoveis = new ArrayList<Imovel>();
		Imovel imovel = null;
		
		try {
			ResultSet rs = selectMenorPreco.executeQuery();
			while (rs.next()) {
				imovel = new Imovel();
				imovel.setId(rs.getInt("id"));
				imovel.setArea(rs.getDouble("area"));
				imovel.setPreco(rs.getDouble("preco"));
				imovel.setDescricao(rs.getString("descricao"));
				imovel.setCep(rs.getString("cep"));
				
				imoveis.add(imovel);
				}
			return imoveis;
			} catch (SQLException e) {
				throw new SelectException("Erro ao buscar imóveis");
			}
	}
	
	public void insertImoProp (int id_imovel, int id_prop) throws InsertException {
		try {
			insertImoProp.setInt(1, id_imovel);
			insertImoProp.setInt(2, id_prop);
			insertImoProp.executeUpdate();
		
		} catch (Exception e) {
			throw new InsertException("Erro ao inserir proprietário no imóvel");
		}
	}

}
