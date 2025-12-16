package persistencia;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import dados.ProjetoEstudante;
import exceptions.DeleteException;
import exceptions.InsertException;
import exceptions.SelectException;
import exceptions.UpdateException;

public class ProjetoestudanteDAO {

	private static ProjetoestudanteDAO instance = null;
	ProjetoestudanteDAO projetoestudanteDAO;
	
	private PreparedStatement insert;
	private PreparedStatement delete;
	private PreparedStatement update;
	private PreparedStatement selectAll;
	
	private ProjetoestudanteDAO () throws ClassNotFoundException, SQLException {
		
		Connection conexao = Conexao.getConexao();
		
		//consultas da tabela estudante
		insert = conexao.prepareStatement("insert into projetoestudante values (?,?,?)");
		delete = conexao.prepareStatement("delete from projetoestudante where numprojeto = ? and estudante = ?");
		update = conexao.prepareStatement("update projetoestudante set supervisor = ? where estudante = ? and numprojeto = ?");
		selectAll = conexao.prepareStatement("select * from projetoestudante");
	}
	
	public static ProjetoestudanteDAO getInstance () throws ClassNotFoundException, SQLException {
		if (instance == null) {
			instance = new ProjetoestudanteDAO();
		}
		return instance;
	}
	
	public void insert (int numprojeto, int estudante, int supervisor) throws InsertException, SelectException {
		try {
			insert.setInt(1, numprojeto);
			insert.setInt(2, estudante);
			insert.setDouble(3, supervisor);
			insert.executeUpdate();
		
		} catch (Exception e) {
			throw new InsertException("Erro ao inserir nova linha na tabela projeto-estudante");
		}
	}
	
	public void delete (int numprojeto, int estudante) throws DeleteException {
		
		try {
			delete.setInt(1, numprojeto);
			delete.setInt(2, estudante);
			delete.executeUpdate();
			
		} catch (Exception e) {
			throw new DeleteException("Erro ao deletar linha da tabela projeto-estudante");
		}
	}
	
	//esse update só altera o supervisor
	public void update (int numprojeto, int estudante, int supervisor) throws UpdateException {
		try {
			update.setDouble(1, supervisor);
			update.setInt(2, estudante);
			update.setInt(3, numprojeto);
			update.executeUpdate();
			
		} catch (SQLException e) {
			throw new UpdateException("Erro ao atualizar linha da tabela projeto-estudante");
		}
	}
	
	public List<ProjetoEstudante> selectAllProjEst () throws SelectException {
		List<ProjetoEstudante> projetoestudante = new ArrayList<ProjetoEstudante>();
		ProjetoEstudante projest = null;
		
		try {
			ResultSet rs = selectAll.executeQuery();
			while (rs.next()) {
				projest = new ProjetoEstudante();
				projest.setNumprojeto(rs.getInt("numprojeto"));
				projest.setEstudante(rs.getInt("estudante"));
				projest.setSupervisor(rs.getInt("supervisor"));
				
				projetoestudante.add(projest);
				}
			return projetoestudante;
			} catch (SQLException e) {
				throw new SelectException("Erro ao buscar linha da tabela projeto-estudante");
			}
	}
	
}
