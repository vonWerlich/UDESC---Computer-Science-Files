package apresentacao;

//import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.EventQueue;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
//import java.util.ArrayList;
//import java.util.List;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextField;
//import javax.swing.border.EmptyBorder;
//import java.sql.Date;

import dados.*;
//import exceptions.SelectException;
import negocio.Sistema;

import javax.swing.JLabel;
//import javax.swing.JComboBox;

@SuppressWarnings("serial")
public class Principal extends JFrame {
	
	private static Sistema sistema;

	private JPanel painel = new JPanel();
	private JScrollPane painelScrollTabelaAconselhamento = new JScrollPane();
	private JScrollPane painelScrollTabelaDepartamento = new JScrollPane();
	private JScrollPane painelScrollTabelaEstudante = new JScrollPane();
	private JScrollPane painelScrollTabelaPessoa = new JScrollPane();
	private JScrollPane painelScrollTabelaProfessor = new JScrollPane();
	private JScrollPane painelScrollTabelaProfDep = new JScrollPane();
	private JScrollPane painelScrollTabelaProjeto = new JScrollPane();
	private JScrollPane painelScrollTabelaProjEst = new JScrollPane();
	private JScrollPane painelScrollTabelaProjProf = new JScrollPane();
	private TabelaAconselhamentos aconselhamentos = new TabelaAconselhamentos();
	private TabelaDepartamentos departamentos = new TabelaDepartamentos();
	private TabelaEstudantes estudantes = new TabelaEstudantes();
	private TabelaPessoas pessoas = new TabelaPessoas();
	private TabelaProfDep profdep = new TabelaProfDep();
	private TabelaProfessores professores = new TabelaProfessores();
	private TabelaProjEst projest = new TabelaProjEst();
	private TabelaProjetos projetos = new TabelaProjetos();
	private TabelaProjProf projprof = new TabelaProjProf();
	private JTable tabelaAconselhamentos = new JTable(aconselhamentos);
	private JTable tabelaDepartamentos = new JTable(departamentos);
	private JTable tabelaEstudantes = new JTable(estudantes);
	private JTable tabelaPessoas = new JTable(pessoas);
	private JTable tabelaProfessores = new JTable(professores);
	private JTable tabelaProfDepartamentos = new JTable(profdep);
	private JTable tabelaProjetos = new JTable(projetos);
	private JTable tabelaProjetoEstudantes = new JTable(projest);
	private JTable tabelaProjetoProfessores = new JTable(projprof);
	private final JLabel lblNewLabel_8 = new JLabel("Nome");
	private final JLabel lblNewLabel_9 = new JLabel("Idade");
	private final JTextField textField = new JTextField();
	private final JTextField textField_1 = new JTextField();
	private final JTextField textField_2 = new JTextField();
	private final JTextField textField_3 = new JTextField();
	private final JTextField textField_4 = new JTextField();
	private final JTextField textField_5 = new JTextField();
	private final JTextField textField_6 = new JTextField();
	private final JTextField textField_7 = new JTextField();
	private final JTextField textField_8 = new JTextField();
	private final JTextField textField_10 = new JTextField();
	private final JTextField textField_11 = new JTextField();
	private final JTextField textField_12 = new JTextField();
	private final JLabel lblNewLabel_9_1 = new JLabel("Idade");
	private final JLabel lblNewLabel_9_2 = new JLabel("Matrícula");
	private final JLabel lblNewLabel_9_3 = new JLabel("Matrícula");
	private final JLabel lblNewLabel_9_4 = new JLabel("Nome");
	private final JLabel lblNewLabel_9_5 = new JLabel("Escritório");
	private final JLabel lblNewLabel_9_6 = new JLabel("Professor Líder");
	private final JTextField textField_9 = new JTextField();
	private final JLabel lblNewLabel_9_2_1 = new JLabel("Número");
	private final JButton botaoremovedep = new JButton("Remover Departamento");
	private JTextField textField_13;
	private JTextField textField_14;
	private final JTextField textField_15 = new JTextField();
	private final JTextField textField_16 = new JTextField();
	private final JButton botaoremoveConselheiro = new JButton("Remover Conselheiro");
	private final JLabel lblNewLabel_8_1_1_1_2 = new JLabel("Aconselhado");
	private final JLabel lblNewLabel_8_1_1_1_1_1 = new JLabel("Aconselhador");
	private final JTextField textField_17 = new JTextField();
	private final JTextField textField_18 = new JTextField();
	private final JTextField textField_19 = new JTextField();
	private final JTextField textField_20 = new JTextField();
	private final JTextField textField_21 = new JTextField();
	private final JLabel lblNewLabel_8_4 = new JLabel("Financiador");
	private final JLabel lblNewLabel_8_5 = new JLabel("Data Início");
	private final JLabel lblNewLabel_8_6 = new JLabel("Data Término");
	private final JLabel lblNewLabel_8_7 = new JLabel("Orçamento");
	private final JLabel lblNewLabel_8_8 = new JLabel("Líder");
	private final JButton botaoProjeto = new JButton("Adicionar Projeto");
	private final JTextField textField_22 = new JTextField();
	private final JLabel lblNewLabel_9_2_1_1 = new JLabel("Número");
	private final JButton botaoremoveProjeto = new JButton("Remover Projeto");
	private final JTextField textField_23 = new JTextField();
	private final JTextField textField_24 = new JTextField();
	private final JLabel lblNewLabel_9_2_1_2 = new JLabel("Número");
	private final JLabel lblNewLabel_8_1_1_2 = new JLabel("Mat. Professor");
	private final JButton botaoProjProf = new JButton("Adicionar Proj-Prof");
	private final JTextField textField_25 = new JTextField();
	private final JTextField textField_26 = new JTextField();
	private final JLabel lblNewLabel_9_2_1_2_1 = new JLabel("Número");
	private final JLabel lblNewLabel_8_1_1_2_1 = new JLabel("Mat. Professor");
	private final JButton botaoremoveProjProf = new JButton("Remover Proj-Prof");
	private JTextField textField_27;
	private JTextField textField_28;
	private JTextField textField_29;
	private JTextField textField_30;
	private JTextField textField_31;
	private final JTextField textField_32 = new JTextField();
	private final JTextField textField_33 = new JTextField();
	private final JTextField textField_34 = new JTextField();
	private final JButton botaoadicionarProfDep = new JButton("Adicionar Prof-Dep");
	private final JLabel lblNewLabel_8_1_4_2 = new JLabel("Porcentagem");
	private final JLabel lblNewLabel_8_3_1 = new JLabel("Departamento");
	private final JLabel lblNewLabel_8_1_1_3 = new JLabel("Matrícula");
	private final JTextField textField_35 = new JTextField();
	private final JTextField textField_36 = new JTextField();
	private final JLabel lblNewLabel_8_3_1_1 = new JLabel("Departamento");
	private final JLabel lblNewLabel_8_1_1_3_1 = new JLabel("Matrícula");
	private final JButton botaoremoveProfDep = new JButton("Remover Prof-Dep");
	
	
	
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
		setTitle("Sistema de Controle de Universidade");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(10,10,1300,700);
		setContentPane(painel);
		painel.setLayout(null);
		
		
		painel.setBackground(new Color(154, 205, 50));
		painelScrollTabelaAconselhamento.setBounds(302, 134, 256, 91);
		painelScrollTabelaDepartamento.setBounds(302, 24, 407, 91);
		painelScrollTabelaEstudante.setBounds(10, 134, 270, 91);
		painelScrollTabelaPessoa.setBounds(10, 24, 270, 91);
		painelScrollTabelaProfessor.setBounds(10, 250, 270, 80);
		painelScrollTabelaProfDep.setBounds(302, 250, 389, 80);
		painelScrollTabelaProjeto.setBounds(568, 134, 591, 91);
		painelScrollTabelaProjEst.setBounds(717, 250, 283, 80);
		painelScrollTabelaProjProf.setBounds(719, 24, 351, 91);
		
