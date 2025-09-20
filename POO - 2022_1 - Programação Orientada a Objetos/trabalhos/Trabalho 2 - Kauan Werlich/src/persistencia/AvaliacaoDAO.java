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

public class AvaliacaoDAO {
	private static AvaliacaoDAO instance = null;
	AvaliacaoDAO avaliacaoDAO;
	
	private PreparedStatement insert;
	private PreparedStatement delete;
	private PreparedStatement update;
	private PreparedStatement select;
	private PreparedStatement selectAll;
	private PreparedStatement selectNewId;
	private PreparedStatement insertAlunoAvaliacao;
	private PreparedStatement removeAvaAlunByAvaliacao;
	private PreparedStatement removeAvaAlunByAluno;
	private PreparedStatement selectAlunByAvaliacao;
	private PreparedStatement selectAvaByAluno;
	private PreparedStatement inserirNotaParaAluno;
	private PreparedStatement selectByIds;
	private PreparedStatement selectNotaAluno;
	private PreparedStatement selectByIdDisciplina;
	private PreparedStatement removeAvasBySemestre;
	private PreparedStatement selectByIdSemestre;
	
	private AvaliacaoDAO () throws ClassNotFoundException, SQLException{
		
		Connection conexao = Conexao.getConexao();
		
		//consultas da tabela avaliacao
		insert = conexao.prepareStatement("insert into avaliacao values (?,?,?,?,?,?)");
		delete = conexao.prepareStatement("delete from avaliacao where id = ?");
		removeAvasBySemestre = conexao.prepareStatement("delete from avaliacao where id_semestre = ?");
		update = conexao.prepareStatement("update avaliacao set nomeavaliacao = ?, dataavaliacao = ?, peso = ? where id = ?");
		select = conexao.prepareStatement("select * from avaliacao where id = ?");
		selectAll = conexao.prepareStatement("select * from avaliacao");
		selectNewId = conexao.prepareStatement("select nextval('id_avaliacao')");
		selectByIdDisciplina = conexao.prepareStatement("select * from avaliacao where id_disciplina =?");
		selectByIdSemestre = conexao.prepareStatement("select * from avaliacao where id_semestre =?");
		selectByIds = conexao.prepareStatement("select * from avaliacao where id_disciplina = ? and id_semestre = ?");
		
		//consultas da tabela alunoavaliacao
		insertAlunoAvaliacao = conexao.prepareStatement("insert into alunoavaliacao values (?,?,?)");
		removeAvaAlunByAvaliacao = conexao.prepareStatement("delete from alunoavaliacao where id_avaliacao = ?");
		removeAvaAlunByAluno = conexao.prepareStatement("delete from alunoavaliacao where id_aluno = ?");
		selectAlunByAvaliacao = conexao.prepareStatement("select id_aluno from alunoavaliacao where id_avaliacao = ?");
		selectAvaByAluno = conexao.prepareStatement("select id_avaliacao from alunoavaliacao where id_aluno = ?");
		selectNotaAluno = conexao.prepareStatement("select nota from alunoavaliacao where id_aluno = ? and id_avaliacao = ?");
		inserirNotaParaAluno = conexao.prepareStatement("update alunoavaliacao set nota = ? where id_aluno = ? and id_avaliacao = ?");
	
	}
	
	public static AvaliacaoDAO getInstance () throws ClassNotFoundException, SQLException {
		if (instance == null) {
			instance = new AvaliacaoDAO();
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
			throw new SelectException("Erro ao buscar novo id da tabela avaliacao");
		}
	}
	
	public void insert (Avaliacao avaliacao) throws InsertException, SelectException {
		try {
			avaliacao.setIdAvaliacao(selectNewId());
			insert.setInt(1, avaliacao.getIdAvaliacao());
			insert.setString(2, avaliacao.getNomeAvaliacao());
			insert.setString(3, avaliacao.getData());
			insert.setDouble(4, avaliacao.getPeso());
			insert.setInt(5, avaliacao.getIdDisciplina());
			insert.setInt(6, avaliacao.getIdSemestre());
			insert.executeUpdate();
		
		} catch (Exception e) {
			throw new InsertException("Erro ao inserir avaliacao");
		}
	}
	
	public void delete (Avaliacao avaliacao) throws DeleteException {
		
		try {
			
			delete.setInt(1, avaliacao.getIdAvaliacao());
			delete.executeUpdate();
			
		} catch (Exception e) {
			throw new DeleteException("Erro ao deletar avaliacao");
		}
	}
	
	public Avaliacao select (int id_avaliacao) throws SelectException {
		Avaliacao avaliacao = null;
		
		try {
			select.setInt(1, id_avaliacao);
			ResultSet rs = select.executeQuery();
			
			if (rs.next()) {
				avaliacao = new Avaliacao();
				avaliacao.setIdAvaliacao(rs.getInt("id"));
				avaliacao.setNomeAvaliacao(rs.getString("nomeavaliacao"));
				avaliacao.setData(rs.getString("dataavaliacao"));
				avaliacao.setPeso(rs.getDouble("peso"));
				avaliacao.setIdDisciplina(rs.getInt("id_disciplina"));
				
			}
			return avaliacao;
		} catch (SQLException e) {
			throw new SelectException ("Não foi possível encontrar a pessoa");
		}
	}
	
