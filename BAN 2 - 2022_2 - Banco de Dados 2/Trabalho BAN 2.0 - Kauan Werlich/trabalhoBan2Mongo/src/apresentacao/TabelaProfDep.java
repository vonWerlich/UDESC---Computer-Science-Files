package apresentacao;

import java.util.List;
import javax.swing.table.AbstractTableModel;

import dados.ProfessorDepartamento;
import negocio.Sistema;

@SuppressWarnings("serial")
public class TabelaProfDep extends AbstractTableModel {

private static Sistema sistema;
	
	private String[] colunas = { "Matrícula", "Departamento", "Porcentagem"};

	public String getColumnName (int column) {
		return colunas[column];
	}
	
	public int getColumnCount () {
		return colunas.length;
	}
	
	public int getRowCount () {
		try {
			sistema = new Sistema("taianicakaka");
			int i = sistema.selectAllProfDepartamento().size();
			return i;
		} catch (Exception e) {
			e.getMessage();
		}
		return 0;
		
	}
	
	public Object getValueAt (int linha, int coluna) {
		try {
			sistema = new Sistema("taianicakaka");
			if (sistema.selectAllProfDepartamento()!=null) {
				List<ProfessorDepartamento> profdep = sistema.selectAllProfDepartamento();
				switch (coluna) {
				case 0:
					return profdep.get(linha).getMatricula();
				case 1:
					return profdep.get(linha).getNumdep();
				case 2:
					return profdep.get(linha).getPorcentagem();
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
