package persistencia;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import dados.Cliente;
import exceptions.DeleteException;
import exceptions.InsertException;
import exceptions.SelectException;

public class ClienteDAO {

	private static ClienteDAO instance = null;
	ClienteDAO clienteDAO;
	
	private PreparedStatement insert;
	private PreparedStatement delete;
	private PreparedStatement select;
	private PreparedStatement selectAll;
	private PreparedStatement selectNewId;
	private PreparedStatement selectClientesVip;
	
	private ClienteDAO () throws ClassNotFoundException, SQLException{
		
		Connection conexao = Conexao.getConexao();
		
		//consultas da tabela imovel
		insert = conexao.prepareStatement("insert into cliente values (?,?,?)");
		delete = conexao.prepareStatement("delete from cliente where id = ?");
		select = conexao.prepareStatement("select * from cliente where id = ?");
		selectAll = conexao.prepareStatement("select * from cliente");
		selectNewId = conexao.prepareStatement("select nextval('id_cliente')");
		
		selectClientesVip = conexao.prepareStatement("select cliente.id,cliente.nomecliente,cliente.telefone from cliente,compra,imovel where cliente.id"
				+ "= compra.id_cliente and preco >= 1000000  and imovel.id = compra.id_imovel");
	
	}
	

	public static ClienteDAO getInstance () throws ClassNotFoundException, SQLException {
		if (instance == null) {
			instance = new ClienteDAO();
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
	
	public void insert (Cliente cliente) throws InsertException, SelectException {
		try {
			cliente.setId(selectNewId());
			insert.setInt(1, cliente.getId());
			insert.setString(2, cliente.getNomecliente());
			insert.setString(3, cliente.getTelefone());
			insert.executeUpdate();
		
		} catch (Exception e) {
			throw new InsertException("Erro ao inserir aluno");
		}
	}
	
	public void delete (Cliente cliente) throws DeleteException {
		
		try {
			delete.setInt(1, cliente.getId());
			delete.executeUpdate();
			
		} catch (Exception e) {
			throw new DeleteException("Erro ao deletar pessoa");
		}
	}
	
	//retorna um único cliente
	public Cliente select (int id_cliente) throws SelectException {
		Cliente cliente = null;
		
		try {
			select.setInt(1, id_cliente);
			ResultSet rs = select.executeQuery();
			
			if (rs.next()) {
				cliente = new Cliente();
				cliente.setId(rs.getInt("id"));
				cliente.setNomecliente(rs.getString("nomecliente"));
				cliente.setTelefone(rs.getString("telefone"));
			}
			return cliente;
		} catch (SQLException e) {
			throw new SelectException ("Não foi possível encontrar o cliente");
		}
	}
	
	//retorna todos os clientes
	public List<Cliente> selectAll () throws SelectException {
		List<Cliente> clientes = new ArrayList<Cliente>();
		Cliente cliente = null;
		
		try {
			ResultSet rs = selectAll.executeQuery();
			while (rs.next()) {
				cliente = new Cliente();
				cliente.setId(rs.getInt("id"));
				cliente.setNomecliente(rs.getString("nomecliente"));
				cliente.setTelefone(rs.getString("telefone"));
				
				clientes.add(cliente);
				}
			return clientes;
			} catch (SQLException e) {
				throw new SelectException("Erro ao buscar clientes");
			}
	}
	
	public List<Cliente> selectAllVips () throws SelectException {
		List<Cliente> clientes = new ArrayList<Cliente>();
		Cliente cliente = null;
		
		try {
			ResultSet rs = selectClientesVip.executeQuery();
			while (rs.next()) {
				cliente = new Cliente();
				cliente.setId(rs.getInt("id"));
				cliente.setNomecliente(rs.getString("nomecliente"));
				cliente.setTelefone(rs.getString("telefone"));
				
				clientes.add(cliente);
				}
			return clientes;
			} catch (SQLException e) {
				throw new SelectException("Erro ao buscar clientes Vip");
			}
	}
	
}