	public List<Avaliacao> selectByIds (int id_disciplina, int id_semestre) throws SelectException {
		List<Avaliacao> avaliacoes = new ArrayList<Avaliacao>();
		Avaliacao avaliacao = null;
		
		try {
			selectByIds.setInt(1, id_disciplina);
			selectByIds.setInt(2, id_semestre);
			ResultSet rs = selectByIds.executeQuery();
			while (rs.next()) {
				avaliacao = new Avaliacao();
				avaliacao.setIdAvaliacao(rs.getInt("id"));
				avaliacao.setNomeAvaliacao(rs.getString("nomeavaliacao"));
				avaliacao.setData(rs.getString("dataavaliacao"));
				avaliacao.setPeso(rs.getDouble("peso"));
				avaliacao.setIdDisciplina(rs.getInt("id_disciplina"));
				avaliacao.setIdSemestre(rs.getInt("id_semestre"));
				
				avaliacoes.add(avaliacao);
				}
			return avaliacoes;
			} catch (SQLException e) {
				throw new SelectException("Erro ao buscar avaliacao");
			}
	}
	
	//retorna a lista de todas as avaliacoes
	public List<Avaliacao> selectAll () throws SelectException {
		List<Avaliacao> avaliacoes = new ArrayList<Avaliacao>();
		Avaliacao avaliacao = null;
		
		try {
			ResultSet rs = selectAll.executeQuery();
			while (rs.next()) {
				avaliacao = new Avaliacao();
				avaliacao.setIdAvaliacao(rs.getInt("id"));
				avaliacao.setNomeAvaliacao(rs.getString("nomeavaliacao"));
				avaliacao.setData(rs.getString("dataavaliacao"));
				avaliacao.setPeso(rs.getDouble("peso"));
				avaliacao.setIdDisciplina(rs.getInt("id_disciplina"));
				avaliacao.setIdSemestre(rs.getInt("id_semestre"));
				
				avaliacoes.add(avaliacao);
				}
			return avaliacoes;
			} catch (SQLException e) {
				throw new SelectException("Erro ao buscar avaliacao");
			}
	}
	
	public void update (Avaliacao avaliacao) throws UpdateException {
		try {
			
			update.setString(1, avaliacao.getNomeAvaliacao());
			update.setString(2, avaliacao.getData());
			update.setDouble(3, avaliacao.getPeso());
			update.setInt(4, avaliacao.getIdAvaliacao()); 
			update.executeUpdate();
			
		} catch (SQLException e) {
			throw new UpdateException("Erro ao atualizar pessoa");
		}
	}
	
	public void cadastrarAlunoEmAvaliacao (int id_aluno, int id_avaliacao, double nota) throws SQLException, InsertException {
		try {
			insertAlunoAvaliacao.setInt(1, id_aluno);
			insertAlunoAvaliacao.setInt(2, id_avaliacao);
			insertAlunoAvaliacao.setDouble(3, nota);
			insertAlunoAvaliacao.executeUpdate();
		} catch (SQLException e) {
			throw new InsertException("Erro ao cadastrar aluno em uma avaliação");
		}
		
	}
	
	//remove todas as tuplas aluno-avaliacao a partir de uma avaliacao que deve ser removida
	public void removeAvaliacaoByAvaliacao (Avaliacao avaliacao) throws DeleteException {
		
		try {
			removeAvaAlunByAvaliacao.setInt(1, avaliacao.getIdAvaliacao());
			removeAvaAlunByAvaliacao.executeUpdate();
		
			} catch (SQLException e) {
				throw new DeleteException("Erro ao deletar avaliações");
			}
	}
	
	//remove todas as tuplas aluno-avaliacao a partir de um aluno que deve ser removido
	public void removeAvaliacaoByAluno (Aluno aluno) throws DeleteException {
			
		try {
			removeAvaAlunByAluno.setInt(1, aluno.getIdAluno());
			removeAvaAlunByAluno.executeUpdate();
			
		} catch (SQLException e) {
			throw new DeleteException("Erro ao deletar avaliações");
		}
	}
	
	public List<Avaliacao> selectAvaByAluno (Aluno aluno) throws SelectException {
		List<Avaliacao> avaliacoes = new ArrayList<Avaliacao>();
		Avaliacao avaliacao = null;
		
		try {
			selectAvaByAluno.setInt(1, aluno.getIdAluno());
			ResultSet rs = selectAvaByAluno.executeQuery();
			while (rs.next()) {
				avaliacao = new Avaliacao();
				avaliacao.setIdAvaliacao(rs.getInt("id_avaliacao"));
				select.setInt(1, avaliacao.getIdAvaliacao());
				ResultSet rstemp = select.executeQuery();
				
				avaliacao.setNomeAvaliacao(rstemp.getString("nomeavaliacao"));
				avaliacao.setData(rstemp.getString("dataavaliacao"));
				avaliacao.setPeso(rstemp.getDouble("peso"));
				avaliacao.setIdDisciplina(rstemp.getInt("id_disciplina"));
				avaliacao.setIdSemestre(rstemp.getInt("id_semestre"));
				
				avaliacoes.add(avaliacao);
			}
			return avaliacoes;
			
		} catch (Exception e) {
			throw new SelectException("Erro ao selecionar avaliações a partir de um aluno");
		}
	}
	
