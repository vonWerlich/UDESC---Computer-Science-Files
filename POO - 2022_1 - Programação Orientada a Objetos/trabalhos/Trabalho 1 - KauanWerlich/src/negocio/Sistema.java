package negocio;

import dados.*;
import java.util.ArrayList;
import java.util.List;

public class Sistema {

	private List<Aluno> listaAlunos = new ArrayList<Aluno>();
	
	public void adicionarAluno (Aluno aluno) {
		listaAlunos.add(aluno);
	}
	
	public List<Aluno> mostrarAlunos () {
		return listaAlunos;
	}
	
	public void adicionarSemestre (Aluno aluno, Semestre semestre) {
		List<Semestre> listatemp = aluno.getListaSemestres();
		listatemp.add(semestre);
		aluno.setListaSemestres(listatemp);
	}
	
	public void removerSemestre (Aluno aluno, Semestre semestre) {
		List<Semestre> listatemp = aluno.getListaSemestres();
		listatemp.remove(semestre);
		aluno.setListaSemestres(listatemp);
	}
	
	public void adicionarDisciplina (Semestre semestre, Disciplina disciplina) {
		List<Disciplina> listatemp = semestre.getListaDisciplinas();
		listatemp.add(disciplina);
		semestre.setListaDisciplinas(listatemp);
	}
	
	public void removerDisciplina (Semestre semestre, Disciplina disciplina) {
		List<Disciplina> listatemp = semestre.getListaDisciplinas();
		listatemp.remove(disciplina);
		semestre.setListaDisciplinas(listatemp);
	}
	
	public void adicionarAvaliacao (Disciplina disciplina, Avaliacao avaliacao) {
		List<Avaliacao> listatemp = disciplina.getListaAvaliacoes();
		listatemp.add(avaliacao);
		disciplina.setListaAvaliacoes(listatemp);
	}
	
	public void removerAvaliacao (Disciplina disciplina, Avaliacao avaliacao) {
		List<Avaliacao> listatemp = disciplina.getListaAvaliacoes();
		listatemp.remove(avaliacao);
		disciplina.setListaAvaliacoes(listatemp);
	}
	
	public void inserirNota (Avaliacao avaliacao, double nota) {
		avaliacao.setNota(nota);
	}
	
	public double calcularMediaFinal (Disciplina disciplina) {
		double media = 0.0;
		double peso = 0.0;
		List<Avaliacao> listatemp = disciplina.getListaAvaliacoes();
			for (Avaliacao ava : listatemp) {
				media += ava.getNota()*ava.getPeso();
				peso += ava.getPeso();
			}
		media = media/peso;
		
		if (peso==0) {
			return 0;
		} else {
			return media;
		}
	}
	
	public String calcularNotaExame (Semestre semestre) {
		String texto = "";
		List<Disciplina> listatemp = semestre.getListaDisciplinas();
		
		for (Disciplina dis : listatemp ) {
			if (calcularMediaFinal(dis)<1.7) {
				texto += dis.getNomeDisciplina() + ": Reprovado\n";
			}
			if (calcularMediaFinal(dis)>=7.0) {
				texto += dis.getNomeDisciplina() + ": Aprovado\n";
			}
			if ((calcularMediaFinal(dis)>=1.7)&&(calcularMediaFinal(dis)<7.0)) {
				double nota = 12.5 - (calcularMediaFinal(dis)*1.5);
				texto += dis.getNomeDisciplina() + ": Em Exame: necessário " + nota + " na prova do exame\n";
			}
		}
		return texto;
	}
}
