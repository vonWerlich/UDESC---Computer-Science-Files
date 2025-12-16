package negocio;

import java.sql.SQLException;
import java.util.List;

import dados.*;
import exceptions.*;
import persistencia.*;

public class Sistema {

	private AconselhamentoDAO aconselhamentoDAO;
	private DepartamentoDAO departamentoDAO;
	private EstudanteDAO estudanteDAO;
	private PessoaDAO pessoaDAO;
	private ProfessorDAO professorDAO;
	private ProfessordepartamentoDAO professordepartamentoDAO;
	private ProjetoDAO projetoDAO;
	private ProjetoestudanteDAO projetoestudanteDAO;
	private ProjetoprofessorDAO projetoprofessorDAO;
	
	public Sistema (String senha) throws SQLException, ClassNotFoundException {
		Conexao.setSenha(senha);
		aconselhamentoDAO = AconselhamentoDAO.getInstance();
		departamentoDAO = DepartamentoDAO.getInstance();
		estudanteDAO = EstudanteDAO.getInstance();
		pessoaDAO = PessoaDAO.getInstance();
		professorDAO = ProfessorDAO.getInstance();
		professordepartamentoDAO = ProfessordepartamentoDAO.getInstance();
		projetoDAO = ProjetoDAO.getInstance();
		projetoestudanteDAO = ProjetoestudanteDAO.getInstance();
		projetoprofessorDAO = ProjetoprofessorDAO.getInstance();
	}
	
	//ADICIONAR
	public void adicionarDepartamento (Departamento dep) throws InsertException, SelectException {
		departamentoDAO.insert(dep);
	}
	
	public void adicionarPessoa (Pessoa pessoa) throws InsertException, SelectException {
		pessoaDAO.insert(pessoa);
	}
	
	public void adicionarEstudante (Estudante estudante) throws InsertException, SelectException {
		estudanteDAO.insert(estudante);
	}
	
	public void adicionarProfessor (Professor professor) throws InsertException, SelectException {
		professorDAO.insert(professor);
	}
	
	public void adicionarProjeto (Projeto projeto) throws InsertException, SelectException {
		projetoDAO.insert(projeto);
	}
	
	public void adicionarAconselhamento (int aconselhado, int aconselhador) throws InsertException, SelectException {
		aconselhamentoDAO.insertAconselhamento(aconselhado, aconselhador);
	}
	
	public void adicionarProfDepartamento (int matricula, int numdep, double porcentagem) throws InsertException, SelectException {
		professordepartamentoDAO.insert(matricula, numdep, porcentagem);
	}
	
	public void adicionarProjEstudante (int numprojeto, int estudante, int supervisor) throws InsertException, SelectException {
		projetoestudanteDAO.insert(numprojeto, estudante, supervisor);
	}
	
	public void adicionarProjProfessor (int numprojeto, int professor) throws InsertException, SelectException {
		projetoprofessorDAO.insertProjProf(numprojeto, professor);
	}
	
	//DELETAR 
	
	public void removerAconselhamentoByAconselhado (int mat1) throws DeleteException {
		aconselhamentoDAO.removeAconselhamentoByMat1(mat1);
	}
	
	public void removerAconselhamentoByAconselhador (int mat2) throws DeleteException {
		aconselhamentoDAO.removeAconselhamentoByMat2(mat2);
	}
	
	public void removerAconselhamentoByAll (int mat1, int mat2) throws DeleteException {
		aconselhamentoDAO.removeAconselhamentoByMat1eMat2(mat1, mat2);
	}
	
	public void removerDepartamentoByNumDep (int numdep) throws DeleteException {
		departamentoDAO.delete(numdep);
	}
	
	public void removerEstudanteByMat (int matricula) throws DeleteException {
		estudanteDAO.delete(matricula);
	}
	
	public void removerPessoaByMat (int matricula) throws DeleteException {
		pessoaDAO.delete(matricula);
	}
	
	public void removerProfessorByMat (int matricula) throws DeleteException {
		professorDAO.delete(matricula);
	}
	
	public void removerProfessorDepartamentoByMat (int matricula) throws DeleteException {
		professordepartamentoDAO.deleteByMat(matricula);
	}
	
	public void removerProfessorDepartamentoByNumDep (int numdep) throws DeleteException {
		professordepartamentoDAO.deleteByNumDep(numdep);
	}
	
	public void removerProfessorDepartamentoByAll (int matricula, int numdep) throws DeleteException {
		professordepartamentoDAO.deleteByAll(matricula, numdep);
	}
	
	public void removerProjetoByNumProj (int numprojeto) throws DeleteException {
		projetoDAO.delete(numprojeto);
	}
	
	public void removerProjetoEstudanteByAll (int numprojeto, int estudante) throws DeleteException {
		projetoestudanteDAO.delete(numprojeto, estudante);
	}
	
	public void removerProjetoProfessorByProfessor (int professor) throws DeleteException {
		projetoprofessorDAO.removeProjProfByProf(professor);
	}
	
	public void removerProjetoProfessorByAll (int numprojeto, int professor) throws DeleteException {
		projetoprofessorDAO.removeProjProfByAll(numprojeto, professor);
	}
	
	//SELECT ALL
	public List<Pessoa> selectAllPessoas () throws SelectException {
		return pessoaDAO.selectAll();
	}
	
	public List<Estudante> selectAllEstudantes () throws SelectException {
		return estudanteDAO.selectAll();
	}
	
	public List<Professor> selectAllProfessores () throws SelectException {
		return professorDAO.selectAll();
	}
	
	public List<Projeto> selectAllProjetos () throws SelectException {
		return projetoDAO.selectAll();
	}
	
	public List<Aconselhamento> selectAllAconselhamentos () throws SelectException {
		return aconselhamentoDAO.selectAllAconselhamentos();
	}
	
	public List<ProjetoProfessor> selectAllProjProfessores () throws SelectException {
		return projetoprofessorDAO.selectAllProjProf();
	}
	
	public List<ProfessorDepartamento> selectAllProfDepartamento () throws SelectException {
		return professordepartamentoDAO.selectAllProfDep();
	}
	
	public List<ProjetoEstudante> selectAllProjEstudantes () throws SelectException {
		return projetoestudanteDAO.selectAllProjEst();
	}
	
	public List<Departamento> selectAllDepartamentos () throws SelectException {
		return departamentoDAO.selectAll();
	}
	

	//métodos extras
	
	public double porcentagemTempo (int matricula) throws SelectException {
		return professorDAO.porcentagemTempo(matricula);
	}
	
	
	// métodos toString
	
	public String pessoatoString (Pessoa pessoa) {
		return pessoaDAO.toString(pessoa);
	}
}