	public List<Aluno> selectAlunoByAva (Avaliacao avaliacao) throws SelectException, ClassNotFoundException, SQLException {
		List<Aluno> alunos = new ArrayList<Aluno>();
		Aluno aluno = null;
		AlunoDAO alunoDAO = AlunoDAO.getInstance();
		
		try {
			selectAlunByAvaliacao.setInt(1, avaliacao.getIdAvaliacao());
			ResultSet rs = selectAlunByAvaliacao.executeQuery();
			while (rs.next()) {
				aluno = new Aluno();
				aluno.setIdAluno(rs.getInt("id_aluno"));
				Aluno temp = alunoDAO.select(aluno.getIdAluno());
				aluno.setMatricula(temp.getMatricula());
				aluno.setNomeAluno(temp.getNomeAluno());
				
				alunos.add(aluno);
			}
			return alunos;
		} catch (Exception e) {
			throw new SelectException("Erro ao selecionar alunos a partir de uma avaliação");
		}
	}
	
	public void inserirNotaAluno (int id_aluno, int id_avaliacao, double nota) throws UpdateException {
		
		try {
			inserirNotaParaAluno.setDouble(1, nota);
			inserirNotaParaAluno.setInt(2, id_aluno);
			inserirNotaParaAluno.setInt(3, id_avaliacao);
			inserirNotaParaAluno.executeUpdate();
		} catch (SQLException e) {
			throw new UpdateException("Erro ao cadastrar a nota para o aluno");
		}
		
	}
	
	public Double selectNotaAluno (int id_avaliacao, int id_aluno) throws SelectException {
		try {
			selectNotaAluno.setInt(1, id_aluno);
			selectNotaAluno.setInt(2, id_avaliacao);
			ResultSet rs = selectNotaAluno.executeQuery();
			if (rs!=null) {
				return rs.getDouble("nota");
			} else {
				return 0.0;
			}
		} catch (Exception e) {
			throw new SelectException("Erro ao buscar a nota do aluno");
		}
	}
	
	public List<Avaliacao> selectAvasByDisciplina (Disciplina disciplina) throws SelectException {
		List<Avaliacao> avaliacoes = new ArrayList<Avaliacao>();
		Avaliacao avaliacao = null;
		
		try {
			selectByIdDisciplina.setInt(1, disciplina.getIdDisciplina());
			ResultSet rs = selectByIdDisciplina.executeQuery();
			while (rs.next()) {
				avaliacao = new Avaliacao();
				avaliacao.setIdAvaliacao(rs.getInt("id"));
				avaliacao.setNomeAvaliacao(rs.getString("nomeavaliacao"));
				avaliacao.setData(rs.getString("dataavaliacao"));
				avaliacao.setPeso(rs.getDouble("peso"));
				avaliacao.setIdDisciplina(rs.getInt("id_disciplina"));
				avaliacao.setIdSemestre(rs.getInt("id_semestre"));
				
				avaliacoes.add(avaliacao);
			}
			return avaliacoes;
		} catch (Exception e) {
			throw new SelectException("Erro ao selecionar avaliacoes a partir de uma disciplina");
		}
	}
	
	public List<Avaliacao> selectAvasByIdSemestre (Semestre semestre) throws SelectException {
		List<Avaliacao> avaliacoes = new ArrayList<Avaliacao>();
		Avaliacao avaliacao = null;
		
		try {
			selectByIdSemestre.setInt(1, semestre.getIdSemestre());
			ResultSet rs = selectByIdSemestre.executeQuery();
			while (rs.next()) {
				avaliacao = new Avaliacao();
				avaliacao.setIdAvaliacao(rs.getInt("id"));
				avaliacao.setNomeAvaliacao(rs.getString("nomeavaliacao"));
				avaliacao.setData(rs.getString("dataavaliacao"));
				avaliacao.setPeso(rs.getDouble("peso"));
				avaliacao.setIdDisciplina(rs.getInt("id_disciplina"));
				avaliacao.setIdSemestre(rs.getInt("id_semestre"));
				
				avaliacoes.add(avaliacao);
			}
			return avaliacoes;
		} catch (Exception e) {
			throw new SelectException("Erro ao selecionar avaliacoes a partir de uma disciplina");
		}
	}
	
	public void removeAvasBySemestre (Semestre semestre) {
		try {
			removeAvasBySemestre.setInt(1, semestre.getIdSemestre());
			removeAvasBySemestre.executeUpdate();
		} catch (Exception e) {
			
		}
	}
}
