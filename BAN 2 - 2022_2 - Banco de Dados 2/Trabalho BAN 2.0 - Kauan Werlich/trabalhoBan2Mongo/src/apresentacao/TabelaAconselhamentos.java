package apresentacao;

import java.util.List;

import javax.swing.table.AbstractTableModel;

import dados.Aconselhamento;
import negocio.Sistema;

@SuppressWarnings("serial")
public class TabelaAconselhamentos extends AbstractTableModel {

private static Sistema sistema;
	
	private String[] colunas = { "Aconselhado","Aconselhador"};

	public String getColumnName (int column) {
		return colunas[column];
	}
	
	public int getColumnCount () {
		return colunas.length;
	}
	
	public int getRowCount () {
		try {
			sistema = new Sistema("taianicakaka");
			int i = sistema.selectAllAconselhamentos().size();
			return i;
		} catch (Exception e) {
			e.getMessage();
		}
		return 0;
		
	}
	
	public Object getValueAt (int linha, int coluna) {
		try {
			sistema = new Sistema("taianicakaka");
			if (sistema.selectAllAconselhamentos()!=null) {
				List<Aconselhamento> aconselhamentos = sistema.selectAllAconselhamentos();
				switch (coluna) {
				case 0:
					return aconselhamentos.get(linha).getAconselhado();
				case 1:
					return aconselhamentos.get(linha).getAconselhador();

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
