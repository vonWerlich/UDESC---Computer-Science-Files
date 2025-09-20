package dados;

public class Avaliacao {

	private int idAvaliacao;
	private String nomeAvaliacao;
	private String data;
	private double peso;
	private int idDisciplina;
	private int idSemestre;
	
	public int getIdSemestre() {
		return idSemestre;
	}
	public void setIdSemestre(int idSemestre) {
		this.idSemestre = idSemestre;
	}
	public int getIdAvaliacao() {
		return idAvaliacao;
	}
	public void setIdAvaliacao(int idAvaliacao) {
		this.idAvaliacao = idAvaliacao;
	}
	public String getNomeAvaliacao() {
		return nomeAvaliacao;
	}
	public void setNomeAvaliacao(String nomeAvaliacao) {
		this.nomeAvaliacao = nomeAvaliacao;
	}
	public String getData() {
		return data;
	}
	public void setData(String data) {
		this.data = data;
	}
	public double getPeso() {
		return peso;
	}
	public void setPeso(double peso) {
		this.peso = peso;
	}
	public int getIdDisciplina() {
		return idDisciplina;
	}
	public void setIdDisciplina(int idDisciplina) {
		this.idDisciplina = idDisciplina;
	}
	
	
}
