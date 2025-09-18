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

public class CompraDAO {

	private static CompraDAO instance = null;
	CompraDAO compraDAO;
	
	private PreparedStatement insert;
	private PreparedStatement delete;
	private PreparedStatement selectByImovel;
	private PreparedStatement selectByCliente;
	private PreparedStatement selectAll;
	private PreparedStatement selectNewId;
	
	private CompraDAO () throws ClassNotFoundException, SQLException{
		
		Connection conexao = Conexao.getConexao();
		
		//consultas da tabela imovel
		insert = conexao.prepareStatement("insert into compra values (?,?,?,?)");
		delete = conexao.prepareStatement("delete from compra where id = ?");
		selectByImovel = conexao.prepareStatement("select * from compra where id_imovel = ?");
		selectByCliente = conexao.prepareStatement("select * from compra where id_cliente = ?");
		selectAll = conexao.prepareStatement("select * from compra");
		selectNewId = conexao.prepareStatement("select nextval('id_compra')");
	
	}
	

	public static CompraDAO getInstance () throws ClassNotFoundException, SQLException {
		if (instance == null) {
			instance = new CompraDAO();
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
			throw new SelectException("Erro ao buscar novo id da tabela compra");
		}
	}
	
	public void insert (int id_imovel, int id_cliente, String datacompra) throws InsertException, SelectException {
		try {
			int id = selectNewId();
			insert.setInt(1, id_imovel);
			insert.setInt(2, id_cliente);
			insert.setInt(3, id);
			insert.setString(4, datacompra);
			insert.executeUpdate();
		
		} catch (Exception e) {
			throw new InsertException("Erro ao inserir compra");
		}
	}
	
	
	//retorna várias compras
	/*public List<Imovel> selectAll () throws SelectException {
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
	}*/
	
	
}
