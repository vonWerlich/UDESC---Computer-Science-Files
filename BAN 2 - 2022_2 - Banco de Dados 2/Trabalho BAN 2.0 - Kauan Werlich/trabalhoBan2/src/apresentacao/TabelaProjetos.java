package apresentacao;

import java.util.List;
import javax.swing.table.AbstractTableModel;
import dados.Projeto;
import negocio.Sistema;

@SuppressWarnings("serial")
public class TabelaProjetos extends AbstractTableModel {

private static Sistema sistema;
	
	private String[] colunas = { "Número", "Financiador", "Início","Término","Orçamento","Líder"};

	public String getColumnName (int column) {
		return colunas[column];
	}
	
	public int getColumnCount () {
		return colunas.length;
	}
	
	public int getRowCount () {
		try {
			sistema = new Sistema("taianicakaka");
			int i = sistema.selectAllProjetos().size();
			return i;
		} catch (Exception e) {
			e.getMessage();
		}
		return 0;
		
	}
	
	public Object getValueAt (int linha, int coluna) {
		try {
			sistema = new Sistema("taianicakaka");
			if (sistema.selectAllProjetos()!=null) {
				List<Projeto> projetos = sistema.selectAllProjetos();
				switch (coluna) {
				case 0:
					return projetos.get(linha).getNumprojeto();
				case 1:
					return projetos.get(linha).getOrgaofinanciador();
				case 2:
					return projetos.get(linha).getDatainicio();
				case 3:
					return projetos.get(linha).getDatatermino();
				case 4:
					return projetos.get(linha).getOrcamento();
				case 5:
					return projetos.get(linha).getPesquisadorprinc();
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
