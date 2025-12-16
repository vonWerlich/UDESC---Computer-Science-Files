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

public class DepartamentoDAO {

	private static DepartamentoDAO instance = null;
	DepartamentoDAO departamentoDAO;
	
	private PreparedStatement insert;
	private PreparedStatement delete;
	private PreparedStatement update;
	private PreparedStatement select;
	private PreparedStatement selectAll;
	private PreparedStatement selectNewId;
	
	private DepartamentoDAO () throws ClassNotFoundException, SQLException {
		
		Connection conexao = Conexao.getConexao();
		
		//consultas da tabela aluno
		insert = conexao.prepareStatement("insert into departamento values (?,?,?,?)");
		delete = conexao.prepareStatement("delete from departamento where numdep = ?");
		update = conexao.prepareStatement("update departamento set nomedep = ?, escritorioprincipal = ?, professorlider = ? where numdep = ?");
		select = conexao.prepareStatement("select * from departamento where numdep = ?");
		selectAll = conexao.prepareStatement("select * from departamento");
		selectNewId = conexao.prepareStatement("select nextval('seqnumdep')");
	}
	
	public static DepartamentoDAO getInstance () throws ClassNotFoundException, SQLException {
		if (instance == null) {
			instance = new DepartamentoDAO();
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
	
	public void insert (Departamento dep) throws InsertException, SelectException {
		try {
			dep.setNumdep(selectNewId());
			insert.setInt(1, dep.getNumdep());
			insert.setString(2, dep.getNomedep());
			insert.setString(3,dep.getEscritorioprincipal());
			insert.setInt(4, dep.getProfessorlider());
			insert.executeUpdate();
		
		} catch (Exception e) {
			throw new InsertException("Erro ao inserir departamento");
		}
	}
	
	public void delete (int numdep) throws DeleteException {
		
		try {
			delete.setInt(1, numdep);
			delete.executeUpdate();
			
		} catch (Exception e) {
			throw new DeleteException("Erro ao deletar departamento");
		}
	}
	
	public void update (Departamento dep) throws UpdateException {
		try {
			update.setString(1, dep.getNomedep());
			update.setString(2,dep.getEscritorioprincipal());
			update.setInt(3, dep.getProfessorlider());
			update.setInt(4, dep.getNumdep());
			update.executeUpdate();
			
		} catch (SQLException e) {
			throw new UpdateException("Erro ao atualizar departamento");
		}
	}
	
	//retorna um único departamento
	public Departamento select (int numdep) throws SelectException {
		Departamento dep = null;
		
		try {
			select.setInt(1, numdep);
			ResultSet rs = select.executeQuery();
			
			if (rs.next()) {
				dep = new Departamento();
				dep.setNumdep(rs.getInt("numdep"));
				dep.setNomedep(rs.getString("nomedep"));
				dep.setEscritorioprincipal(rs.getString("escritorioprincipal"));
				dep.setProfessorlider(rs.getInt("professorlider"));
			}
			return dep;
		} catch (SQLException e) {
			throw new SelectException ("Não foi possível encontrar o departamento");
		}
	}
	
	//retorna vários alunos
	public List<Departamento> selectAll () throws SelectException {
		List<Departamento> departamentos = new ArrayList<Departamento>();
		Departamento dep = null;
		
		try {
			ResultSet rs = selectAll.executeQuery();
			while (rs.next()) {
				dep = new Departamento();
				dep.setNumdep(rs.getInt("numdep"));
				dep.setNomedep(rs.getString("nomedep"));
				dep.setEscritorioprincipal(rs.getString("escritorioprincipal"));
				dep.setProfessorlider(rs.getInt("professorlider"));
				
				departamentos.add(dep);
				}
			return departamentos;
			} catch (SQLException e) {
				throw new SelectException("Erro ao buscar departamentos");
			}
	}
	
}