		painel.add(painelScrollTabelaAconselhamento);
		painel.add(painelScrollTabelaDepartamento);
		painel.add(painelScrollTabelaEstudante);
		painel.add(painelScrollTabelaPessoa);
		painel.add(painelScrollTabelaProfessor);
		painel.add(painelScrollTabelaProfDep);
		painel.add(painelScrollTabelaProjeto);
		painel.add(painelScrollTabelaProjEst);
		painel.add(painelScrollTabelaProjProf);
		
		painelScrollTabelaAconselhamento.setViewportView(tabelaAconselhamentos);
		painelScrollTabelaDepartamento.setViewportView(tabelaDepartamentos);
		painelScrollTabelaEstudante.setViewportView(tabelaEstudantes);
		painelScrollTabelaPessoa.setViewportView(tabelaPessoas);
		painelScrollTabelaProfessor.setViewportView(tabelaProfessores);
		painelScrollTabelaProfDep.setViewportView(tabelaProfDepartamentos);
		painelScrollTabelaProjeto.setViewportView(tabelaProjetos);
		painelScrollTabelaProjEst.setViewportView(tabelaProjetoEstudantes);
		painelScrollTabelaProjProf.setViewportView(tabelaProjetoProfessores);
		
		JLabel Pessoas = new JLabel("Pessoas:");
		Pessoas.setBounds(10, 11, 138, 14);
		painel.add(Pessoas);
		
