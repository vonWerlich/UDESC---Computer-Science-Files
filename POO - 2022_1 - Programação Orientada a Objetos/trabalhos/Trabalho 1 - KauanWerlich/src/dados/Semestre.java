package dados;

import java.util.ArrayList;
import java.util.List;

public class Semestre {
	
	private String nomeSemestre;
	private List<Disciplina> listaDisciplinas = new ArrayList<Disciplina>();
	
	public String getNomeSemestre() {
		return nomeSemestre;
	}
	public void setNomeSemestre(String nomeSemestre) {
		this.nomeSemestre = nomeSemestre;
	}
	public List<Disciplina> getListaDisciplinas() {
		return listaDisciplinas;
	}
	public void setListaDisciplinas(List<Disciplina> listaDisciplinas) {
		this.listaDisciplinas = listaDisciplinas;
	}

	
}
