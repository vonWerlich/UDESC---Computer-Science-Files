package persistencia;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import dados.Aconselhamento;
//import dados.*;
import exceptions.DeleteException;
import exceptions.InsertException;
import exceptions.SelectException;


public class AconselhamentoDAO {

	private static AconselhamentoDAO instance = null;

	private PreparedStatement insert;
	private PreparedStatement deleteByMat1eMat2;
	private PreparedStatement deleteByMat1;
	private PreparedStatement deleteByMat2;
	private PreparedStatement selectAll;
	
	private AconselhamentoDAO () throws ClassNotFoundException, SQLException {
		
		Connection conexao = Conexao.getConexao();
		
	//consultas da tabela disciplinasemestre
	insert = conexao.prepareStatement("insert into aconselhamento values (?,?)");
	deleteByMat1eMat2 = conexao.prepareStatement("delete from aconselhamento where matricula1 = ? and matricula2 = ?");
	deleteByMat1 = conexao.prepareStatement("delete from aconselhamento where matricula1 = ?");
	deleteByMat2 = conexao.prepareStatement("delete from aconselhamento where matricula2 = ?");
	selectAll = conexao.prepareStatement("select * from aconselhamento");

	}
	
	public static AconselhamentoDAO getInstance () throws ClassNotFoundException, SQLException {
		if (instance == null) {
			instance = new AconselhamentoDAO();
		}
		return instance;
	}
	
	public void insertAconselhamento (int matricula1, int matricula2) throws InsertException {
		try {
			insert.setInt(1, matricula1);
			insert.setInt(2, matricula2);
			insert.executeUpdate();
		
		} catch (Exception e) {
			throw new InsertException("Erro ao inserir estudantes na tabela aconselhamento");
		}
	}
	
	public void removeAconselhamentoByMat1eMat2 (int mat1, int mat2) throws DeleteException {
		try {
			deleteByMat1eMat2.setInt(1, mat1);
			deleteByMat1eMat2.setInt(2, mat2);
			deleteByMat1eMat2.executeUpdate();
		} catch (Exception e) {
			throw new DeleteException("Erro ao deletar linha da tabela disciplina-semestre");
		}
	}
	
	public void removeAconselhamentoByMat1 (int mat1) throws DeleteException {
		try {
			deleteByMat1.setInt(1, mat1);
			deleteByMat1.executeUpdate();
		} catch (Exception e) {
			throw new DeleteException("Erro ao deletar linha da aconselhamento a partir da matrícula 1");
		}
		
	}
	
	public void removeAconselhamentoByMat2 (int mat2) throws DeleteException {
		try {
			deleteByMat2.setInt(1, mat2);
			deleteByMat2.executeUpdate();
		} catch (Exception e) {
			throw new DeleteException("Erro ao deletar linha da aconselhamento a partir da matrícula 2");
		}
	}
	
	public List<Aconselhamento> selectAllAconselhamentos () throws SelectException {
		List<Aconselhamento> aconselhamentos = new ArrayList<Aconselhamento>();
		Aconselhamento acon = null;
		
		try {
			ResultSet rs = selectAll.executeQuery();
			while (rs.next()) {
				acon = new Aconselhamento();
				acon.setAconselhado(rs.getInt("matricula1"));
				acon.setAconselhador(rs.getInt("matricula2"));
				
				aconselhamentos.add(acon);
				}
			return aconselhamentos;
			} catch (SQLException e) {
				throw new SelectException("Erro ao buscar aconselhamentos");
			}
	}
	
}
