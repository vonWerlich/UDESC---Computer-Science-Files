package apresentacao;

import java.util.List;
import javax.swing.table.AbstractTableModel;
import dados.Professor;
import negocio.Sistema;

@SuppressWarnings("serial")
public class TabelaProfessores extends AbstractTableModel{

private static Sistema sistema;
	
	private String[] colunas = { "Matrícula","Especialidade","Sala"};

	public String getColumnName (int column) {
		return colunas[column];
	}
	
	public int getColumnCount () {
		return colunas.length;
	}
	
	public int getRowCount () {
		try {
			sistema = new Sistema("taianicakaka");
			int i = sistema.selectAllProfessores().size();
			return i;
		} catch (Exception e) {
			e.getMessage();
		}
		return 0;
		
	}
	
	public Object getValueAt (int linha, int coluna) {
		try {
			sistema = new Sistema("taianicakaka");
			if (sistema.selectAllProfessores()!=null) {
				List<Professor> professsores = sistema.selectAllProfessores();
				switch (coluna) {
				case 0:
					return professsores.get(linha).getMatricula();
				case 1:
					return professsores.get(linha).getEspecialidade();
				case 2:
					return professsores.get(linha).getSala();
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
