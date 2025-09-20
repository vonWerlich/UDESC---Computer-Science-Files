package negocio;

import dados.*;
import exceptions.DeleteException;
import exceptions.InsertException;
import exceptions.SelectException;
import exceptions.UpdateException;
import persistencia.*;

import java.io.FileNotFoundException;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import com.itextpdf.kernel.pdf.PdfDocument;
import com.itextpdf.kernel.pdf.PdfWriter;
import com.itextpdf.layout.Document;
import com.itextpdf.layout.element.Cell;
import com.itextpdf.layout.element.Paragraph;
import com.itextpdf.layout.element.Table;

public class Sistema {

	private AlunoDAO alunoDAO;
	private AvaliacaoDAO avaliacaoDAO;
	private DisciplinaDAO disciplinaDAO;
	private SemestreDAO semestreDAO;
	private DisciplinaSemestreDAO disciplinaSemestreDAO;
	private static Sistema sistema; 
	
	public Sistema (String senha) throws SQLException, ClassNotFoundException {
		Conexao.setSenha(senha);
		alunoDAO = AlunoDAO.getInstance();
		avaliacaoDAO = AvaliacaoDAO.getInstance();
		disciplinaDAO = DisciplinaDAO.getInstance();
		semestreDAO = SemestreDAO.getInstance();
		disciplinaSemestreDAO = DisciplinaSemestreDAO.getInstance();
	}
	
	public void adicionarAluno (Aluno aluno) throws InsertException, SelectException {
		alunoDAO.insert(aluno);
	}
	
	public void adicionarAvaliacao (Avaliacao avaliacao) throws InsertException, SelectException {
		avaliacaoDAO.insert(avaliacao);
	}
	
	public void adicionarDisciplina (Disciplina disciplina) throws InsertException, SelectException {
		disciplinaDAO.insert(disciplina);
	}
	
	public void adicionarSemestre (Semestre semestre) throws InsertException, SelectException {
		semestreDAO.insert(semestre);
	}
	
	public void adicionarDiscSem (int id_semestre, int id_disciplina) throws SelectException, InsertException {
		Semestre semestre = semestreDAO.select(id_semestre);
		Disciplina disciplina = disciplinaDAO.select(id_disciplina);
		disciplinaSemestreDAO.insertDisciplinaSemestre(semestre, disciplina);
	}
	
	public void removerAluno (int id_aluno) throws DeleteException {
		alunoDAO.delete(id_aluno);
	}
	
	public void removerAvaliacao (int id_avaliacao) throws DeleteException, SelectException {
		Avaliacao avaliacao = new Avaliacao();
		avaliacao = avaliacaoDAO.select(id_avaliacao);	
		avaliacaoDAO.removeAvaliacaoByAvaliacao(avaliacao);//remove linha na tabela aluno-avaliacao

		avaliacaoDAO.delete(avaliacao);//remove a avaliacao
	}
	
	public void removerDisciplina (int id_disciplina) throws SelectException, SQLException, DeleteException {
		 Disciplina disciplina = disciplinaDAO.select(id_disciplina);
			alunoDAO.removeAlunoDiscSemByDisc(disciplina);//remove em alu-disc-sem
			List<Avaliacao> avas = avaliacaoDAO.selectAvasByDisciplina(disciplina);
			for (Avaliacao ava : avas) {
				avaliacaoDAO.removeAvaliacaoByAvaliacao(ava);//remove em aluno-avaliac
				avaliacaoDAO.delete(ava);//remove em avaliacoes
			}
			disciplinaSemestreDAO.removeDiscSemByDisciplina(disciplina);//remove em disc-semestre
			disciplinaDAO.delete(disciplina);

	}
	
	public void removerSemestre (int id_semestre) throws DeleteException, SelectException, SQLException {
		Semestre semestre = semestreDAO.select(id_semestre);
		alunoDAO.removerAlunoDiscSemBySemestre(semestre);
		avaliacaoDAO.removeAvasBySemestre(semestre);
		disciplinaSemestreDAO.removeDiscSemBySemestre(semestre);
		semestreDAO.delete(semestre);
	}
	
