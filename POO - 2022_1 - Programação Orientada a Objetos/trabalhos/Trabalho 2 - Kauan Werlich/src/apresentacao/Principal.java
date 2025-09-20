package apresentacao;

import java.awt.BorderLayout;
import java.awt.EventQueue;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.border.EmptyBorder;

import dados.*;
import negocio.Sistema;

public class Principal extends JFrame {
	
	private static Sistema sistema;

	private JPanel painel = new JPanel();
	private JScrollPane painelScrollTabelaAlunos = new JScrollPane();
	private JScrollPane painelScrollTabelaDisciplinas = new JScrollPane();
	private JScrollPane painelScrollTabelaSemestres = new JScrollPane();
	private JScrollPane painelScrollTabelaAvaliacoes = new JScrollPane();
	private JTable tabelaAlunos;
	private JTable tabelaDisciplinas;
	private JTable tabelaSemestres;
	private JTable tabelaAvaliacoes;
	private TabelaAlunos alunos = new TabelaAlunos();
	private TabelaDisciplinas disciplinas = new TabelaDisciplinas();
	private TabelaSemestres semestres = new TabelaSemestres();
	private TabelaAvaliacoes avaliacoes = new TabelaAvaliacoes();
	private JLabel infoCaixaTexto1 = new JLabel("Alunos:");
	private JLabel infoCaixaTexto2 = new JLabel("Disciplinas:");
	private JLabel infoCaixaTexto3 = new JLabel("Semestres:");
	private JLabel infoCaixaTexto4 = new JLabel("Avaliações:");
	
	private JTextField caixaTexto1 = new JTextField();
	private JTextField caixaTexto2 = new JTextField();
	
	private JButton botaoRelatorio = new JButton("Gerar Relatório");
	
