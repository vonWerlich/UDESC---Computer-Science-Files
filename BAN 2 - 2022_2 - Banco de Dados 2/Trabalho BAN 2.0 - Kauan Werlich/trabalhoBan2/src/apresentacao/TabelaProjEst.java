package apresentacao;

import java.util.List;

import javax.swing.table.AbstractTableModel;

import dados.ProjetoEstudante;
import negocio.Sistema;

@SuppressWarnings("serial")
public class TabelaProjEst extends AbstractTableModel {

private static Sistema sistema;
	
	private String[] colunas = { "Projeto", "Estudante", "Supervisor"};

	public String getColumnName (int column) {
		return colunas[column];
	}
	
	public int getColumnCount () {
		return colunas.length;
	}
	
	public int getRowCount () {
		try {
			sistema = new Sistema("taianicakaka");
			int i = sistema.selectAllProjEstudantes().size();
			return i;
		} catch (Exception e) {
			e.getMessage();
		}
		return 0;
		
	}
	
	public Object getValueAt (int linha, int coluna) {
		try {
			sistema = new Sistema("taianicakaka");
			if (sistema.selectAllProjEstudantes()!=null) {
				List<ProjetoEstudante> estudantes = sistema.selectAllProjEstudantes();
				switch (coluna) {
				case 0:
					return estudantes.get(linha).getNumprojeto();
				case 1:
					return estudantes.get(linha).getEstudante();
				case 2:
					return estudantes.get(linha).getSupervisor();
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
