package apresentacao;

import java.sql.SQLException;
import java.util.List;

import javax.swing.table.AbstractTableModel;

import dados.Aluno;
import exceptions.SelectException;
import negocio.Sistema;
import persistencia.AlunoDAO;



public class TabelaAlunos extends AbstractTableModel {

	private static Sistema sistema;
	
	private String[] colunas = { "ID", "Matricula", "Nome"};

	public String getColumnName (int column) {
		return colunas[column];
	}
	
	public int getColumnCount () {
		return colunas.length;
	}
	
	public int getRowCount () {
		try {
			sistema = new Sistema("taianicakaka");
			int i = sistema.selectAlunos().size();
			return i;
		} catch (Exception e) {
			e.getMessage();
		}
		return 0;
		
	}
	
	public Object getValueAt (int linha, int coluna) {
		try {
			sistema = new Sistema("taianicakaka");
			if (sistema.selectAlunos()!=null) {
				List<Aluno> alunos = sistema.selectAlunos();
				switch (coluna) {
				case 0:
					return alunos.get(linha).getIdAluno();
				case 1:
					return alunos.get(linha).getMatricula();
				case 2:
					return alunos.get(linha).getNomeAluno();
				}
			} else {
			return " - ";
			}
		} catch (Exception e) {
			e.getMessage();
		}
		
		return null;
	}
	
	public void atualizar () {
		fireTableStructureChanged();
	}
}
