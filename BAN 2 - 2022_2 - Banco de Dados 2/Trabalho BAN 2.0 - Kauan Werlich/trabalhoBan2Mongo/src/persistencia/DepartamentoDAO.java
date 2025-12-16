package persistencia;

import com.mongodb.BasicDBObject;
import com.mongodb.DB;
import com.mongodb.DBCollection;
import com.mongodb.DBObject;
import com.mongodb.MongoClient;
import com.mongodb.connection.Connection;
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

		
		//consultas da tabela aluno
		MongoClient mongoClient = new MongoClient("localhost", 27017);
		DB db = mongoClient.getDB("universidade");
        DBCollection coll = db.getCollection("Departamento");
        DBObject data = new BasicDBObject();
        data.put("cpf", "3243248"); 
        data.put("nome", "Antonio"); 
        data.put("endereco", "Rua Otto Benack"); 
        coll.insert(data);
		
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
			
			MongoClient mongoClient = new MongoClient("localhost", 27017);
			DB db = mongoClient.getDB("universidade");
	        DBCollection coll = db.getCollection("Departamento");
	        DBObject data = new BasicDBObject();
	        data.put("numdep", dep.getNumdep()); 
	        data.put("nomedep", dep.getNomedep()); 
	        data.put("escritorioP", dep.getEscritorioprincipal()); 
	        data.put("professorL", dep.getProfessorlider()); 
	        coll.insert(data);
		
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
			MongoClient mongoClient = new MongoClient("localhost", 27017);
			DB db = mongoClient.getDB("universidade");
	        DBCollection coll = db.getCollection("Departamento");
	        DBObject data = new BasicDBObject();
	        
	        BasicDBObject query = new BasicDBObject("nome", "Fabiano");
	        DBCursor cursor = coll.find(query);
			try {
				 while(cursor.hasNext()) {
					 System.out.println(cursor.next());
				 }
			} finally {
				cursor.close();
			}

			ResultSet rs = db.universidade.find()
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
