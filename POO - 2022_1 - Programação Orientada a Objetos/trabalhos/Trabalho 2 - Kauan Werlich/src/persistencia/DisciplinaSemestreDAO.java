package persistencia;

import dados.*;
import exceptions.DeleteException;
import exceptions.InsertException;
import exceptions.SelectException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class DisciplinaSemestreDAO {

		private static DisciplinaSemestreDAO instance = null;

		private PreparedStatement insert;
		private PreparedStatement deleteByDiscESem;
		private PreparedStatement deleteBySemestre;
		private PreparedStatement deleteByDisciplina;
		private PreparedStatement selectBySemestre;//retorna todas as disciplinas que se relacionam com esse id_semestre
		private PreparedStatement selectByDisciplina;//retorna todos os semestres que se relacionam com esse id_disciplina
		//private PreparedStatement selectAll;//retorna todas as tuplas da tabela
		
		private DisciplinaSemestreDAO () throws ClassNotFoundException, SQLException {
			
			Connection conexao = Conexao.getConexao();
			
			//consultas da tabela disciplinasemestre
			insert = conexao.prepareStatement("insert into disciplinasemestre values (?,?)");
			deleteByDiscESem = conexao.prepareStatement("delete from disciplinasemestre where id_semestre = ? and id_disciplina = ?");
			deleteBySemestre = conexao.prepareStatement("delete from disciplinasemestre where id_semestre = ?");
			deleteByDisciplina = conexao.prepareStatement("delete from disciplinasemestre where id_disciplina = ?");
			selectBySemestre = conexao.prepareStatement("select id_disciplina from disciplinasemestre where id_semestre = ?");
			selectByDisciplina = conexao.prepareStatement("select id_semestre from disciplinasemestre where id_disciplina = ?");
			//selectAll = conexao.prepareStatement("select * from disciplinasemestre");
			
		}
	
	
	public static DisciplinaSemestreDAO getInstance () throws ClassNotFoundException, SQLException {
		if (instance == null) {
			instance = new DisciplinaSemestreDAO();
		}
		return instance;
	}
	
	public void insertDisciplinaSemestre (Semestre semestre, Disciplina disciplina) throws InsertException {
		try {
			insert.setInt(1, semestre.getIdSemestre());
			insert.setInt(2, disciplina.getIdDisciplina());
			insert.executeUpdate();
		
		} catch (Exception e) {
			throw new InsertException("Erro ao inserir disciplina em um semestre");
		}
	}
	
	public void removeDiscSemByDiscESem (int id_semestre, int id_disciplina) throws SQLException, DeleteException {
		try {
			deleteByDiscESem.setInt(1, id_semestre);
			deleteByDiscESem.setInt(2, id_disciplina);
			deleteByDiscESem.executeUpdate();
		} catch (Exception e) {
			throw new DeleteException("Erro ao deletar linha da tabela disciplina-semestre");
		}
	}
	
	public void removeDiscSemByDisciplina (Disciplina disciplina) throws SQLException, DeleteException {
		try {
			deleteByDisciplina.setInt(1, disciplina.getIdDisciplina());
			deleteByDisciplina.executeUpdate();
		} catch (Exception e) {
			throw new DeleteException("Erro ao deletar linha da tabela disciplina-semestre a partir da disciplina");
		}
		
	}
	
	public void removeDiscSemBySemestre (Semestre semestre) throws SQLException, DeleteException {
		try {
			deleteBySemestre.setInt(1, semestre.getIdSemestre());
			deleteBySemestre.executeUpdate();
		} catch (Exception e) {
			throw new DeleteException("Erro ao deletar linha da tabela disciplina-semestre a partir do semestre");
		}
	}
	
	public List<Disciplina> selectBySemestre (Semestre semestre) throws SelectException, ClassNotFoundException, SQLException {
		List<Disciplina> disciplinas = new ArrayList<Disciplina>();
		Disciplina disciplina = null;
		Disciplina temp = new Disciplina();
		DisciplinaDAO disciplinaDAO = DisciplinaDAO.getInstance();
		
		try {
			selectBySemestre.setInt(1, semestre.getIdSemestre());
			ResultSet rs = selectBySemestre.executeQuery();
			while (rs.next()) {
				disciplina = new Disciplina();
				disciplina.setIdDisciplina(rs.getInt("id_disciplina"));
				temp = disciplinaDAO.select(disciplina.getIdDisciplina());
				disciplina.setNomeDisciplina(temp.getNomeDisciplina());
				
				disciplinas.add(disciplina);
			}
			return disciplinas;
		} catch (Exception e) {
			throw new SelectException("Erro ao buscar disciplinas relacionadas a um semestre");
		}
	}
	
	public List<Semestre> selectByDisciplina (Disciplina disciplina) throws SelectException, ClassNotFoundException, SQLException {
		List<Semestre> semestres = new ArrayList<Semestre>();
		Semestre semestre = null;
		Semestre temp = new Semestre();
		SemestreDAO semestreDAO = SemestreDAO.getInstance();
		
		try {
			selectByDisciplina.setInt(1, disciplina.getIdDisciplina());
			ResultSet rs = selectByDisciplina.executeQuery();
			while (rs.next()) {
				semestre = new Semestre();
				semestre.setIdSemestre(rs.getInt("id_semestre"));
				temp = semestreDAO.select(semestre.getIdSemestre());
				semestre.setNomeSemestre(temp.getNomeSemestre());
				
				semestres.add(semestre);
			}
			return semestres;
		} catch (Exception e) {
			throw new SelectException("Erro ao buscar semestres relacionados a uma disciplina");
		}
	}
	
	
}