	public void removerSemestre (Aluno aluno, Semestre semestre) throws DeleteException {
		alunoDAO.removerAlunoDiscSemBySemestre(semestre);
		//avaliacaoDAO.
	}
	
	public void removeDiscSemByDiscESem (int id_sem, int id_disc) throws SelectException, SQLException, DeleteException {
		disciplinaSemestreDAO.removeDiscSemByDiscESem(id_sem, id_disc);
	}
	
	public void inserirNota (int id_aluno, int id_avaliacao, double nota) throws UpdateException {
		avaliacaoDAO.inserirNotaAluno(id_avaliacao, id_aluno, nota);
	}
	
	public double calcularMediaFinalDisciplina (Aluno aluno, Disciplina disciplina, Semestre semestre) throws SelectException {
		double media = 0.0;
		double peso = 0.0;
		List<Avaliacao> listatemp = avaliacaoDAO.selectByIds(disciplina.getIdDisciplina(), semestre.getIdSemestre());
			for (Avaliacao ava : listatemp) {
				int id_ava = ava.getIdAvaliacao();
				media += avaliacaoDAO.selectNotaAluno(id_ava, aluno.getIdAluno())*ava.getPeso();
				peso += ava.getPeso();
			}
		media = media/peso;
		
		if (peso==0) {
			return 0;
		} else {
			return media;
		}
	}
	
	//calcula as notas necessárias para o exame em cada semestre de um aluno
	public String calcularAllNotaExame (Aluno aluno) throws SelectException, ClassNotFoundException, SQLException {
		String texto = "";
		AlunoDAO alunoDAO = AlunoDAO.getInstance();
		List<Semestre> semestres = new ArrayList<Semestre>();
		
		semestres = alunoDAO.selectSemestreByAluno(aluno);
		for (Semestre sem : semestres) {
			List<Disciplina> disciplinas = new ArrayList<Disciplina>();
			disciplinas = alunoDAO.selectDisciplinaBySemestre(aluno, sem);
			
			
			
		}
		return texto;
	}
	
	public String notasdisciplinas (Disciplina dis, Aluno aluno, Semestre sem) throws SelectException {
		String texto = "";
		
				if (calcularMediaFinalDisciplina(aluno, dis, sem)<1.7) {
					texto += dis.getNomeDisciplina() + ": Reprovado\n";
				}
				if (calcularMediaFinalDisciplina(aluno, dis, sem)>=7.0) {
					texto += dis.getNomeDisciplina() + ": Aprovado\n";
				}
				if ((calcularMediaFinalDisciplina(aluno, dis, sem)>=1.7)&&(calcularMediaFinalDisciplina(aluno, dis, sem)<7.0)) {
					double nota = 12.5 - (calcularMediaFinalDisciplina(aluno, dis, sem)*1.5);
					texto += dis.getNomeDisciplina() + ": Em Exame: necessário " + nota + " na prova do exame\n";
				}

		return texto;
	}
	
	/*public String notasdisciplinas (List<Disciplina> disciplinas, Aluno aluno, Semestre sem) throws SelectException {
		String texto = "";
		for (Disciplina dis : disciplinas) {
				
				if (calcularMediaFinalDisciplina(aluno, dis, sem)<1.7) {
					texto += dis.getNomeDisciplina() + ": Reprovado\n";
				}
				if (calcularMediaFinalDisciplina(aluno, dis, sem)>=7.0) {
					texto += dis.getNomeDisciplina() + ": Aprovado\n";
				}
				if ((calcularMediaFinalDisciplina(aluno, dis, sem)>=1.7)&&(calcularMediaFinalDisciplina(aluno, dis, sem)<7.0)) {
					double nota = 12.5 - (calcularMediaFinalDisciplina(aluno, dis, sem)*1.5);
					texto += dis.getNomeDisciplina() + ": Em Exame: necessário " + nota + " na prova do exame\n";
				}
			}
		return texto;
	}*/
	
	public void cadastrarAlunoEmDisciplinaSemestre (int id_aluno, int id_disciplina, int id_semestre) throws InsertException {
		alunoDAO.cadastrarAlunoEmDisciplinaSemestre(id_aluno, id_disciplina, id_semestre);
	}
	
