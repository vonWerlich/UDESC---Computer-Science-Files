package persistencia;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import dados.*;
import exceptions.DeleteException;
import exceptions.InsertException;
import exceptions.SelectException;
import exceptions.UpdateException;


public class ProfessorDAO {

	private static ProfessorDAO instance = null;
	ProfessorDAO professorDAO;
		
	private PreparedStatement insert;
	private PreparedStatement delete;
	private PreparedStatement update;
	private PreparedStatement select;
	private PreparedStatement selectAll;
	private PreparedStatement porcentagem;

	
	private ProfessorDAO () throws ClassNotFoundException, SQLException{
		
		Connection conexao = Conexao.getConexao();
		
		//consultas da tabela professor
		insert = conexao.prepareStatement("insert into professor values (?,?,?)");
		delete = conexao.prepareStatement("delete from professor where matricula = ?");
		update = conexao.prepareStatement("update professor set especialidade = ?, sala = ? where matricula = ?");
		select = conexao.prepareStatement("select * from professor where matricula = ?");
		selectAll = conexao.prepareStatement("select * from professor");
		porcentagem = conexao.prepareStatement("select calculaPorcentagemTempo(?)");
		
			}
		
	public static ProfessorDAO getInstance () throws ClassNotFoundException, SQLException {
		if (instance == null) {
			instance = new ProfessorDAO();
	}
		return instance;
	}
	
	public void insert (Professor professor) throws InsertException, SelectException {
		try {
			insert.setInt(1, professor.getMatricula());
			insert.setString(2, professor.getEspecialidade());
			insert.setString(3, professor.getSala());
			insert.executeUpdate();
	
			} catch (Exception e) {
			throw new InsertException("Erro ao inserir professor");
		}
	}
	
	public void delete (int matricula) throws DeleteException {
		
		try {
			delete.setInt(1, matricula);
			delete.executeUpdate();
			
		} catch (Exception e) {
			throw new DeleteException("Erro ao deletar professor");
		}
	}
		
	public void update (Professor professor) throws UpdateException {
		try {
			update.setString(1, professor.getEspecialidade());
			update.setString(2, professor.getSala());
			update.setInt(3, professor.getMatricula());
			update.executeUpdate();
			
		} catch (SQLException e) {
			throw new UpdateException("Erro ao atualizar professor");
		}
	}
	
	//retorna um único professor
	public Professor select (int matricula) throws SelectException {
			Professor prof = null;
		
		try {
			select.setInt(1, matricula);
			ResultSet rs = select.executeQuery();
			
			if (rs.next()) {
				prof = new Professor();
				prof.setMatricula(rs.getInt("matricula"));
				prof.setEspecialidade(rs.getString("especialidade"));
				prof.setSala(rs.getString("sala"));
			}
		return prof;
			} catch (SQLException e) {
			throw new SelectException ("Não foi possível encontrar o professor");
		}
	}
	
	public List<Professor> selectAll () throws SelectException {
		List<Professor> professores = new ArrayList<Professor>();
		Professor prof = null;
		
		try {
			ResultSet rs = selectAll.executeQuery();
			while (rs.next()) {
				prof = new Professor();
				prof.setMatricula(rs.getInt("matricula"));
				prof.setEspecialidade(rs.getString("especialidade"));
				prof.setSala(rs.getString("sala"));
				
				professores.add(prof);
				}
			return professores;
			} catch (SQLException e) {
				throw new SelectException("Erro ao buscar professor");
			}
	}
	
	public double porcentagemTempo (int matricula) throws SelectException {
		try {
			porcentagem.setInt(1, matricula);
			ResultSet rs = porcentagem.executeQuery();
			
			if (rs.next()) {
				double temp = rs.getDouble("calculaporcentagemtempo");
				return temp;
			}
			else {
				return 0;
			}
			} catch (SQLException e) {
				throw new SelectException("Erro ao buscar professor");
			}
	}
	
}
