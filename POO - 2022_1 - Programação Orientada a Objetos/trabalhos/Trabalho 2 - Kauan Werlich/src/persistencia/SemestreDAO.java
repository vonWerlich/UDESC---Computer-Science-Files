package persistencia;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import dados.*;
import exceptions.*;

public class SemestreDAO {
	
	private static SemestreDAO instance = null;
	SemestreDAO semestreDAO;
	
	private PreparedStatement insert;
	private PreparedStatement delete;
	private PreparedStatement update;
	private PreparedStatement select;
	private PreparedStatement selectAll;
	private PreparedStatement selectNewId;
	
	private SemestreDAO () throws ClassNotFoundException, SQLException{
		
		Connection conexao = Conexao.getConexao();
		
		
		//consultas da tabela semestre
		insert = conexao.prepareStatement("insert into semestre values (?,?)");
		delete = conexao.prepareStatement("delete from semestre where id = ?");
		update = conexao.prepareStatement("update semestre set nomesemestre = ? where id = ?");
		select = conexao.prepareStatement("select * from semestre where id = ?");
		selectAll = conexao.prepareStatement("select * from semestre");
		selectNewId = conexao.prepareStatement("select nextval('id_semestre')");
		
	}
	
	public static SemestreDAO getInstance () throws ClassNotFoundException, SQLException {
		if (instance == null) {
			instance = new SemestreDAO();
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
			throw new SelectException("Erro ao buscar novo id da tabela semestre");
		}
	}
	
	public void insert (Semestre semestre) throws InsertException, SelectException {
		try {
			semestre.setIdSemestre(selectNewId());
			insert.setInt(1, semestre.getIdSemestre());
			insert.setString(2, semestre.getNomeSemestre());
			insert.executeUpdate();
			
		} catch (Exception e) {
			throw new InsertException("Erro ao inserir semestre");
		}
	}
	
	public void delete (Semestre semestre) throws DeleteException {
		
		try {
		
			delete.setInt(1, semestre.getIdSemestre());
			delete.executeUpdate();
			
		} catch (Exception e) {
			throw new DeleteException("Erro ao deletar semestre");
		}
	}
	
	//retorna um único semestre
	public Semestre select (int id_semestre) throws SelectException {
		Semestre semestre = null;
		
		try {
			select.setInt(1, id_semestre);
			ResultSet rs = select.executeQuery();
			
			if (rs.next()) {
				semestre = new Semestre();
				semestre.setIdSemestre(rs.getInt("id"));
				semestre.setNomeSemestre(rs.getString("nomesemestre"));
				
			}
			return semestre;
		} catch (SQLException e) {
			throw new SelectException ("Não foi possível encontrar o semestre");
		}
	}
	
	//retorna uma lista de semestres
	public List<Semestre> selectAll () throws SelectException {
		List<Semestre> semestres = new ArrayList<Semestre>();
		Semestre semestre = null;
		
		try {
			ResultSet rs = selectAll.executeQuery();
			while (rs.next()) {
				semestre = new Semestre();
				semestre.setIdSemestre(rs.getInt("id"));
				semestre.setNomeSemestre(rs.getString("nomesemestre"));
				
				semestres.add(semestre);
				}
			return semestres;
			} catch (SQLException e) {
				throw new SelectException("Erro ao buscar semestres");
			}
	}
	
	public void update (Semestre semestre) throws UpdateException {
		try {
			
			update.setString(1, semestre.getNomeSemestre());
			update.setInt(2, semestre.getIdSemestre());
			
		} catch (SQLException e) {
			throw new UpdateException("Erro ao atualizar semestre");
		}
	}
}
