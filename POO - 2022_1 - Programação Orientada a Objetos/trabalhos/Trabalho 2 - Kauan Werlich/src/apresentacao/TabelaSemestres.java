package apresentacao;

import java.util.List;

import javax.swing.table.AbstractTableModel;

import dados.Disciplina;
import dados.Semestre;
import negocio.Sistema;

public class TabelaSemestres extends AbstractTableModel {

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
			int i = sistema.selectSemestres().size();
			return i;
		} catch (Exception e) {
			e.getMessage();
		}
		return 0;
		
	}
	
	public Object getValueAt (int linha, int coluna) {
		try {
			sistema = new Sistema("taianicakaka");
			if (sistema.selectSemestres()!=null) {
				List<Semestre> semestres = sistema.selectSemestres();
				switch (coluna) {
				case 0:
					return semestres.get(linha).getIdSemestre();
				case 1:
					return semestres.get(linha).getNomeSemestre();
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
