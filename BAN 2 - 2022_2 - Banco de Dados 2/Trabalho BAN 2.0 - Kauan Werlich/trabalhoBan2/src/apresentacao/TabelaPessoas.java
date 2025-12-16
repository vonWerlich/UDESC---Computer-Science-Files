package apresentacao;

import java.util.List;

import javax.swing.table.AbstractTableModel;

import dados.Pessoa;
import negocio.Sistema;

@SuppressWarnings("serial")
public class TabelaPessoas extends AbstractTableModel {

private static Sistema sistema;
	
	private String[] colunas = { "Matrícula", "Nome", "Idade"};

	public String getColumnName (int column) {
		return colunas[column];
	}
	
	public int getColumnCount () {
		return colunas.length;
	}
	
	public int getRowCount () {
		try {
			sistema = new Sistema("taianicakaka");
			int i = sistema.selectAllPessoas().size();
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
				List<Pessoa> pessoas = sistema.selectAllPessoas();
				switch (coluna) {
				case 0:
					return pessoas.get(linha).getMatricula();
				case 1:
					return pessoas.get(linha).getNome();
				case 2:
					return pessoas.get(linha).getIdade();
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
