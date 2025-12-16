package apresentacao;

import java.util.List;

import javax.swing.table.AbstractTableModel;

import dados.ProjetoProfessor;
import negocio.Sistema;

@SuppressWarnings("serial")
public class TabelaProjProf extends AbstractTableModel {

private static Sistema sistema;
	
	private String[] colunas = { "Projeto","Professor"};

	public String getColumnName (int column) {
		return colunas[column];
	}
	
	public int getColumnCount () {
		return colunas.length;
	}
	
	public int getRowCount () {
		try {
			sistema = new Sistema("taianicakaka");
			int i = sistema.selectAllProjProfessores().size();
			return i;
		} catch (Exception e) {
			e.getMessage();
		}
		return 0;
		
	}
	
	public Object getValueAt (int linha, int coluna) {
		try {
			sistema = new Sistema("taianicakaka");
			if (sistema.selectAllProjProfessores()!=null) {
				List<ProjetoProfessor> estudantes = sistema.selectAllProjProfessores();
				switch (coluna) {
				case 0:
					return estudantes.get(linha).getNumprojeto();
				case 1:
					return estudantes.get(linha).getProfessor();
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
