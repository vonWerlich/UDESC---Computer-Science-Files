package apresentacao;

import java.util.List;
import javax.swing.table.AbstractTableModel;
import dados.Estudante;
import negocio.Sistema;

@SuppressWarnings("serial")
public class TabelaEstudantes extends AbstractTableModel{

private static Sistema sistema;
	
	private String[] colunas = { "Matrícula", "Tipo de Curso", "Departamento"};

	public String getColumnName (int column) {
		return colunas[column];
	}
	
	public int getColumnCount () {
		return colunas.length;
	}
	
	public int getRowCount () {
		try {
			sistema = new Sistema("taianicakaka");
			int i = sistema.selectAllEstudantes().size();
			return i;
		} catch (Exception e) {
			e.getMessage();
		}
		return 0;
		
	}
	
	public Object getValueAt (int linha, int coluna) {
		try {
			sistema = new Sistema("taianicakaka");
			if (sistema.selectAllEstudantes()!=null) {
				List<Estudante> estudantes = sistema.selectAllEstudantes();
				switch (coluna) {
				case 0:
					return estudantes.get(linha).getMatricula();
				case 1:
					return estudantes.get(linha).getTipocurso();
				case 2:
					return estudantes.get(linha).getDepcurso();
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
