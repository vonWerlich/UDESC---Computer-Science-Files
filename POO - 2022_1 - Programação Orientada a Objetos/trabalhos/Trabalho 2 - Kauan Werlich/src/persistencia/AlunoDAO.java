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

public class AlunoDAO {

	private static AlunoDAO instance = null;
	AlunoDAO alunoDAO;
	
	private PreparedStatement insert;
	private PreparedStatement delete;
	private PreparedStatement update;
	private PreparedStatement select;
	private PreparedStatement selectAll;
	private PreparedStatement selectNewId;
	private PreparedStatement insertAlunoDisciplina;
	private PreparedStatement removeAlunDiscSemByAluno;
	private PreparedStatement removeAlunDiscSemByDisc;
	private PreparedStatement removeAlunDiscSemBySem;
	private PreparedStatement selectSemestreByAluno;
	private PreparedStatement selectDisciplinaBySemestre;
	
	private AlunoDAO () throws ClassNotFoundException, SQLException{
		
		Connection conexao = Conexao.getConexao();
		
		//consultas da tabela aluno
		insert = conexao.prepareStatement("insert into aluno values (?,?,?)");
		delete = conexao.prepareStatement("delete from aluno where id = ?");
		update = conexao.prepareStatement("update aluno set matricula = ?, nomealuno = ? where id = ?");
		select = conexao.prepareStatement("select * from aluno where id = ?");
		selectAll = conexao.prepareStatement("select * from aluno");
		selectNewId = conexao.prepareStatement("select nextval('id_aluno')");
		
		//consultas da tabela alunodisciplinasemestre
		insertAlunoDisciplina = conexao.prepareStatement("insert into alunodisciplinasemestre values (?,?,?)");
		removeAlunDiscSemByAluno = conexao.prepareStatement("delete from alunodisciplinasemestre where id_aluno = ?");
		removeAlunDiscSemByDisc = conexao.prepareStatement("delete from alunodisciplinasemestre where id_disciplina = ?");
		removeAlunDiscSemBySem = conexao.prepareStatement("delete from alunodisciplinasemestre where id_semestre = ?");
		selectSemestreByAluno = conexao.prepareStatement("select distinct id_semestre from alunodisciplinasemestre where id_aluno = ?");
		selectDisciplinaBySemestre = conexao.prepareStatement("select id_disciplina from alunodisciplinasemestre where id_semestre = ? and id_aluno =?");
		
	
	}
	
	public static AlunoDAO getInstance () throws ClassNotFoundException, SQLException {
		if (instance == null) {
			instance = new AlunoDAO();
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
			throw new SelectException("Erro ao buscar novo id da tabela aluno");
		}
	}
	
	public void insert (Aluno aluno) throws InsertException, SelectException {
		try {
			aluno.setIdAluno(selectNewId());
			insert.setInt(1, aluno.getIdAluno());
			insert.setInt(2, aluno.getMatricula());
			insert.setString(3, aluno.getNomeAluno());
			insert.executeUpdate();
		
		} catch (Exception e) {
			throw new InsertException("Erro ao inserir aluno");
		}
	}
	
	public void delete (int id_aluno) throws DeleteException {
		
		try {
			delete.setInt(1, id_aluno);
			delete.executeUpdate();
			
		} catch (Exception e) {
			throw new DeleteException("Erro ao deletar pessoa");
		}
	}
	
	public void removeAlunoDiscSemByDisc (Disciplina disciplina) throws DeleteException {
		try {
			removeAlunDiscSemByDisc.setInt(1, disciplina.getIdDisciplina());
			removeAlunDiscSemByDisc.executeUpdate();
		} catch (Exception e) {
			throw new DeleteException("Erro ao deletar linha da tabela aluno-disciplina-semestre");
		}
	}
	
	public void removeAlunoDiscSemByAluno (Aluno aluno) throws DeleteException {
		try {
			removeAlunDiscSemByAluno.setInt(1, aluno.getIdAluno());
			removeAlunDiscSemByAluno.executeUpdate();
		} catch (Exception e) {
			throw new DeleteException("Erro ao deletar linha da tabela aluno-disciplina-semestre");
		}
	}
	
	public void removerAlunoDiscSemBySemestre (Semestre semestre) throws DeleteException {
		try {
			removeAlunDiscSemBySem.setInt(1, semestre.getIdSemestre());
			removeAlunDiscSemBySem.executeUpdate();
		} catch (Exception e) {
			throw new DeleteException("Erro ao deletar linha da tabela aluno-disciplina-semestre");
		}
	}
	
