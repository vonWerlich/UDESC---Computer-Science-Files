package apresentacao;

import java.util.List;
import javax.swing.table.AbstractTableModel;

import dados.Departamento;
import negocio.Sistema;

@SuppressWarnings("serial")
public class TabelaDepartamentos extends AbstractTableModel {

private static Sistema sistema;
	
	private String[] colunas = { "Número", "Nome", "Escritório","Líder"};

	public String getColumnName (int column) {
		return colunas[column];
	}
	
	public int getColumnCount () {
		return colunas.length;
	}
	
	public int getRowCount () {
		try {
			sistema = new Sistema("taianicakaka");
			int i = sistema.selectAllDepartamentos().size();
			return i;
		} catch (Exception e) {
			e.getMessage();
		}
		return 0;
		
	}
	
	public Object getValueAt (int linha, int coluna) {
		try {
			sistema = new Sistema("taianicakaka");
			if (sistema.selectAllPessoas()!=null) {
				List<Departamento> dep = sistema.selectAllDepartamentos();
				switch (coluna) {
				case 0:
					return dep.get(linha).getNumdep();
				case 1:
					return dep.get(linha).getNomedep();
				case 2:
					return dep.get(linha).getEscritorioprincipal();
				case 3:
					return dep.get(linha).getProfessorlider();
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
