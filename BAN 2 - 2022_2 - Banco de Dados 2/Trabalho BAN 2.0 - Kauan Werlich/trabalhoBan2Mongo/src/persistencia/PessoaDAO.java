package persistencia;

import com.mongodb.connection.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import com.mongodb.MongoClient;

import dados.Pessoa;
import exceptions.DeleteException;
import exceptions.InsertException;
import exceptions.SelectException;
import exceptions.UpdateException;

public class PessoaDAO {

	private static PessoaDAO instance = null;
	PessoaDAO pessoaDAO;
	
	private PreparedStatement insert;
	private PreparedStatement delete;
	private PreparedStatement update;
	private PreparedStatement select;
	private PreparedStatement selectAll;
	private PreparedStatement selectNewId;
	
	private PessoaDAO () throws ClassNotFoundException, SQLException {
		
		try (Connection conexao = (Connection) new MongoClient("localhost", 27017)) {
			//consultas da tabela aluno
			insert = conexao.prepareStatement("insert into pessoa values (?,?,?)");
			delete = conexao.prepareStatement("delete from pessoa where matricula = ?");
			update = conexao.prepareStatement("update pessoa set nome = ?, idade = ? where matricula = ?");
			select = conexao.prepareStatement("select * from pessoa where matricula = ?");
			selectAll = conexao.prepareStatement("select * from pessoa");
			selectNewId = conexao.prepareStatement("select nextval('seqmatricula')");
		}
	}
	
	public static PessoaDAO getInstance () throws ClassNotFoundException, SQLException {
		if (instance == null) {
			instance = new PessoaDAO();
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
			throw new SelectException("Erro ao buscar nova matrícula da tabela pessoa");
		}
	}
	
	public void insert (Pessoa pessoa) throws InsertException, SelectException {
		try {
			pessoa.setMatricula(selectNewId());
			insert.setInt(1, pessoa.getMatricula());
			insert.setString(2, pessoa.getNome());
			insert.setInt(3, pessoa.getIdade());
			insert.executeUpdate();
		
		} catch (Exception e) {
			throw new InsertException("Erro ao inserir pessoa");
		}
	}
	
	public void delete (int matricula) throws DeleteException {
		
		try {
			delete.setInt(1, matricula);
			delete.executeUpdate();
			
		} catch (Exception e) {
			throw new DeleteException("Erro ao deletar pessoa");
		}
	}
	
	public void update (Pessoa pessoa) throws UpdateException {
		try {
			update.setString(1, pessoa.getNome());
			update.setInt(2,pessoa.getIdade());
			update.setInt(3, pessoa.getMatricula());
			update.executeUpdate();
			
		} catch (SQLException e) {
			throw new UpdateException("Erro ao atualizar pessoa");
		}
	}
	
	//retorna uma única pessoa
	public Pessoa select (int matricula) throws SelectException {
		Pessoa pessoa = null;
		
		try {
			select.setInt(1, matricula);
			ResultSet rs = select.executeQuery();
			
			if (rs.next()) {
				pessoa = new Pessoa();
				pessoa.setMatricula(rs.getInt("matricula"));
				pessoa.setNome(rs.getString("nome"));
				pessoa.setIdade(rs.getInt("idade"));
			}
			return pessoa;
		} catch (SQLException e) {
			throw new SelectException ("Não foi possível encontrar a pessoa");
		}
	}
	
	public List<Pessoa> selectAll () throws SelectException {
		List<Pessoa> pessoas = new ArrayList<Pessoa>();
		Pessoa pessoa = null;
		
		try {
			ResultSet rs = selectAll.executeQuery();
			while (rs.next()) {
				pessoa = new Pessoa();
				pessoa.setMatricula(rs.getInt("matricula"));
				pessoa.setNome(rs.getString("nome"));
				pessoa.setIdade(rs.getInt("idade"));
				
				pessoas.add(pessoa);
				}
			return pessoas;
			} catch (SQLException e) {
				throw new SelectException("Erro ao buscar pessoa");
			}
	}
	
	public String toString(Pessoa pessoa) {
		return pessoa.toString();
	}
}
