package dados;

import java.util.ArrayList;
import java.util.List;

public class Aluno {

	private String nomeAluno;
	private int matricula;
	private List<Semestre> listaSemestres = new ArrayList<Semestre>();
	
	public String getNomeAluno() {
		return nomeAluno;
	}
	public List<Semestre> getListaSemestres() {
		return listaSemestres;
	}
	public void setListaSemestres(List<Semestre> listaSemestres) {
		this.listaSemestres = listaSemestres;
	}
	public void setNomeAluno(String nomeAluno) {
		this.nomeAluno = nomeAluno;
	}
	public int getMatricula() {
		return matricula;
	}
	public void setMatricula(int matricula) {
		this.matricula = matricula;
	}
	
	
	
}