		JLabel lblNewLabel = new JLabel("Estudantes:");
		lblNewLabel.setBounds(10, 120, 117, 14);
		painel.add(lblNewLabel);
		
		JLabel lblNewLabel_1 = new JLabel("Professores:");
		lblNewLabel_1.setBounds(10, 236, 138, 14);
		painel.add(lblNewLabel_1);
		
		JLabel lblNewLabel_2 = new JLabel("Departamentos:");
		lblNewLabel_2.setBounds(302, 11, 145, 14);
		painel.add(lblNewLabel_2);
		
		JLabel lblNewLabel_3 = new JLabel("Projetos:");
		lblNewLabel_3.setBounds(568, 120, 145, 14);
		painel.add(lblNewLabel_3);
		
		JLabel lblNewLabel_4 = new JLabel("Aconselhamento");
		lblNewLabel_4.setBounds(302, 120, 117, 14);
		painel.add(lblNewLabel_4);
		
		JLabel lblNewLabel_5 = new JLabel("Professor-Departamento");
		lblNewLabel_5.setBounds(302, 236, 156, 14);
		painel.add(lblNewLabel_5);
		
		JLabel lblNewLabel_6 = new JLabel("Projeto-Professor:");
		lblNewLabel_6.setBounds(721, 11, 159, 14);
		painel.add(lblNewLabel_6);
		
		JLabel lblNewLabel_7 = new JLabel("Projeto-Estudante");
		lblNewLabel_7.setBounds(718, 236, 162, 14);
		painel.add(lblNewLabel_7);
		
		//adicionar Pessoa
		JTextField caixaTexto1 = new JTextField();
		JTextField caixaTexto2 = new JTextField();
		caixaTexto1.setBounds(10, 356, 150, 20);
		painel.add(caixaTexto1);
		JLabel infoCaixaTexto5 = new JLabel("Insira o Nome:");
		infoCaixaTexto5.setBounds(10, 250, 150, 20);
		painel.add(infoCaixaTexto5);
		
		caixaTexto2.setBounds(170, 356, 150, 20);
		painel.add(caixaTexto2);
		JLabel infoCaixaTexto6 = new JLabel("Insira a Idade:");
		infoCaixaTexto6.setBounds(170, 250, 150, 20);
		painel.add(infoCaixaTexto6);
		
		JButton botaoAluno = new JButton("Adicionar Pessoa");
		botaoAluno.setBounds(330, 356, 150, 20);
		painel.add(botaoAluno);
		lblNewLabel_8.setBounds(10, 341, 46, 14);
		
		painel.add(lblNewLabel_8);
		lblNewLabel_9.setBounds(171, 341, 46, 14);
		
		painel.add(lblNewLabel_9);
		textField.setBounds(10, 395, 69, 20);
		
		painel.add(textField);
		textField_1.setBounds(91, 395, 150, 20);
		
		painel.add(textField_1);
		textField_2.setBounds(251, 395, 150, 20);
		
		painel.add(textField_2);
		
		JButton botaoAluno_1 = new JButton("Adicionar Estudante");
		botaoAluno_1.setBounds(411, 395, 150, 20);
		painel.add(botaoAluno_1);
		
		JLabel lblNewLabel_8_1 = new JLabel("Matrícula");
		lblNewLabel_8_1.setBounds(10, 380, 69, 14);
		painel.add(lblNewLabel_8_1);
		
