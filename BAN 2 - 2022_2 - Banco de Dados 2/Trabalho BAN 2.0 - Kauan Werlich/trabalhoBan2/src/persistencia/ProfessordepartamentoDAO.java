package persistencia;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import dados.ProfessorDepartamento;
import exceptions.DeleteException;
import exceptions.InsertException;
import exceptions.SelectException;
import exceptions.UpdateException;

public class ProfessordepartamentoDAO {

	private static ProfessordepartamentoDAO instance = null;
	ProfessordepartamentoDAO professordepartamentoDAO;
	
	private PreparedStatement insert;
	private PreparedStatement delete;
	private PreparedStatement delete2;
	private PreparedStatement deletebyAll;
	private PreparedStatement update;
	private PreparedStatement selectAll;
	
	private ProfessordepartamentoDAO () throws ClassNotFoundException, SQLException {
		
		Connection conexao = Conexao.getConexao();
		
		//consultas da tabela estudante
		insert = conexao.prepareStatement("insert into profdepartamento values (?,?,?)");
		delete = conexao.prepareStatement("delete from profdepartamento where matricula = ?");
		deletebyAll = conexao.prepareStatement("delete from profdepartamento where matricula = ? and numdep = ?");
		delete2 = conexao.prepareStatement("delete from profdepartamento where numdep = ?");
		update = conexao.prepareStatement("update profdepartamento set porcentagem = ? where matricula = ? and numdep = ?");
		selectAll = conexao.prepareStatement("select * from profdepartamento");
	}
	
	public static ProfessordepartamentoDAO getInstance () throws ClassNotFoundException, SQLException {
		if (instance == null) {
			instance = new ProfessordepartamentoDAO();
		}
		return instance;
	}
	
	public void insert (int matricula, int numdep, double porcentagem) throws InsertException, SelectException {
		try {
			insert.setInt(1, matricula);
			insert.setInt(2, numdep);
			insert.setDouble(3, porcentagem);
			insert.executeUpdate();
		
		} catch (Exception e) {
			throw new InsertException("Erro ao inserir nova linha na tabela professor-departamento");
		}
	}
	
	public void deleteByMat (int matricula) throws DeleteException {
		
		try {
			delete.setInt(1, matricula);
			delete.executeUpdate();
			
		} catch (Exception e) {
			throw new DeleteException("Erro ao deletar linha da tabela professor-departamento");
		}
	}
	
	public void deleteByNumDep (int numdep) throws DeleteException {
			
			try {
				delete2.setInt(1, numdep);
				delete2.executeUpdate();
				
			} catch (Exception e) {
				throw new DeleteException("Erro ao deletar linha da tabela professor-departamento");
			}
		}
	
	public void deleteByAll (int matricula, int numdep) throws DeleteException {
		
		try {
			deletebyAll.setInt(1, matricula);
			deletebyAll.setInt(2, numdep);
			deletebyAll.executeUpdate();
			
		} catch (Exception e) {
			throw new DeleteException("Erro ao deletar linha da tabela professor-departamento");
		}
	}
	
	//esse update só altera a porcentagem
	public void update (int matricula, int numdep, double porcentagem) throws UpdateException {
		try {
			update.setDouble(1, porcentagem);
			update.setInt(2, matricula);
			update.setInt(3, numdep);
			update.executeUpdate();
			
		} catch (SQLException e) {
			throw new UpdateException("Erro ao atualizar linha da tabela professor-departamento");
		}
	}
	
	public List<ProfessorDepartamento> selectAllProfDep () throws SelectException {
		List<ProfessorDepartamento> professordepartaemento = new ArrayList<ProfessorDepartamento>();
		ProfessorDepartamento profdep = null;
		
		try {
			ResultSet rs = selectAll.executeQuery();
			while (rs.next()) {
				profdep = new ProfessorDepartamento();
				profdep.setMatricula(rs.getInt("matricula"));
				profdep.setNumdep(rs.getInt("numdep"));
				profdep.setPorcentagem(rs.getFloat("porcentagem"));
				
				professordepartaemento.add(profdep);
				}
			return professordepartaemento;
			} catch (SQLException e) {
				throw new SelectException("Erro ao buscar linha da tabela professor-departamento");
			}
	}
}
