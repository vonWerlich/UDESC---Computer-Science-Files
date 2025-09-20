package negocio;

import dados.*;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;

import com.itextpdf.kernel.pdf.PdfDocument ;
import com.itextpdf.kernel.pdf.PdfWriter ;
import com.itextpdf.layout.Document;
import com.itextpdf.layout.element.Cell;
import com.itextpdf.layout.element.Paragraph;
import com.itextpdf.layout.element.Table;


public class Teste {
	private static Sistema sistema; 
	
	public static void main (String args[]) {
		
		try {
			sistema = new Sistema("taianicakaka");
			
		
			Aluno a1 = new Aluno();
			a1.setNomeAluno("João");
			a1.setMatricula(123);
			sistema.adicionarAluno(a1);
			
			Semestre s1 = new Semestre();
			s1.setNomeSemestre("Semestre 2022/1");
			sistema.adicionarSemestre(s1);
			
			Disciplina d1 = new Disciplina();
			d1.setNomeDisciplina("Programação Orientada a Objetos");
			sistema.adicionarDisciplina(d1);
			Disciplina d2 = new Disciplina();
			d2.setNomeDisciplina("Cálculo Diferencial e Integral 2");
			sistema.adicionarDisciplina(d2);
			
			Avaliacao ava1 = new Avaliacao();
			ava1.setData("01-06-2022");
			ava1.setNomeAvaliacao("Avaliação 1");
			ava1.setPeso(1.0);
			ava1.setIdDisciplina(1);
			ava1.setIdSemestre(1);
			sistema.adicionarAvaliacao(ava1);
			
			Avaliacao ava2 = new Avaliacao();
			ava2.setData("03-06-2022");
			ava2.setNomeAvaliacao("Avaliação 2");
			ava2.setPeso(1);
			ava2.setIdDisciplina(2);
			ava2.setIdSemestre(1);
			sistema.adicionarAvaliacao(ava2);
			
			Avaliacao ava3 = new Avaliacao();
			ava3.setData("01-06-2022");
			ava3.setNomeAvaliacao("Avaliação 3");
			ava3.setPeso(1);
			ava3.setIdDisciplina(2);
			ava3.setIdSemestre(1);
			sistema.adicionarAvaliacao(ava3);
			
			Aluno a2 = new Aluno();
			a2.setNomeAluno("Maria");
			a2.setMatricula(124);
			sistema.adicionarAluno(a2);
			
			Semestre s2 = new Semestre();
			s2.setNomeSemestre("Semestre 2021/1");
			sistema.adicionarSemestre(s2);
			
			Disciplina d3 = new Disciplina();
			d3.setNomeDisciplina("Programação Orientada a Objetos");
			sistema.adicionarDisciplina(d3);
			
			
			sistema.cadastrarDisciplinaSemestre(d1, s1);
			sistema.cadastrarDisciplinaSemestre(d2, s1);
			sistema.cadastrarDisciplinaSemestre(d3, s2);
			
			sistema.cadastrarDisciplinaSemestre(d3, s2);
			sistema.cadastrarAlunoEmDisciplinaSemestre(a1.getIdAluno(), d1.getIdDisciplina(), s1.getIdSemestre());
			sistema.cadastrarAlunoEmDisciplinaSemestre(a1.getIdAluno(), d2.getIdDisciplina(), s1.getIdSemestre());
			sistema.cadastrarAlunoEmDisciplinaSemestre(a2.getIdAluno(), d2.getIdDisciplina(), s1.getIdSemestre());
		
			sistema.inserirNota(a1.getIdAluno(), ava1.getIdAvaliacao(), 10.0);
			sistema.inserirNota(a1.getIdAluno(), ava2.getIdAvaliacao(), 8.0);
			sistema.inserirNota(a1.getIdAluno(), ava3.getIdAvaliacao(), 9.0);
			
			try {
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
								System.out.println("cheguei");
								
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
				}

		} catch (Exception e) {
			e.getMessage();
		}
	}
}
