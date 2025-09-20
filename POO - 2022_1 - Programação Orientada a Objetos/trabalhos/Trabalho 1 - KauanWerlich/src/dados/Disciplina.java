package dados;

import java.util.ArrayList;
import java.util.List;

public class Disciplina {
	
	private String nomeDisciplina;
	private List<Avaliacao> listaAvaliacoes = new ArrayList<Avaliacao>();
	
	public String getNomeDisciplina() {
		return nomeDisciplina;
	}
	public void setNomeDisciplina(String nomeDisciplina) {
		this.nomeDisciplina = nomeDisciplina;
	}
	public List<Avaliacao> getListaAvaliacoes() {
		return listaAvaliacoes;
	}
	public void setListaAvaliacoes(List<Avaliacao> listaAvaliacoes) {
		this.listaAvaliacoes = listaAvaliacoes;
	}

	
}