		JLabel lblNewLabel_8_2 = new JLabel("Tipo Curso");
		lblNewLabel_8_2.setBounds(91, 380, 95, 14);
		painel.add(lblNewLabel_8_2);
		
		JLabel lblNewLabel_8_3 = new JLabel("Departamento");
		lblNewLabel_8_3.setBounds(252, 380, 106, 14);
		painel.add(lblNewLabel_8_3);
		textField_3.setBounds(10, 433, 69, 20);
		
		painel.add(textField_3);
		textField_4.setBounds(91, 433, 150, 20);
		
		painel.add(textField_4);
		textField_5.setBounds(251, 433, 150, 20);
		
		painel.add(textField_5);
		
		JLabel lblNewLabel_8_1_1 = new JLabel("Matrícula");
		lblNewLabel_8_1_1.setBounds(10, 419, 69, 14);
		painel.add(lblNewLabel_8_1_1);
		
		JLabel lblNewLabel_8_1_2 = new JLabel("Especialidade");
		lblNewLabel_8_1_2.setBounds(91, 419, 106, 14);
		painel.add(lblNewLabel_8_1_2);
		
		JLabel lblNewLabel_8_1_3 = new JLabel("Sala");
		lblNewLabel_8_1_3.setBounds(251, 419, 69, 14);
		painel.add(lblNewLabel_8_1_3);
		
		JButton botaoprofessor = new JButton("Adicionar Professor");
		botaoprofessor.setBounds(411, 432, 150, 20);
		painel.add(botaoprofessor);
		textField_6.setBounds(490, 356, 69, 20);
		
		painel.add(textField_6);
		textField_7.setBounds(571, 395, 69, 20);
		
		painel.add(textField_7);
		textField_8.setBounds(571, 433, 69, 20);
		
		painel.add(textField_8);
		
		JButton botaoAluno_2 = new JButton("Remover Pessoa");
		JButton botaoremoveEst = new JButton("Remover Estudante");
		JButton botaoremoveProf = new JButton("Remover Professor");
		
		
		botaoAluno_2.setBounds(571, 355, 150, 20);
		
		painel.add(botaoAluno_2);
		botaoremoveEst.setBounds(650, 394, 150, 20);
		
		painel.add(botaoremoveEst);
		botaoremoveProf.setBounds(650, 432, 150, 20);
		
		painel.add(botaoremoveProf);
		textField_10.setBounds(743, 356, 106, 20);
		
		painel.add(textField_10);
		textField_11.setBounds(859, 356, 106, 20);
		
		painel.add(textField_11);
		textField_12.setBounds(975, 356, 117, 20);
		
		painel.add(textField_12);
		
		JButton botaodepartamento = new JButton("Adicionar Departamento");
		botaodepartamento.setBounds(1102, 356, 172, 20);
		painel.add(botaodepartamento);
		
		lblNewLabel_9_1.setBounds(490, 341, 46, 14);
		
		painel.add(lblNewLabel_9_1);
		lblNewLabel_9_2.setBounds(571, 380, 79, 14);
		
		painel.add(lblNewLabel_9_2);
		lblNewLabel_9_3.setBounds(571, 419, 95, 14);
		
		painel.add(lblNewLabel_9_3);
		lblNewLabel_9_4.setBounds(743, 341, 46, 14);
		
		painel.add(lblNewLabel_9_4);
		lblNewLabel_9_5.setBounds(859, 341, 79, 14);
		
		painel.add(lblNewLabel_9_5);
		lblNewLabel_9_6.setBounds(975, 341, 95, 14);
		
		painel.add(lblNewLabel_9_6);
		textField_9.setBounds(823, 395, 69, 20);
		
		painel.add(textField_9);
		lblNewLabel_9_2_1.setBounds(823, 380, 79, 14);
		
		painel.add(lblNewLabel_9_2_1);
		botaoremovedep.setBounds(898, 394, 172, 20);
		
		painel.add(botaoremovedep);
		
		textField_13 = new JTextField();
		textField_13.setBounds(10, 473, 69, 20);
		painel.add(textField_13);
		
		textField_14 = new JTextField();
		textField_14.setBounds(91, 473, 69, 20);
		painel.add(textField_14);
		