	public static void main(String[] args) {
			
			EventQueue.invokeLater(new Runnable() {
				public void run() {
					try {
						Principal frame = new Principal();
						frame.setVisible(true);
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			});
		
			}
	
	public Principal() {
		setTitle("Sistema de Gestão de Notas");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(10,10,1300,700);
		setContentPane(painel);
		painel.setLayout(null);

		//tabela mostra alunos
		painelScrollTabelaAlunos.setBounds(10, 20,  600,  100);
		painel.add(painelScrollTabelaAlunos);
		
		tabelaAlunos = new JTable(alunos);
		painelScrollTabelaAlunos.setViewportView(tabelaAlunos);
		
		infoCaixaTexto1.setBounds(10, 5, 200, 15);
		painel.add(infoCaixaTexto1);
		
		//tabela mostra disciplinas
		painelScrollTabelaDisciplinas.setBounds(630, 20,  600,  100);
		painel.add(painelScrollTabelaDisciplinas);
		
		tabelaDisciplinas = new JTable(disciplinas);
		painelScrollTabelaDisciplinas.setViewportView(tabelaDisciplinas);
		
		infoCaixaTexto2.setBounds(630, 5, 200, 15);
		painel.add(infoCaixaTexto2);
		
		//tabela mostra semestres
		painelScrollTabelaSemestres.setBounds(630, 140,  600,  100);
		painel.add(painelScrollTabelaSemestres);
		
		tabelaSemestres = new JTable(semestres);
		painelScrollTabelaSemestres.setViewportView(tabelaSemestres);
		
		infoCaixaTexto3.setBounds(630, 120, 200, 15);
		painel.add(infoCaixaTexto3);
		
		//tabela mostra avaliacoes
		painelScrollTabelaAvaliacoes.setBounds(10, 140,  600,  100);
		painel.add(painelScrollTabelaAvaliacoes);
		
		tabelaAvaliacoes = new JTable(avaliacoes);
		painelScrollTabelaAvaliacoes.setViewportView(tabelaAvaliacoes);
		
		infoCaixaTexto4.setBounds(10, 120, 200, 15);
		painel.add(infoCaixaTexto4);
		
		//adicionar aluno
		caixaTexto1.setBounds(10, 270, 150, 20);
		painel.add(caixaTexto1);
		JLabel infoCaixaTexto5 = new JLabel("Insira a Matrícula:");
		infoCaixaTexto5.setBounds(10, 250, 150, 20);
		painel.add(infoCaixaTexto5);
		
		caixaTexto2.setBounds(170, 270, 150, 20);
		painel.add(caixaTexto2);
		JLabel infoCaixaTexto6 = new JLabel("Insira o nome:");
		infoCaixaTexto6.setBounds(170, 250, 150, 20);
		painel.add(infoCaixaTexto6);
		
		JButton botaoAluno = new JButton("Adicionar Aluno");
		botaoAluno.setBounds(330, 270, 150, 20);
		painel.add(botaoAluno);
		botaoAluno.addActionListener( new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				try {
					sistema = new Sistema("taianicakaka");
					Aluno temp = new Aluno();
					temp.setMatricula(Integer.parseInt(caixaTexto1.getText()));
					temp.setNomeAluno(caixaTexto2.getText());
					sistema.adicionarAluno(temp);
					alunos.atualizar();
					caixaTexto1.setText("");
					caixaTexto2.setText("");
				} catch (Exception e) {
					e.getMessage();
				}
			}
		});
		
		//Remover Aluno
		
		JTextField caixaTexto3 = new JTextField();
		caixaTexto3.setBounds(500, 270, 100, 20);
		painel.add(caixaTexto3);
		JLabel infoCaixaTexto7 = new JLabel("Insira o ID do aluno a ser removido:");
		infoCaixaTexto7.setBounds(500, 250, 200, 20);
		painel.add(infoCaixaTexto7);
		
		JButton botaoRemoveAluno = new JButton("Remover Aluno");
		botaoRemoveAluno.setBounds(610, 270, 150, 20);
		painel.add(botaoRemoveAluno);
		botaoRemoveAluno.addActionListener( new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				try {
					sistema = new Sistema("taianicakaka");
					int temp = Integer.parseInt(caixaTexto3.getText());
					sistema.removeAlunDiscSemByAluno(temp);
					sistema.removeAvaAlunByAluno(temp);
					sistema.removerAluno(temp);
					alunos.atualizar();
					caixaTexto3.setText("");
				} catch (Exception e) {
					e.getMessage();
				}
			}
		});
		
		//adicionar disciplina
		
		JTextField caixaTexto4 = new JTextField();
		caixaTexto4.setBounds(10, 310, 150, 20);
		painel.add(caixaTexto4);
		JLabel infoCaixaTexto9 = new JLabel("Insira o nome:");
		infoCaixaTexto9.setBounds(10, 290, 150, 20);
		painel.add(infoCaixaTexto9);
		
		JButton botaoDisciplina = new JButton("Adicionar Disciplina");
		botaoDisciplina.setBounds(170, 310, 150, 20);
		painel.add(botaoDisciplina);
		botaoDisciplina.addActionListener( new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				try {
					sistema = new Sistema("taianicakaka");
					Disciplina dis = new Disciplina();
					dis.setNomeDisciplina(caixaTexto4.getText());
					sistema.adicionarDisciplina(dis);
					disciplinas.atualizar();
					caixaTexto4.setText("");
				} catch (Exception e) {
					e.getMessage();
				}
			}
		});
		
		//remover disciplina
		
		JTextField caixaTexto5 = new JTextField();
		caixaTexto5.setBounds(330, 310, 100, 20);
		painel.add(caixaTexto5);
		JLabel infoCaixaTexto10 = new JLabel("Insira o ID da disciplina a ser removida:");
		infoCaixaTexto10.setBounds(330, 290, 250, 20);
		painel.add(infoCaixaTexto10);
		
		JButton botaoRemoveDisciplina = new JButton("Remover Disciplina");
		botaoRemoveDisciplina.setBounds(450, 310, 150, 20);
		painel.add(botaoRemoveDisciplina);
		botaoRemoveDisciplina.addActionListener( new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				try {
					sistema = new Sistema("taianicakaka");
					int temp = Integer.parseInt(caixaTexto5.getText());
					sistema.removerDisciplina(temp);
					disciplinas.atualizar();
					caixaTexto5.setText("");
				} catch (Exception e) {
					e.getMessage();
				}
			}
		});
		
		//adicionar avaliacoes
		
		JTextField caixaTexto6 = new JTextField();
		caixaTexto6.setBounds(10, 350, 100, 20);
		painel.add(caixaTexto6);
		JLabel infoCaixaTexto11 = new JLabel("Insira o nome:");
		infoCaixaTexto11.setBounds(10, 330, 150, 20);
		painel.add(infoCaixaTexto11);
		
		JTextField caixaTexto7 = new JTextField();
		caixaTexto7.setBounds(120, 350, 100, 20);
		painel.add(caixaTexto7);
		JLabel infoCaixaTexto12 = new JLabel("Insira a data:");
		infoCaixaTexto12.setBounds(120, 330, 150, 20);
		painel.add(infoCaixaTexto12);
		
		JTextField caixaTexto8 = new JTextField();
		caixaTexto8.setBounds(230, 350, 69, 20);
		painel.add(caixaTexto8);
		JLabel infoCaixaTexto13 = new JLabel("Insira o peso:");
		infoCaixaTexto13.setBounds(230, 330, 130, 20);
		painel.add(infoCaixaTexto13);
		
		JTextField caixaTexto9 = new JTextField();
		caixaTexto9.setBounds(310, 350, 120, 20);
		painel.add(caixaTexto9);
		JLabel infoCaixaTexto14 = new JLabel("Insira o ID da Disciplina:");
		infoCaixaTexto14.setBounds(310, 330, 150, 20);
		painel.add(infoCaixaTexto14);
		
		JTextField caixaTexto10 = new JTextField();
		caixaTexto10.setBounds(450, 350, 100, 20);
		painel.add(caixaTexto10);
		JLabel infoCaixaTexto15 = new JLabel("Insira o ID do Semestre:");
		infoCaixaTexto15.setBounds(450, 330, 150, 20);
		painel.add(infoCaixaTexto15);
		
		JButton botaoAvaliacao = new JButton("Adicionar Avaliação");
		botaoAvaliacao.setBounds(560, 350, 150, 20);
		painel.add(botaoAvaliacao);
		botaoAvaliacao.addActionListener( new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				try {
					sistema = new Sistema("taianicakaka");
					Avaliacao ava = new Avaliacao();
					ava.setNomeAvaliacao(caixaTexto6.getText());
					ava.setData(caixaTexto7.getText());
					ava.setPeso(Double.parseDouble(caixaTexto8.getText()));
					ava.setIdDisciplina(Integer.parseInt(caixaTexto9.getText()));
					ava.setIdSemestre(Integer.parseInt(caixaTexto10.getText()));
					sistema.adicionarAvaliacao(ava);
					avaliacoes.atualizar();
					caixaTexto6.setText("");
					caixaTexto7.setText("");
					caixaTexto8.setText("");
					caixaTexto9.setText("");
					caixaTexto10.setText("");
				} catch (Exception e) {
					e.getMessage();
				}
			}
		});
		
		//remover avaliacoes
		
		JTextField caixaTexto11 = new JTextField();
		caixaTexto11.setBounds(730, 350, 100, 20);
		painel.add(caixaTexto11);
		JLabel infoCaixaTexto16 = new JLabel("Insira o ID da avaliação a ser removida:");
		infoCaixaTexto16.setBounds(730, 330, 250, 20);
		painel.add(infoCaixaTexto16);
		
		JButton botaoRemoveAvaliacao = new JButton("Remover Avaliação");
		botaoRemoveAvaliacao.setBounds(840, 350, 150, 20);
		painel.add(botaoRemoveAvaliacao);
		botaoRemoveAvaliacao.addActionListener( new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				try {
					sistema = new Sistema("taianicakaka");
					int temp = Integer.parseInt(caixaTexto11.getText());
					sistema.removerAvaliacao(temp);
					avaliacoes.atualizar();
					caixaTexto11.setText("");
				} catch (Exception e) {
					e.getMessage();
				}
			}
		});
		
		//adicionar semestre
		
		JTextField caixaTexto12 = new JTextField();
		caixaTexto12.setBounds(10, 390, 150, 20);
		painel.add(caixaTexto12);
		JLabel infoCaixaTexto17 = new JLabel("Insira o nome:");
		infoCaixaTexto17.setBounds(10, 370, 150, 20);
		painel.add(infoCaixaTexto17);
		
		JButton botaoSemestre = new JButton("Adicionar Semestre");
		botaoSemestre.setBounds(170, 390, 150, 20);
		painel.add(botaoSemestre);
		botaoSemestre.addActionListener( new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				try {
					sistema = new Sistema("taianicakaka");
					Semestre sem = new Semestre();
					sem.setNomeSemestre(caixaTexto12.getText());
					sistema.adicionarSemestre(sem);
					semestres.atualizar();
					caixaTexto12.setText("");
				} catch (Exception e) {
					e.getMessage();
				}
			}
		});
		
		//remover Semestre
		
		JTextField caixaTexto13 = new JTextField();
		caixaTexto13.setBounds(350, 390, 100, 20);
		painel.add(caixaTexto13);
		JLabel infoCaixaTexto18 = new JLabel("Insira o ID do semestre a ser removido:");
		infoCaixaTexto18.setBounds(350, 370, 250, 20);
		painel.add(infoCaixaTexto18);
		
		JButton botaoRemoveSemestre = new JButton("Remover Semestre");
		botaoRemoveSemestre.setBounds(460, 390, 150, 20);
		painel.add(botaoRemoveSemestre);
		botaoRemoveSemestre.addActionListener( new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				try {
					sistema = new Sistema("taianicakaka");
					int temp = Integer.parseInt(caixaTexto13.getText());
					sistema.removerSemestre(temp);
					semestres.atualizar();
					caixaTexto13.setText("");
				} catch (Exception e) {
					e.getMessage();
				}
			}
		});
		
		//inserir disciplina em semestre
		
		JTextField caixaTexto14 = new JTextField();
		caixaTexto14.setBounds(10, 430, 135, 20);
		painel.add(caixaTexto14);
		JLabel infoCaixaTexto19 = new JLabel("Insira o ID do Semestre:");
		infoCaixaTexto19.setBounds(10, 410, 150, 20);
		painel.add(infoCaixaTexto19);
		
		JTextField caixaTexto15 = new JTextField();
		caixaTexto15.setBounds(155, 430, 135, 20);
		painel.add(caixaTexto15);
		JLabel infoCaixaTexto20 = new JLabel("Insira o ID da Disciplina:");
		infoCaixaTexto20.setBounds(155, 410, 150, 20);
		painel.add(infoCaixaTexto20);
		
		JButton botaoDiscSem = new JButton("Adicionar Disciplina em Semestre");
		botaoDiscSem.setBounds(310, 430, 240, 20);
		painel.add(botaoDiscSem);
		botaoDiscSem.addActionListener( new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				try {
					sistema = new Sistema("taianicakaka");
					int var1 = Integer.parseInt(caixaTexto14.getText());
					int var2 = Integer.parseInt(caixaTexto15.getText());
					sistema.adicionarDiscSem(var1, var2);
					caixaTexto14.setText("");
					caixaTexto15.setText("");
				} catch (Exception e) {
					e.getMessage();
				}
			}
		});
		
		//remover disciplina de semestre 
		
		JTextField caixaTexto16 = new JTextField();
		caixaTexto16.setBounds(560, 430, 150, 20);
		painel.add(caixaTexto16);
		JLabel infoCaixaTexto21 = new JLabel("Insira o ID do Semestre:");
		infoCaixaTexto21.setBounds(560, 410, 150, 20);
		painel.add(infoCaixaTexto21);
		
		JTextField caixaTexto17 = new JTextField();
		caixaTexto17.setBounds(720, 430, 150, 20);
		painel.add(caixaTexto17);
		JLabel infoCaixaTexto22 = new JLabel("Insira o ID da Disciplina:");
		infoCaixaTexto22.setBounds(720, 410, 150, 20);
		painel.add(infoCaixaTexto22);
		
		JButton botaoRemDiscSem = new JButton("Remover Disciplina de Semestre");
		botaoRemDiscSem.setBounds(880, 430, 221, 20);
		painel.add(botaoRemDiscSem);
		botaoRemDiscSem.addActionListener( new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				try {
					sistema = new Sistema("taianicakaka");
					int var1 = Integer.parseInt(caixaTexto16.getText());
					int var2 = Integer.parseInt(caixaTexto17.getText());
					sistema.removeDiscSemByDiscESem(var1, var2);
					caixaTexto16.setText("");
					caixaTexto17.setText("");
				} catch (Exception e) {
					e.getMessage();
				}
			}
		});
		
		//adicionar aluno em disciplina
		
		JTextField caixaTexto18 = new JTextField();
		caixaTexto18.setBounds(10, 470, 135, 20);
		painel.add(caixaTexto18);
		JLabel infoCaixaTexto23 = new JLabel("Insira o ID do Aluno:");
		infoCaixaTexto23.setBounds(10, 450, 150, 20);
		painel.add(infoCaixaTexto23);
		
		JTextField caixaTexto19 = new JTextField();
		caixaTexto19.setBounds(155, 470, 135, 20);
		painel.add(caixaTexto19);
		JLabel infoCaixaTexto24 = new JLabel("Insira o ID da Disciplina:");
		infoCaixaTexto24.setBounds(155, 450, 150, 20);
		painel.add(infoCaixaTexto24);
		
		JTextField caixaTexto20 = new JTextField();
		caixaTexto20.setBounds(300, 470, 135, 20);
		painel.add(caixaTexto20);
		JLabel infoCaixaTexto25 = new JLabel("Insira o ID do Semestre:");
		infoCaixaTexto25.setBounds(300, 450, 150, 20);
		painel.add(infoCaixaTexto25);
		
		JButton botaoAddAluDiscSem = new JButton("Cadastrar Aluno em Disciplina");
		botaoAddAluDiscSem.setBounds(450, 470, 221, 20);
		painel.add(botaoAddAluDiscSem);
		botaoAddAluDiscSem.addActionListener( new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				try {
					sistema = new Sistema("taianicakaka");
					int var1 = Integer.parseInt(caixaTexto18.getText());
					int var2 = Integer.parseInt(caixaTexto19.getText());
					int var3 = Integer.parseInt(caixaTexto20.getText());
					sistema.cadastrarAlunoEmDisciplinaSemestre(var1, var2, var3);
					caixaTexto18.setText("");
					caixaTexto19.setText("");
					caixaTexto20.setText("");
				} catch (Exception e) {
					e.getMessage();
				}
			}
		});
		
		//adicionar nota para aluno
		
		JTextField caixaTexto21 = new JTextField();
		caixaTexto21.setBounds(10, 510, 135, 20);
		painel.add(caixaTexto21);
		JLabel infoCaixaTexto26 = new JLabel("Insira o ID do Aluno:");
		infoCaixaTexto26.setBounds(10, 490, 150, 20);
		painel.add(infoCaixaTexto26);
		
		JTextField caixaTexto22 = new JTextField();
		caixaTexto22.setBounds(155, 510, 135, 20);
		painel.add(caixaTexto22);
		JLabel infoCaixaTexto27 = new JLabel("Insira o ID da Avaliação:");
		infoCaixaTexto27.setBounds(155, 490, 150, 20);
		painel.add(infoCaixaTexto27);
		
		JTextField caixaTexto23 = new JTextField();
		caixaTexto23.setBounds(300, 510, 100, 20);
		painel.add(caixaTexto23);
		JLabel infoCaixaTexto28 = new JLabel("Insira a nota:");
		infoCaixaTexto28.setBounds(300, 490, 150, 20);
		painel.add(infoCaixaTexto28);
		
		JButton botaoAddAluAva = new JButton("Cadastrar Nota");
		botaoAddAluAva.setBounds(410, 510, 160, 20);
		painel.add(botaoAddAluAva);
		botaoAddAluAva.addActionListener( new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				try {
					sistema = new Sistema("taianicakaka");
					int var1 = Integer.parseInt(caixaTexto21.getText());
					int var2 = Integer.parseInt(caixaTexto22.getText());
					double var3 = Double.parseDouble(caixaTexto23.getText());
					sistema.cadastrarAlunoAvaliacao(var1, var2, var3);
					caixaTexto21.setText("");
					caixaTexto22.setText("");
					caixaTexto23.setText("");
				} catch (Exception e) {
					e.getMessage();
				}
			}
		});
		
		//Relatório
		botaoRelatorio.setBounds(1107,  597,  155,  53);
		painel.add(botaoRelatorio);

		
		botaoRelatorio.addActionListener( new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				try {
					sistema = new Sistema("taianicakaka");
					sistema.gerarRelatorio();
				} catch (Exception e) {
					e.getMessage();
				}
			}
		});
		}
}
