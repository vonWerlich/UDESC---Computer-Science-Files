package negocio;

import dados.*;
import java.io.FileNotFoundException;

import com.itextpdf.kernel.pdf.PdfDocument ;
import com.itextpdf.kernel.pdf.PdfWriter ;
import com.itextpdf.layout.Document;
import com.itextpdf.layout.element.Cell;
import com.itextpdf.layout.element.Paragraph;
import com.itextpdf.layout.element.Table;


public class Teste {
	private static Sistema sistema = new Sistema();
	
	public static void main (String args[]) {
		
		//declarando aluno 1
		Aluno a1 = new Aluno();
		a1.setNomeAluno("João");
		a1.setMatricula(123);
		sistema.adicionarAluno(a1);
		
		Semestre s1 = new Semestre();
		s1.setNomeSemestre("Semestre 2022/1");
		sistema.adicionarSemestre(a1, s1);
		
		Disciplina d1 = new Disciplina();
		d1.setNomeDisciplina("Programação Orientada a Objetos");
		sistema.adicionarDisciplina(s1, d1);
		Disciplina d2 = new Disciplina();
		d2.setNomeDisciplina("Cálculo Diferencial e Integral 2");
		sistema.adicionarDisciplina(s1, d2);
		
		Avaliacao ava1 = new Avaliacao();
		ava1.setData("01-06-2022");
		ava1.setNomeAvaliacao("Avaliação 1");
		ava1.setPeso(1);
		sistema.adicionarAvaliacao(d1, ava1);
		Avaliacao ava2 = new Avaliacao();
		ava2.setData("03-06-2022");
		ava2.setNomeAvaliacao("Avaliação 2");
		ava2.setPeso(1);
		sistema.adicionarAvaliacao(d1, ava2);
		
		Avaliacao ava3 = new Avaliacao();
		ava3.setData("01-06-2022");
		ava3.setNomeAvaliacao("Avaliação 1");
		ava3.setPeso(1);
		sistema.adicionarAvaliacao(d2, ava3);
		Avaliacao ava4 = new Avaliacao();
		ava4.setData("03-06-2022");
		ava4.setNomeAvaliacao("Avaliação 2");
		ava4.setPeso(2);
		sistema.adicionarAvaliacao(d2, ava4);
		
		sistema.inserirNota(ava1, 6.0);
		sistema.inserirNota(ava2, 8.0);
		sistema.inserirNota(ava3, 3.0);
		sistema.inserirNota(ava4, 6.0);
		
		//declarando aluno 2
		Aluno a2 = new Aluno();
		a2.setNomeAluno("Maria");
		a2.setMatricula(124);
		sistema.adicionarAluno(a2);
		
		Semestre s2 = new Semestre();
		s2.setNomeSemestre("Semestre 2021/1");
		sistema.adicionarSemestre(a2, s2);
		
		Disciplina d3 = new Disciplina();
		d3.setNomeDisciplina("Programação Orientada a Objetos");
		sistema.adicionarDisciplina(s2, d3);
		
		Avaliacao ava5 = new Avaliacao();
		ava5.setData("01-06-2022");
		ava5.setNomeAvaliacao("Avaliação 1");
		ava5.setPeso(1);
		sistema.adicionarAvaliacao(d3, ava5);
		Avaliacao ava6 = new Avaliacao();
		ava6.setData("03-06-2022");
		ava6.setNomeAvaliacao("Avaliação 2");
		ava6.setPeso(1);
		sistema.adicionarAvaliacao(d3, ava6);
		
		sistema.inserirNota(ava5, 7.0);
		sistema.inserirNota(ava6, 9.0);
		
		System.out.println("Nota necessária no exame do aluno 1:");
		System.out.println(sistema.calcularNotaExame(a1.getListaSemestres().get(0)));
		
		System.out.println("Nota necessária no exame do aluno 2:");
		System.out.println(sistema.calcularNotaExame(a2.getListaSemestres().get(0)));
		
		try {
			// Creating a PdfDocument object
			String dest = "RelatorioNotas.pdf";
			PdfWriter writer;
			writer = new PdfWriter (dest) ;
			// Creating a PdfDocument object
			PdfDocument pdf = new PdfDocument (writer) ;
			// Creating a Document object
			Document doc = new Document (pdf);
			for (Aluno a : sistema.mostrarAlunos()) {
			doc.add(new Paragraph("Aluno: " + a.getNomeAluno() + "     Matrícula: " + a.getMatricula()));
			doc.add(new Paragraph());
			
				for (Semestre s : a.getListaSemestres()) {
					doc.add(new Paragraph(s.getNomeSemestre()));
					float [ ] pointColumnWidths = { 220F, 220F} ;
					Table table = new Table ( pointColumnWidths );
					table.addCell (new Cell().add (new Paragraph ("Disciplina") ) ) ;
					table.addCell (new Cell().add (new Paragraph ("Média Final") ) ) ;
					for (Disciplina d : s.getListaDisciplinas()) {// Creating a table
						
						table.addCell (new Cell().add (new Paragraph (d.getNomeDisciplina()) ) ) ;
						table.addCell (new Cell().add (new Paragraph (Double.toString(sistema.calcularMediaFinal(d))) ) ) ;
						
					}
					doc.add (table);// Adding Table to document
					doc.add(new Paragraph());
				}
			}
			// Closing the document
			doc.close( ) ;
			System.out.println("Relatório criado com sucesso..");
			} catch ( FileNotFoundException e) {
			e.printStackTrace ();
			}

		
	}
}
