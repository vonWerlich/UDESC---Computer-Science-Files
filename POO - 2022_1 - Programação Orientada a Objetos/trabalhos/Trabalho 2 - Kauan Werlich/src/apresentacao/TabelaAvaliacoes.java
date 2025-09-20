package apresentacao;

import java.util.List;
import javax.swing.table.AbstractTableModel;

import dados.Avaliacao;
import dados.Disciplina;
import negocio.Sistema;

public class TabelaAvaliacoes extends AbstractTableModel {

private static Sistema sistema;
	
	private String[] colunas = { "ID", "Nome", "Data", "Peso", "ID-Disciplina","ID-Semestre"};

	public String getColumnName (int column) {
		return colunas[column];
	}
	
	public int getColumnCount () {
		return colunas.length;
	}
	
	public int getRowCount () {
		try {
			sistema = new Sistema("taianicakaka");
			int i = sistema.selectAvaliacoes().size();
			return i;
		} catch (Exception e) {
			e.getMessage();
		}
		return 0;
		
	}
	
	public Object getValueAt (int linha, int coluna) {
		try {
			sistema = new Sistema("taianicakaka");
			if (sistema.selectAvaliacoes()!=null) {
				List<Avaliacao> avas = sistema.selectAvaliacoes();
				switch (coluna) {
				case 0:
					return avas.get(linha).getIdAvaliacao();
				case 1:
					return avas.get(linha).getNomeAvaliacao();
				case 2:
					return avas.get(linha).getData();
				case 3:
					return avas.get(linha).getPeso();
				case 4:
					return avas.get(linha).getIdDisciplina();
				case 5:
					return avas.get(linha).getIdSemestre();
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