	public void cadastrarDisciplinaSemestre (Disciplina disciplina, Semestre semestre) throws InsertException {
		disciplinaSemestreDAO.insertDisciplinaSemestre(semestre, disciplina);
	}
	
	//public void removerAlunoDisciplina ()
	public void cadastrarAlunoAvaliacao (int id_aluno, int id_avaliacao, double nota) throws SQLException, InsertException {
		avaliacaoDAO.cadastrarAlunoEmAvaliacao(id_aluno, id_avaliacao, nota);
	}
	
	public List<Aluno> selectAlunos () throws SelectException {
		return alunoDAO.selectAll();
	}
	
	public List<Disciplina> selectDisciplinas () throws SelectException {
		return disciplinaDAO.selectAll();
	}
	
	public List<Semestre> selectSemestres () throws SelectException {
		return semestreDAO.selectAll();
	}
	
	public List<Avaliacao> selectAvaliacoes () throws SelectException {
		return avaliacaoDAO.selectAll();
	}
	
	public List<Semestre> selectSemestreByAluno (Aluno aluno) throws ClassNotFoundException, SelectException {
		return alunoDAO.selectSemestreByAluno(aluno);
	}
	
	public List<Disciplina> selectDisciplinaBySemestre (Aluno aluno, Semestre semestre) throws ClassNotFoundException, SelectException {
		return alunoDAO.selectDisciplinaBySemestre(aluno, semestre);
	}
	
	public String nomeDisciplina (Disciplina disciplina) {
		return disciplinaDAO.nomeDisciplina(disciplina);
	}
	
	public void removeAlunDiscSemByAluno (int id_aluno) throws DeleteException {
		Aluno temp = new Aluno();
		temp.setIdAluno(id_aluno);
		alunoDAO.removeAlunoDiscSemByAluno(temp);
	}
	
	public void removeAvaAlunByAluno (int id_aluno) throws DeleteException {
		Aluno temp = new Aluno();
		temp.setIdAluno(id_aluno);
		avaliacaoDAO.removeAvaliacaoByAluno(temp);
	}
	
	public void gerarRelatorio () {
		try {
			sistema = new Sistema("taianicakaka");
			// Creating a PdfDocument object
			String dest = "RelatorioNotas.pdf";
			PdfWriter writer;
			writer = new PdfWriter (dest) ;
			// Creating a PdfDocument object
			PdfDocument pdf = new PdfDocument (writer) ;
			// Creating a Document object
			Document doc = new Document (pdf);
			
			for (Aluno a : sistema.selectAlunos()) {
			doc.add(new Paragraph("Aluno: " + a.getNomeAluno() + "     Matrícula: " + a.getMatricula()));
			doc.add(new Paragraph());
			
			List<Semestre> semestres = new ArrayList<Semestre>();
			
			semestres = sistema.selectSemestreByAluno(a);
			
				for (Semestre s : semestres) {
					if (s!=null) {
						doc.add(new Paragraph(s.getNomeSemestre()));
						float [ ] pointColumnWidths = { 220F, 220F} ;
						Table table = new Table ( pointColumnWidths );
						table.addCell (new Cell().add (new Paragraph ("Disciplina") ) ) ;
						table.addCell (new Cell().add (new Paragraph ("Média Final") ) ) ;
						
						List<Disciplina> disciplinas = sistema.selectDisciplinaBySemestre(a, s);
						
						for (Disciplina d : disciplinas) {// Creating a table
							if (d!=null) {
								table.addCell (new Cell().add (new Paragraph (sistema.nomeDisciplina(d)) ) ) ;
								table.addCell (new Cell().add (new Paragraph (sistema.notasdisciplinas(d, a, s))) )  ;
							}
							
						}
						doc.add (table);// Adding Table to document
						doc.add(new Paragraph());
					}
				}
			}
			// Closing the document
			doc.close( );
			System.out.println("Relatório criado com sucesso..");
			} catch ( FileNotFoundException e) {
				e.printStackTrace ();
			} catch (Exception e) {
				e.getMessage();
			}
	}
}