		JLabel lblNewLabel_8_1_1_1 = new JLabel("Aconselhado");
		lblNewLabel_8_1_1_1.setBounds(10, 458, 79, 14);
		painel.add(lblNewLabel_8_1_1_1);
		
		JLabel lblNewLabel_8_1_1_1_1 = new JLabel("Aconselhador");
		lblNewLabel_8_1_1_1_1.setBounds(91, 458, 95, 14);
		painel.add(lblNewLabel_8_1_1_1_1);
		
		JButton botaoAconselhamento = new JButton("Adicionar Conselheiro");
		botaoAconselhamento.setBounds(170, 472, 159, 20);
		painel.add(botaoAconselhamento);
		textField_15.setBounds(350, 473, 69, 20);
		
		painel.add(textField_15);
		textField_16.setBounds(431, 473, 69, 20);
		
		painel.add(textField_16);
		botaoremoveConselheiro.setBounds(510, 473, 162, 20);
		
		painel.add(botaoremoveConselheiro);
		lblNewLabel_8_1_1_1_2.setBounds(350, 458, 89, 14);
		
		painel.add(lblNewLabel_8_1_1_1_2);
		lblNewLabel_8_1_1_1_1_1.setBounds(431, 458, 89, 14);
		
		painel.add(lblNewLabel_8_1_1_1_1_1);
		textField_17.setBounds(10, 519, 150, 20);
		
		painel.add(textField_17);
		textField_18.setBounds(170, 519, 117, 20);
		
		painel.add(textField_18);
		textField_19.setBounds(302, 519, 150, 20);
		
		painel.add(textField_19);
		textField_20.setBounds(462, 519, 150, 20);
		
		painel.add(textField_20);
		textField_21.setBounds(622, 519, 79, 20);
		
		painel.add(textField_21);
		lblNewLabel_8_4.setBounds(10, 504, 69, 14);
		
		painel.add(lblNewLabel_8_4);
		lblNewLabel_8_5.setBounds(171, 504, 109, 14);
		
		painel.add(lblNewLabel_8_5);
		lblNewLabel_8_6.setBounds(302, 503, 89, 14);
		
		painel.add(lblNewLabel_8_6);
		lblNewLabel_8_7.setBounds(462, 504, 96, 14);
		
		painel.add(lblNewLabel_8_7);
		lblNewLabel_8_8.setBounds(622, 504, 46, 14);
		
		painel.add(lblNewLabel_8_8);
		botaoProjeto.setBounds(717, 519, 162, 20);
		
		painel.add(botaoProjeto);
		textField_22.setBounds(889, 519, 69, 20);
		
		painel.add(textField_22);
		lblNewLabel_9_2_1_1.setBounds(886, 504, 79, 14);
		
		painel.add(lblNewLabel_9_2_1_1);
		botaoremoveProjeto.setBounds(968, 518, 162, 20);
		
		painel.add(botaoremoveProjeto);
		textField_23.setBounds(10, 560, 69, 20);
		
		painel.add(textField_23);
		textField_24.setBounds(91, 560, 69, 20);
		
		painel.add(textField_24);
		lblNewLabel_9_2_1_2.setBounds(10, 546, 79, 14);
		
		painel.add(lblNewLabel_9_2_1_2);
		lblNewLabel_8_1_1_2.setBounds(91, 546, 89, 14);
		
		painel.add(lblNewLabel_8_1_1_2);
		botaoProjProf.setBounds(170, 559, 150, 20);
		
		painel.add(botaoProjProf);
		textField_25.setBounds(330, 560, 69, 20);
		
		painel.add(textField_25);
		textField_26.setBounds(409, 560, 69, 20);
		
		painel.add(textField_26);
		lblNewLabel_9_2_1_2_1.setBounds(330, 546, 79, 14);
		
		painel.add(lblNewLabel_9_2_1_2_1);
		lblNewLabel_8_1_1_2_1.setBounds(411, 546, 95, 14);
		
		painel.add(lblNewLabel_8_1_1_2_1);
		botaoremoveProjProf.setBounds(490, 559, 150, 20);
		
		painel.add(botaoremoveProjProf);
		
		textField_27 = new JTextField();
		textField_27.setBounds(10, 599, 69, 20);
		painel.add(textField_27);
		
		textField_28 = new JTextField();
		textField_28.setBounds(91, 599, 69, 20);
		painel.add(textField_28);
		