	//retorna um único aluno
	public Aluno select (int id_aluno) throws SelectException {
		Aluno aluno = null;
		
		try {
			select.setInt(1, id_aluno);
			ResultSet rs = select.executeQuery();
			
			if (rs.next()) {
				aluno = new Aluno();
				aluno.setIdAluno(rs.getInt("id"));
				aluno.setMatricula(rs.getInt("matricula"));
				aluno.setNomeAluno(rs.getString("nomealuno"));
			}
			return aluno;
		} catch (SQLException e) {
			throw new SelectException ("Não foi possível encontrar o aluno");
		}
	}
	
	//retorna vários alunos
	public List<Aluno> selectAll () throws SelectException {
		List<Aluno> alunos = new ArrayList<Aluno>();
		Aluno aluno = null;
		
		try {
			ResultSet rs = selectAll.executeQuery();
			while (rs.next()) {
				aluno = new Aluno();
				aluno.setIdAluno(rs.getInt("id"));
				aluno.setMatricula(rs.getInt("matricula"));
				aluno.setNomeAluno(rs.getString("nomealuno"));
				
				alunos.add(aluno);
				}
			return alunos;
			} catch (SQLException e) {
				throw new SelectException("Erro ao buscar pessoa");
			}
	}
	
	public void update (Aluno aluno) throws UpdateException {
		try {
			update.setInt(1, aluno.getMatricula());
			update.setString(2, aluno.getNomeAluno());
			update.setInt(3, aluno.getIdAluno());
			update.executeUpdate();
			
		} catch (SQLException e) {
			throw new UpdateException("Erro ao atualizar pessoa");
		}
	}
	
	//cadastra um aluno na tabela aluno-disciplina-semestre
	public void cadastrarAlunoEmDisciplinaSemestre (int id_aluno, int id_disciplina, int id_semestre) throws InsertException {
		try {
			insertAlunoDisciplina.setInt(1, id_aluno);
			insertAlunoDisciplina.setInt(2, id_disciplina);
			insertAlunoDisciplina.setInt(3, id_semestre);
			
			insertAlunoDisciplina.executeUpdate();
		} catch (SQLException e) {
			throw new InsertException("Erro ao cadastrar aluno em disciplina");
		}
	}
	
	public List<Semestre> selectSemestreByAluno (Aluno aluno) throws SelectException, ClassNotFoundException {
		List<Semestre> semestres = new ArrayList<Semestre>();
		Semestre semestre = null;
		SemestreDAO semestreDAO;
		
		try {
			selectSemestreByAluno.setInt(1, aluno.getIdAluno());
			ResultSet rs = selectSemestreByAluno.executeQuery();
			while (rs.next()) {
				semestre = new Semestre();
				semestre.setIdSemestre(rs.getInt("id_semestre"));
				
				Semestre temp = new Semestre();
				semestreDAO = SemestreDAO.getInstance();
				temp = semestreDAO.select(semestre.getIdSemestre());
				semestre.setNomeSemestre(temp.getNomeSemestre());
				
				semestres.add(semestre);
				}
			return semestres;
			} catch (SQLException e) {
				throw new SelectException("Erro ao buscar semestres do aluno");
			}
	}
	
	public List<Disciplina> selectDisciplinaBySemestre (Aluno aluno, Semestre semestre) throws SelectException, ClassNotFoundException {
		
		List<Disciplina> disciplinas = new ArrayList<Disciplina>();
		Disciplina disciplina = null;
		DisciplinaDAO disciplinaDAO;
		
		try {
			selectDisciplinaBySemestre.setInt(1, semestre.getIdSemestre());
			selectDisciplinaBySemestre.setInt(2, aluno.getIdAluno());
			ResultSet rs = selectSemestreByAluno.executeQuery();
			while (rs.next()) {
				disciplina = new Disciplina();
		
				disciplinaDAO = DisciplinaDAO.getInstance();
				disciplina = disciplinaDAO.select(disciplina.getIdDisciplina());//rs.getInt("id_disciplina")
				
				disciplinas.add(disciplina);
				}
			return disciplinas;
			} catch (SQLException e) {
				throw new SelectException("Erro ao buscar semestres do aluno");
			}
	}
	
}
