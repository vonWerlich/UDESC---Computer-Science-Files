package persistencia;

import com.mongodb.connection.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
//import java.text.SimpleDateFormat;  
//import java.util.Date; 
//import java.util.Calendar;

import com.mongodb.MongoClient;

import dados.Projeto;
import exceptions.DeleteException;
import exceptions.InsertException;
import exceptions.SelectException;
import exceptions.UpdateException;

public class ProjetoDAO {

	private static ProjetoDAO instance = null;
	ProjetoDAO projetoDAO;
	
	private PreparedStatement insert;
	private PreparedStatement delete;
	private PreparedStatement update;
	private PreparedStatement select;
	private PreparedStatement selectAll;
	private PreparedStatement selectNewId;
	
	private ProjetoDAO () throws ClassNotFoundException, SQLException {
		
		try (Connection conexao = (Connection) new MongoClient("localhost", 27017)) {
			//consultas da tabela aluno
			insert = conexao.prepareStatement("insert into projeto values (?,?,?,?,?,?)");
			delete = conexao.prepareStatement("delete from projeto where numprojeto = ?");
			update = conexao.prepareStatement("update projeto set orgaofinanciador = ?, datainicio = ?,datatermino = ?, orcamento = ?, pesquisadorprinc = ? where numprojeto = ?");
			select = conexao.prepareStatement("select * from projeto where numprojeto = ?");
			selectAll = conexao.prepareStatement("select * from projeto");
			selectNewId = conexao.prepareStatement("select nextval('seqnumprojeto')");
		}
	}
	
	public static ProjetoDAO getInstance () throws ClassNotFoundException, SQLException {
		if (instance == null) {
			instance = new ProjetoDAO();
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
			throw new SelectException("Erro ao buscar novo número da tabela projeto");
		}
	}
	
	public void insert (Projeto projeto) throws InsertException, SelectException {
		try {
			//String strDate1 = projeto.getDatainicio();
			//String strDate2 = projeto.getDatatermino();
			
			//SimpleDateFormat sdf = new SimpleDateFormat("yyyy-mm-dd hh:mm:ss");
			//Date date1 = sdf.parse(strDate1); 
			//Date sqlDate1 = new Date(date1.getTime());
			
			//Date date2 = sdf.parse(strDate2); 
			//Date sqlDate2 = new Date(date2.getTime());
			//insert.setDate(3, (java.sql.Date) sqlDate1);
			//insert.setDate(4, (java.sql.Date) sqlDate2);
			
			
			projeto.setNumprojeto(selectNewId());
			insert.setInt(1, projeto.getNumprojeto());
			insert.setString(2, projeto.getOrgaofinanciador());
			insert.setString(3, projeto.getDatainicio());
			insert.setString(4, projeto.getDatatermino());
			insert.setDouble(5, projeto.getOrcamento());
			insert.setInt(6, projeto.getPesquisadorprinc());
			insert.executeUpdate();
		
		} catch (Exception e) {
			throw new InsertException("Erro ao inserir projeto");
		}
	}
	
	public void delete (int numprojeto) throws DeleteException {
		
		try {
			delete.setInt(1, numprojeto);
			delete.executeUpdate();
			
		} catch (Exception e) {
			throw new DeleteException("Erro ao deletar projeto");
		}
	}
	
	public void update (Projeto projeto) throws UpdateException {
		try {
			update.setInt(1, projeto.getNumprojeto());
			update.setString(2, projeto.getOrgaofinanciador());
			update.setString(3, projeto.getDatainicio());
			update.setString(4, projeto.getDatatermino());
			update.setDouble(5, projeto.getOrcamento());
			update.setInt(6, projeto.getPesquisadorprinc());
			update.executeUpdate();
			
		} catch (SQLException e) {
			throw new UpdateException("Erro ao atualizar projeto");
		}
	}
	
	//retorna um único projeto
	public Projeto select (int numprojeto) throws SelectException {
		Projeto projeto = null;
		
		try {
			select.setInt(1, numprojeto);
			ResultSet rs = select.executeQuery();
			
			if (rs.next()) {
				projeto = new Projeto();
				projeto.setNumprojeto(rs.getInt("numprojeto"));
				projeto.setOrgaofinanciador(rs.getString("orgaofinanciador"));
				projeto.setDatainicio(rs.getString("datainicio"));
				projeto.setDatatermino(rs.getString("datatermino"));
				projeto.setOrcamento(rs.getDouble("orcamento"));
				projeto.setPesquisadorprinc(rs.getInt("pesquisadorprinc"));
			}
			return projeto;
		} catch (SQLException e) {
			throw new SelectException ("Não foi possível encontrar o projeto");
		}
	}
	
	public List<Projeto> selectAll () throws SelectException {
		List<Projeto> projetos = new ArrayList<Projeto>();
		Projeto projeto = null;
		
		try {
			ResultSet rs = selectAll.executeQuery();
			while (rs.next()) {
				projeto = new Projeto();
				projeto.setNumprojeto(rs.getInt("numprojeto"));
				projeto.setOrgaofinanciador(rs.getString("orgaofinanciador"));
				projeto.setDatainicio(rs.getString("datainicio"));
				projeto.setDatatermino(rs.getString("datatermino"));
				projeto.setOrcamento(rs.getDouble("orcamento"));
				projeto.setPesquisadorprinc(rs.getInt("pesquisadorprinc"));
				
				projetos.add(projeto);
				}
			return projetos;
			} catch (SQLException e) {
				throw new SelectException("Erro ao buscar projeto");
			}
	}
}
