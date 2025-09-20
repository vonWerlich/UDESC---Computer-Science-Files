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

public class DisciplinaDAO {
	private static DisciplinaDAO instance = null;
	DisciplinaDAO disciplinaDAO;
	
	private PreparedStatement insert;
	private PreparedStatement delete;
	private PreparedStatement update;
	private PreparedStatement select;
	private PreparedStatement selectAll;
	private PreparedStatement selectNewId;
	
	private DisciplinaDAO () throws ClassNotFoundException, SQLException{
		
		Connection conexao = Conexao.getConexao();
		
		//consultas da tabela disciplina
		insert = conexao.prepareStatement("insert into disciplina values (?,?)");
		delete = conexao.prepareStatement("delete from disciplina where id = ?");
		update = conexao.prepareStatement("update disciplina set nomedisciplina = ? where id = ?");
		select = conexao.prepareStatement("select * from disciplina where id = ?");//retorna uma disciplina a partir de um id
		selectAll = conexao.prepareStatement("select * from disciplina");//retorna lista de disciplinas
		selectNewId = conexao.prepareStatement("select nextval('id_disciplina')");
	
	}
	
	public static DisciplinaDAO getInstance () throws ClassNotFoundException, SQLException {
		if (instance == null) {
			instance = new DisciplinaDAO();
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
			throw new SelectException("Erro ao buscar novo id da tabela pessoa");
		}
	}
	
	public void insert (Disciplina disciplina) throws InsertException, SelectException {
		try {
			disciplina.setIdDisciplina(selectNewId());
			insert.setInt(1, disciplina.getIdDisciplina());
			insert.setString(2, disciplina.getNomeDisciplina());
			insert.executeUpdate();
			
		} catch (Exception e) {
			throw new InsertException("Erro ao inserir pessoa");
		}
	}
	
	public void delete (Disciplina disciplina) throws DeleteException {
		try {
			delete.setInt(1, disciplina.getIdDisciplina());
			delete.executeUpdate();
			
		} catch (Exception e) {
			throw new DeleteException("Erro ao deletar pessoa");
		}
	}
	
	//retorna uma disciplina a partir do id
	public Disciplina select (int id_disciplina) throws SelectException {
		Disciplina disciplina = null;
		
		try {
			select.setInt(1, id_disciplina);
			ResultSet rs = select.executeQuery();
			
			if (rs.next()) {
				disciplina = new Disciplina();
				disciplina.setIdDisciplina(rs.getInt("id"));
				disciplina.setNomeDisciplina(rs.getString("nomedisciplina"));
				
			}
			return disciplina;
		} catch (SQLException e) {
			throw new SelectException ("Não foi possível encontrar a disciplina");
		}
	}
	
	//retorna uma lista com todas as disciplinas
	public List<Disciplina> selectAll () throws SelectException {
		List<Disciplina> disciplinas = new ArrayList<Disciplina>();
		Disciplina disciplina = null;
		
		try {
			ResultSet rs = selectAll.executeQuery();
			while (rs.next()) {
				disciplina = new Disciplina();
				disciplina.setIdDisciplina(rs.getInt("id"));
				disciplina.setNomeDisciplina(rs.getString("nomedisciplina"));
				
				disciplinas.add(disciplina);
				}
			return disciplinas;
			} catch (SQLException e) {
				throw new SelectException("Erro ao buscar disciplina");
			}
	}
	
	public void update (Disciplina disciplina) throws UpdateException {
		try {
			
			update.setString(1, disciplina.getNomeDisciplina());
			update.setInt(2, disciplina.getIdDisciplina());
			update.executeUpdate();
			
		} catch (SQLException e) {
			throw new UpdateException("Erro ao atualizar disciplina");
		}
	}
	
	public String nomeDisciplina (Disciplina disciplina) {
		return disciplina.getNomeDisciplina();
	}
}
