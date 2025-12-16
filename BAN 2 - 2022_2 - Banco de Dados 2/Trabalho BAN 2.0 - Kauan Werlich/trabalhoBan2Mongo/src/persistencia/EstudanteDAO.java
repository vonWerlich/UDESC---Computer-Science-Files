package persistencia;

import com.mongodb.connection.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import com.mongodb.MongoClient;

import dados.Estudante;
import exceptions.DeleteException;
import exceptions.InsertException;
import exceptions.SelectException;
import exceptions.UpdateException;

public class EstudanteDAO {

	private static EstudanteDAO instance = null;
	EstudanteDAO estudanteDAO;
	
	private PreparedStatement insert;
	private PreparedStatement delete;
	private PreparedStatement update;
	private PreparedStatement select;
	private PreparedStatement selectAll;
	
	private EstudanteDAO () throws ClassNotFoundException, SQLException {
		
		try (Connection conexao = (Connection) new MongoClient("localhost", 27017)) {
			//consultas da tabela estudante
			insert = conexao.prepareStatement("insert into estudante values (?,?,?)");
			delete = conexao.prepareStatement("delete from estudante where matricula = ?");
			update = conexao.prepareStatement("update estudante set tipocurso = ?, depcurso = ? where matricula = ?");
			select = conexao.prepareStatement("select * from estudante where matricula = ?");
			selectAll = conexao.prepareStatement("select * from estudante");
		}
	}
	
	public static EstudanteDAO getInstance () throws ClassNotFoundException, SQLException {
		if (instance == null) {
			instance = new EstudanteDAO();
		}
		return instance;
	}
	
	public void insert (Estudante estudante) throws InsertException, SelectException {
		try {
			insert.setInt(1, estudante.getMatricula());
			insert.setString(2, estudante.getTipocurso());
			insert.setInt(3, estudante.getDepcurso());
			insert.executeUpdate();
		
		} catch (Exception e) {
			throw new InsertException("Erro ao inserir estudante");
		}
	}
	
	public void delete (int matricula) throws DeleteException {
		
		try {
			delete.setInt(1, matricula);
			delete.executeUpdate();
			
		} catch (Exception e) {
			throw new DeleteException("Erro ao deletar estudante");
		}
	}
	
	public void update (Estudante estudante) throws UpdateException {
		try {
			update.setString(1, estudante.getTipocurso());
			update.setInt(2, estudante.getDepcurso());
			update.setInt(3, estudante.getMatricula());
			update.executeUpdate();
			
		} catch (SQLException e) {
			throw new UpdateException("Erro ao atualizar projeto");
		}
	}
	
	//retorna um único estudante
	public Estudante select (int estudante) throws SelectException {
		Estudante est = null;
		
		try {
			select.setInt(1, estudante);
			ResultSet rs = select.executeQuery();
			
			if (rs.next()) {
				est = new Estudante();
				est.setMatricula(rs.getInt("matricula"));
				est.setTipocurso(rs.getString("tipocurso"));
				est.setDepcurso(rs.getInt("depcurso"));

			}
			return est;
		} catch (SQLException e) {
			throw new SelectException ("Não foi possível encontrar o estudante");
		}
	}
	
	public List<Estudante> selectAll () throws SelectException {
		List<Estudante> estudantes = new ArrayList<Estudante>();
		Estudante est = null;
		
		try {
			ResultSet rs = selectAll.executeQuery();
			while (rs.next()) {
				est = new Estudante();
				est.setMatricula(rs.getInt("matricula"));
				est.setTipocurso(rs.getString("tipocurso"));
				est.setDepcurso(rs.getInt("depcurso"));
				
				estudantes.add(est);
				}
			return estudantes;
			} catch (SQLException e) {
				throw new SelectException("Erro ao buscar estudantes");
			}
	}
}
