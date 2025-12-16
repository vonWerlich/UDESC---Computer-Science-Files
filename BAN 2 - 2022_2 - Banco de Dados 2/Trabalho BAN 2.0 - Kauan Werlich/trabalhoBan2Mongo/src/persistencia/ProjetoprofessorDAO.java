package persistencia;

import com.mongodb.connection.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import com.mongodb.MongoClient;

import dados.ProjetoProfessor;
import exceptions.DeleteException;
import exceptions.InsertException;
import exceptions.SelectException;
public class ProjetoprofessorDAO {

	private static ProjetoprofessorDAO instance = null;

	private PreparedStatement insert;
	private PreparedStatement deleteByAll;
	private PreparedStatement deleteByNumPro;
	private PreparedStatement deleteByProf;
	private PreparedStatement selectAll;
	
	private ProjetoprofessorDAO () throws ClassNotFoundException, SQLException {
		
		try (Connection conexao = (Connection) new MongoClient("localhost", 27017)) {
			//consultas da tabela disciplinasemestre
			insert = conexao.prepareStatement("insert into projetoprofessor values (?,?)");
			deleteByAll = conexao.prepareStatement("delete from projetoprofessor where numprojeto = ? and professor = ?");
			deleteByNumPro = conexao.prepareStatement("delete from projetoprofessor where numprojeto = ?");
			selectAll = conexao.prepareStatement("select * from projetoprofessor");
		}

	}
	
	public static ProjetoprofessorDAO getInstance () throws ClassNotFoundException, SQLException {
		if (instance == null) {
			instance = new ProjetoprofessorDAO();
		}
		return instance;
	}
	
	public void insertProjProf (int numprojeto, int professor) throws InsertException {
		try {
			insert.setInt(1, numprojeto);
			insert.setInt(2, professor);
			insert.executeUpdate();
		
		} catch (Exception e) {
			throw new InsertException("Erro ao inserir linha na tabela projeto-professor");
		}
	}
	
	public void removeProjProfByAll (int numprojeto, int professor) throws DeleteException {
		try {
			deleteByAll.setInt(1, numprojeto);
			deleteByAll.setInt(2, professor);
			deleteByAll.executeUpdate();
		} catch (Exception e) {
			throw new DeleteException("Erro ao deletar linha na tabela projeto-professor");
		}
	}
	
	public void removeProjProfByNumPro (int numprojeto) throws DeleteException {
		try {
			deleteByNumPro.setInt(1, numprojeto);
			deleteByNumPro.executeUpdate();
		} catch (Exception e) {
			throw new DeleteException("Erro ao deletar linha na tabela projeto-professor");
		}
		
	}
	
	public void removeProjProfByProf (int professor) throws DeleteException {
		try {
			deleteByProf.setInt(1, professor);
			deleteByProf.executeUpdate();
		} catch (Exception e) {
			throw new DeleteException("Erro ao deletar linha na tabela projeto-professor");
		}
	}
	
	public List<ProjetoProfessor> selectAllProjProf () throws SelectException {
		List<ProjetoProfessor> projetoprofessores = new ArrayList<ProjetoProfessor>();
		ProjetoProfessor projprof = null;
		
		try {
			ResultSet rs = selectAll.executeQuery();
			while (rs.next()) {
				projprof = new ProjetoProfessor();
				projprof.setNumprojeto(rs.getInt("numprojeto"));
				projprof.setProfessor(rs.getInt("professor"));
				
				projetoprofessores.add(projprof);
				}
			return projetoprofessores;
			} catch (SQLException e) {
				throw new SelectException("Erro ao buscar linha da tabela projeto-professor");
			}
	}
}
