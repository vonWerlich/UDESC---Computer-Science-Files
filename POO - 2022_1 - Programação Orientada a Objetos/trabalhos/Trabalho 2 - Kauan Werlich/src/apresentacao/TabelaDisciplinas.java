package apresentacao;

import java.util.List;

import javax.swing.table.AbstractTableModel;

import dados.Aluno;
import dados.Disciplina;
import negocio.Sistema;

public class TabelaDisciplinas extends AbstractTableModel  {

private static Sistema sistema;
	
	private String[] colunas = { "ID", "Nome"};

	public String getColumnName (int column) {
		return colunas[column];
	}
	
	public int getColumnCount () {
		return colunas.length;
	}
	
	public int getRowCount () {
		try {
			sistema = new Sistema("taianicakaka");
			int i = sistema.selectDisciplinas().size();
			return i;
		} catch (Exception e) {
			e.getMessage();
		}
		return 0;
		
	}
	
	public Object getValueAt (int linha, int coluna) {
		try {
			sistema = new Sistema("taianicakaka");
			if (sistema.selectDisciplinas()!=null) {
				List<Disciplina> disc = sistema.selectDisciplinas();
				switch (coluna) {
				case 0:
					return disc.get(linha).getIdDisciplina();
				case 1:
					return disc.get(linha).getNomeDisciplina();
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