		textField_29 = new JTextField();
		textField_29.setBounds(172, 599, 69, 20);
		painel.add(textField_29);
		
		JLabel lblNewLabel_9_2_1_3 = new JLabel("Num. Projeto");
		lblNewLabel_9_2_1_3.setBounds(10, 587, 79, 14);
		painel.add(lblNewLabel_9_2_1_3);
		
		JButton botaoprojetoEst = new JButton("Adicionar Proj-Est");
		botaoprojetoEst.setBounds(251, 598, 150, 20);
		painel.add(botaoprojetoEst);
		
		JLabel lblNewLabel_8_1_4 = new JLabel("Estudante");
		lblNewLabel_8_1_4.setBounds(91, 587, 69, 14);
		painel.add(lblNewLabel_8_1_4);
		
		JLabel lblNewLabel_8_1_5 = new JLabel("Supervisor");
		lblNewLabel_8_1_5.setBounds(172, 587, 69, 14);
		painel.add(lblNewLabel_8_1_5);
		
		textField_30 = new JTextField();
		textField_30.setBounds(409, 599, 69, 20);
		painel.add(textField_30);
		
		textField_31 = new JTextField();
		textField_31.setBounds(490, 599, 69, 20);
		painel.add(textField_31);
		
		JButton botaoremoveProjEst = new JButton("Remover Proj-Est");
		botaoremoveProjEst.setBounds(568, 598, 150, 20);
		painel.add(botaoremoveProjEst);
		
		JLabel lblNewLabel_9_2_1_3_1 = new JLabel("Num. Projeto");
		lblNewLabel_9_2_1_3_1.setBounds(411, 587, 79, 14);
		painel.add(lblNewLabel_9_2_1_3_1);
		
		JLabel lblNewLabel_8_1_4_1 = new JLabel("Estudante");
		lblNewLabel_8_1_4_1.setBounds(490, 587, 69, 14);
		painel.add(lblNewLabel_8_1_4_1);
		textField_32.setBounds(799, 584, 81, 20);
		
		painel.add(textField_32);
		textField_33.setBounds(886, 584, 87, 20);
		
		painel.add(textField_33);
		textField_34.setBounds(983, 584, 69, 20);
		
		painel.add(textField_34);
		botaoadicionarProfDep.setBounds(1062, 584, 150, 20);
		
		painel.add(botaoadicionarProfDep);
		lblNewLabel_8_1_4_2.setBounds(983, 563, 87, 14);
		
		painel.add(lblNewLabel_8_1_4_2);
		lblNewLabel_8_3_1.setBounds(889, 563, 106, 14);
		
		painel.add(lblNewLabel_8_3_1);
		lblNewLabel_8_1_1_3.setBounds(799, 563, 69, 14);
		
		painel.add(lblNewLabel_8_1_1_3);
		textField_35.setBounds(799, 627, 69, 20);
		
		painel.add(textField_35);
		textField_36.setBounds(878, 627, 69, 20);
		
		painel.add(textField_36);
		lblNewLabel_8_3_1_1.setBounds(878, 605, 106, 14);
		
		painel.add(lblNewLabel_8_3_1_1);
		lblNewLabel_8_1_1_3_1.setBounds(799, 605, 69, 14);
		
		painel.add(lblNewLabel_8_1_1_3_1);
		botaoremoveProfDep.setBounds(957, 626, 150, 20);
		
		painel.add(botaoremoveProfDep);
		
		/*try {
			List<Pessoa> tempPessoas = sistema.selectAllPessoas();
			ArrayList<String> todos = new ArrayList<String>();
			for (int i=0; i<tempPessoas.size(); i++) {
				todos.add(tempPessoas.get(i).toString());
			}
			
			JComboBox<String> comboBox = new JComboBox();
			comboBox.setBounds(1158, 432, 89, 22);
			
			painel.add(comboBox);
			comboBox.addItem("Selecione:");
			comboBox.
			
		} catch (SelectException e1) {
			e1.printStackTrace();
		}*/
		
	
		
		
		
