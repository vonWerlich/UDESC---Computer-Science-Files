package dados;

public class Estudante{

	private int matricula;
	private String tipocurso;
	private int depcurso;
	
	public int getMatricula() {
		return matricula;
	}
	public void setMatricula(int matricula) {
		this.matricula = matricula;
	}
	public String getTipocurso() {
		return tipocurso;
	}
	public void setTipocurso(String tipocurso) {
		this.tipocurso = tipocurso;
	}
	public int getDepcurso() {
		return depcurso;
	}
	public void setDepcurso(int depcurso) {
		this.depcurso = depcurso;
	}
	
	public String toString() {  
	    return Integer.toString(this.getMatricula());
	}  
	
}