		botaoAluno.addActionListener( new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				try {
					sistema = new Sistema("taianicakaka");
					Pessoa temp = new Pessoa();
					temp.setNome(caixaTexto1.getText());
					temp.setIdade(Integer.parseInt(caixaTexto2.getText()));
					sistema.adicionarPessoa(temp);
					pessoas.atualizar();
					caixaTexto1.setText("");
					caixaTexto2.setText("");
				} catch (Exception e) {
					e.getMessage();
				}
			}
		});
		
		botaoAluno_1.addActionListener( new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				try {
					sistema = new Sistema("taianicakaka");
					Estudante temp = new Estudante();
					temp.setMatricula(Integer.parseInt(textField.getText()));
					temp.setTipocurso(textField_1.getText());
					temp.setDepcurso(Integer.parseInt(textField_2.getText()));
					sistema.adicionarEstudante(temp);
					estudantes.atualizar();
					textField.setText("");
					textField_1.setText("");
					textField_2.setText("");
				} catch (Exception e) {
					e.getMessage();
				}
			}
		});
		botaoprofessor.addActionListener( new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				try {
					sistema = new Sistema("taianicakaka");
					Professor temp = new Professor();
					temp.setMatricula(Integer.parseInt(textField_3.getText()));
					temp.setEspecialidade(textField_4.getText());
					temp.setSala(textField_5.getText());
					sistema.adicionarProfessor(temp);
					professores.atualizar();
					textField_3.setText("");
					textField_4.setText("");
					textField_5.setText("");
				} catch (Exception e) {
					e.getMessage();
				}
			}
		});
		
		botaoAluno_2.addActionListener( new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				try {
					sistema = new Sistema("taianicakaka");
					int temp;
					temp = Integer.parseInt(textField_6.getText());
					sistema.removerPessoaByMat(temp);
					pessoas.atualizar();
				} catch (Exception e) {
					e.getMessage();
				}
			}
		});
		
		botaoremoveEst.addActionListener( new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				try {
					sistema = new Sistema("taianicakaka");
					int temp;
					temp = Integer.parseInt(textField_7.getText());
					sistema.removerEstudanteByMat(temp);
					estudantes.atualizar();
				} catch (Exception e) {
					e.getMessage();
				}
			}
		});
		
		botaoremoveProf.addActionListener( new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				try {
					sistema = new Sistema("taianicakaka");
					int temp;
					temp = Integer.parseInt(textField_8.getText());
					sistema.removerProfessorByMat(temp);
					professores.atualizar();
					departamentos.atualizar();
					
				} catch (Exception e) {
					e.getMessage();
				}
			}
		});
		
		botaodepartamento.addActionListener( new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				try {
					sistema = new Sistema("taianicakaka");
					Departamento temp = new Departamento();
					temp.setNomedep(textField_10.getText());
					temp.setEscritorioprincipal(textField_11.getText());
					temp.setProfessorlider(Integer.parseInt(textField_12.getText()));
					sistema.adicionarDepartamento(temp);
					departamentos.atualizar();
					professores.atualizar();
					textField_10.setText("");
					textField_11.setText("");
					textField_12.setText("");
				} catch (Exception e) {
					e.getMessage();
				}
			}
		});
		
		botaoremovedep.addActionListener( new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				try {
					sistema = new Sistema("taianicakaka");
					int temp;
					temp = Integer.parseInt(textField_9.getText());
					sistema.removerDepartamentoByNumDep(temp);
					departamentos.atualizar();
					textField_9.setText("");
				} catch (Exception e) {
					e.getMessage();
				}
			}
		});
		
		botaoAconselhamento.addActionListener( new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				try {
					sistema = new Sistema("taianicakaka");
					int temp1 = Integer.parseInt(textField_13.getText());
					int temp2 = Integer.parseInt(textField_14.getText());
					sistema.adicionarAconselhamento(temp1, temp2);
					aconselhamentos.atualizar();
					textField_13.setText("");
					textField_14.setText("");
				} catch (Exception e) {
					e.getMessage();
				}
			}
		});
		
		botaoremoveConselheiro.addActionListener( new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				try {
					sistema = new Sistema("taianicakaka");
					int temp1 = Integer.parseInt(textField_15.getText());
					int temp2 = Integer.parseInt(textField_16.getText());
					sistema.removerAconselhamentoByAll(temp1, temp2);
					aconselhamentos.atualizar();
					textField_15.setText("");
					textField_16.setText("");
				} catch (Exception e) {
					e.getMessage();
				}
			}
		});
		
		botaoProjeto.addActionListener( new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				try {
					sistema = new Sistema("taianicakaka");
					Projeto temp = new Projeto();
					temp.setOrgaofinanciador(textField_17.getText());
					temp.setDatainicio(textField_18.getText());
					temp.setDatatermino(textField_19.getText());
					temp.setOrcamento(Double.parseDouble(textField_20.getText()));
					temp.setPesquisadorprinc(Integer.parseInt(textField_21.getText()));
					sistema.adicionarProjeto(temp);
					projetos.atualizar();
					textField_17.setText("");
					textField_18.setText("");
					textField_19.setText("");
					textField_20.setText("");
					textField_21.setText("");
				} catch (Exception e) {
					e.getMessage();
				}
			}
		});
		
		botaoremoveProjeto.addActionListener( new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				try {
					sistema = new Sistema("taianicakaka");
					int temp;
					temp = Integer.parseInt(textField_22.getText());
					sistema.removerProjetoByNumProj(temp);
					projetos.atualizar();
					textField_22.setText("");
				} catch (Exception e) {
					e.getMessage();
				}
			}
		});
		
		botaoProjProf.addActionListener( new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				try {
					sistema = new Sistema("taianicakaka");
					int temp1 = Integer.parseInt(textField_23.getText());
					int temp2 = Integer.parseInt(textField_24.getText());
					sistema.adicionarProjProfessor(temp1, temp2);
					projprof.atualizar();
					textField_23.setText("");
					textField_24.setText("");
				} catch (Exception e) {
					e.getMessage();
				}
			}
		});
		
		botaoremoveProjProf.addActionListener( new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				try {
					sistema = new Sistema("taianicakaka");
					int temp1 = Integer.parseInt(textField_25.getText());
					int temp2 = Integer.parseInt(textField_26.getText());
					sistema.removerProjetoProfessorByAll(temp1, temp2);
					projprof.atualizar();
					textField_25.setText("");
					textField_26.setText("");
				} catch (Exception e) {
					e.getMessage();
				}
			}
		});
		
		botaoprojetoEst.addActionListener( new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				try {
					sistema = new Sistema("taianicakaka");
					int temp1 = Integer.parseInt(textField_27.getText());
					int temp2 = Integer.parseInt(textField_28.getText());
					int temp3 = Integer.parseInt(textField_29.getText());
					sistema.adicionarProjEstudante(temp1, temp2, temp3);
					projest.atualizar();
					textField_27.setText("");
					textField_28.setText("");
					textField_29.setText("");
				} catch (Exception e) {
					e.getMessage();
				}
			}
		});
		
		botaoremoveProjEst.addActionListener( new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				try {
					sistema = new Sistema("taianicakaka");
					int temp1 = Integer.parseInt(textField_30.getText());
					int temp2 = Integer.parseInt(textField_31.getText());
					sistema.removerProjetoEstudanteByAll(temp1, temp2);
					projest.atualizar();
					textField_30.setText("");
					textField_31.setText("");
				} catch (Exception e) {
					e.getMessage();
				}
			}
		});
		
		botaoadicionarProfDep.addActionListener( new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				try {
					sistema = new Sistema("taianicakaka");
					int temp1 = Integer.parseInt(textField_32.getText());
					int temp2 = Integer.parseInt(textField_33.getText());
					double temp3 = Double.parseDouble(textField_34.getText());
					if ((sistema.porcentagemTempo(temp1) + temp3 <= 100) && temp3 > 0) {
						sistema.adicionarProfDepartamento(temp1, temp2, temp3);
					profdep.atualizar();
					textField_32.setText("");
					textField_33.setText("");
					textField_34.setText("");
					}
					
				} catch (Exception e) {
					e.getMessage();
				}
			}
		});
		
		botaoremoveProfDep.addActionListener( new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				try {
					sistema = new Sistema("taianicakaka");
					int temp1 = Integer.parseInt(textField_35.getText());
					int temp2 = Integer.parseInt(textField_36.getText());
					sistema.removerProfessorDepartamentoByAll(temp1, temp2);
					profdep.atualizar();
					textField_35.setText("");
					textField_36.setText("");
				} catch (Exception e) {
					e.getMessage();
				}
			}
		});

		
	}
}
