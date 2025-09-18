import java.sql.SQLException;
import java.util.List;
import java.util.Scanner;

import dados.*;
import exceptions.InsertException;
import exceptions.SelectException;
import persistencia.*;


public class Principal {

	private ClienteDAO clienteDAO;
	private ImovelDAO imovelDAO;
	private ProprietarioDAO proprietarioDAO;
	private CompraDAO compraDAO;
	private AluguelDAO aluguelDAO;
	
	private static Principal principal;
	private static Scanner s = new Scanner(System.in);
	
	public static void main (String args[]) {
		
		try {
			principal = new Principal("taianicakaka");
		
		int opcao = -1;
		
		while (opcao != 12) {
			
			System.out.println("Escolha uma opção");
			System.out.println("1 - Cadastrar um proprietário");
			System.out.println("2 - Cadastrar um cliente");
			System.out.println("3 - Cadastrar um imóvel");
			System.out.println("4 - Cadastrar um imóvel a um proprietário");
			System.out.println("5 - Cadastrar uma compra");
			System.out.println("6 - Cadastrar um aluguel");
			System.out.println("7 - Listar todos os imóveis");
			System.out.println("8 - Listar todos os proprietários");
			System.out.println("9 - Listar todos os clientes");
			System.out.println("10 - Mostrar os imóveis mais baratos");
			System.out.println("11 - Mostrar os clientes que compraram imoveis com preco >= 1.000.000");
			System.out.println("12 - Sair do programa");
			
			opcao = Integer.parseInt(s.nextLine());
			
			switch (opcao) {
			
				case 1:
					System.out.println("Digite o nome do novo proprietário:");
					String nome = s.nextLine();
					System.out.println("Digite o telefone do novo proprietário");
					String telefone = s.nextLine();
					
					Proprietario temp = new Proprietario();
					temp.setNomeprop(nome);
					temp.setTelefone(telefone);
					
					try {
						principal.proprietarioDAO.insert(temp);
					} catch (InsertException e) {
						e.getMessage();
					} catch (SelectException e) {
						e.getMessage();
					}
					
					break;
				case 2:
					System.out.println("Digite o nome do novo cliente:");
					String nome2 = s.nextLine();
					System.out.println("Digite o telefone do novo cliente");
					String telefone2 = s.nextLine();
					
					Cliente temp2 = new Cliente();
					temp2.setNomecliente(nome2);
					temp2.setTelefone(telefone2);
					
					try {
						principal.clienteDAO.insert(temp2);
					} catch (InsertException e) {
						e.getMessage();
					} catch (SelectException e) {
						e.getMessage();
					}
					break;
				case 3:
					System.out.println("Digite o a área do novo imóvel:");
					double area = Double.parseDouble(s.nextLine());
					System.out.println("Digite o preço do novo imóvel:");
					double preco = Double.parseDouble(s.nextLine());
					System.out.println("Digite a descrição do novo imóvel:");
					String descricao = s.nextLine();
					System.out.println("Digite o CEP do novo terreno:");
					String cep = s.nextLine();
					
					Imovel temp3 = new Imovel();
					temp3.setArea(area);
					temp3.setPreco(preco);
					temp3.setDescricao(descricao);
					temp3.setCep(cep);
					
					try {
						principal.imovelDAO.insert(temp3);
					} catch (InsertException e) {
						e.getMessage();
					} catch (SelectException e) {
						e.getMessage();
					}
					break;
				case 4:
					
				try {
					List<Imovel> imo= principal.imovelDAO.selectAll();
					mostrarImoveis();
					if (imo.size()==0) {
						System.out.println("Nenhum imóvel cadastrado!");
						break;
					}
					System.out.println("Selecione o id do imóvel a ser cadastrado:");
					int num1 = Integer.parseInt(s.nextLine());
					
					List<Proprietario> pro = principal.proprietarioDAO.selectAll();
					mostrarProprietarios();
					if (pro.size()==0) {
						System.out.println("Nenhum proprietário cadastrado!");
						break;
					}
					System.out.println("Selecione o id do proprietário a ser cadastrado:");
					int num2 = Integer.parseInt(s.nextLine());
					
					principal.imovelDAO.insertImoProp(num1, num2);
					
				} catch (SelectException e1) {
					e1.getMessage();
				} catch (InsertException e) {
					e.getMessage();
				}
					
					break;
				case 5:
					try {
						List<Imovel> imo= principal.imovelDAO.selectAll();
						mostrarImoveis();
						if (imo.size() == 0) {
							System.out.println("Nenhum imóvel cadastrado!");
							break;
						}
						System.out.println("Selecione o id do imóvel a ser cadastrado:");
						int num1 = Integer.parseInt(s.nextLine());
						
						List<Cliente> cli= principal.clienteDAO.selectAll();
						mostrarClientes();
						if (cli.size()==0) {
							System.out.println("Nenhum cliente cadastrado!");
							break;
						}
						System.out.println("Selecione o id do cliente a ser cadastrado:");
						int num2 = Integer.parseInt(s.nextLine());
						
						System.out.println("Digite a data da compra");
						String text = s.nextLine();
						
						principal.compraDAO.insert(num1, num2, text);
						
					} catch (Exception e) {
						e.getMessage();
					}
					
					break;
				case 6:
					try {
						List<Imovel> imo= principal.imovelDAO.selectAll();
						mostrarImoveis();
						if (imo.size() == 0) {
							System.out.println("Nenhum imóvel cadastrado!");
							break;
						}
						System.out.println("Selecione o id do imóvel a ser cadastrado:");
						int num1 = Integer.parseInt(s.nextLine());
						
						List<Cliente> cli= principal.clienteDAO.selectAll();
						mostrarClientes();
						if (cli.size()==0) {
							System.out.println("Nenhum cliente cadastrado!");
							break;
						}
						System.out.println("Selecione o id do cliente a ser cadastrado:");
						int num2 = Integer.parseInt(s.nextLine());
						
						System.out.println("Digite a data do início do contrato");
						String text1 = s.nextLine();
						
						System.out.println("Digite a data do término do contrato");
						String text2 = s.nextLine();
						
						principal.aluguelDAO.insert(num1, num2, text1, text2);
						
					} catch (Exception e) {
						e.getMessage();
					}	
					break;
				case 7:
					try {
						List<Imovel> imoveis = principal.imovelDAO.selectAll();
						
						for (Imovel i : imoveis) {
							if (i!=null) {
								System.out.println(i.getId() + " " + i.getArea() + " " + i.getPreco() + " " + i.getDescricao() + " " + i.getCep());
							}
						}
					} catch (SelectException e) {
						e.getMessage();
					}		
					break;
				case 8:
					try {
						List<Proprietario> props = principal.proprietarioDAO.selectAll();
						
						for (Proprietario p : props) {
							if (p!=null) {
								System.out.println(p.getId() + " " + p.getNomeprop() + " " + p.getTelefone());
							}
						}
					} catch (SelectException e) {
						e.getMessage();
					}				
					break;
				case 9:
					try {
						List<Cliente> clientes = principal.clienteDAO.selectAll();
						
						for (Cliente c : clientes) {
							if (c!=null) {
								System.out.println(c.getId() + " " + c.getNomecliente() + " " + c.getTelefone());
							}
						}
					} catch (SelectException e) {
						e.getMessage();
					}						
					break;
				case 10:
					try {
						List<Imovel> imoveis = principal.imovelDAO.selectMenores();
						
						for (Imovel i : imoveis) {
							if (i!=null) {
								System.out.println(i.getId() + " " + i.getArea() + " " + i.getPreco() + " " + i.getDescricao() + " " + i.getCep());
							}
						}
					} catch (SelectException e) {
						e.getMessage();
					}
					break;
				case 11:
				try {
					List<Cliente> vips = principal.clienteDAO.selectAllVips();
					for (Cliente v : vips) {
						if (v!=null) {
							System.out.println(v.getId() + " " + v.getNomecliente() + " " + v.getTelefone());
						}
					}
				} catch (SelectException e) {
					e.getMessage();
				}
					break;
				case 12:
					break;
				default:
					System.out.println("Digite certo da próxima vez!");
					break;				
				}
			}
		} catch (ClassNotFoundException e1) {
			e1.printStackTrace();
		} catch (SQLException e1) {
			e1.printStackTrace();
		}
	}
		
		public Principal (String senha) throws SQLException, ClassNotFoundException {
			Conexao.setSenha(senha);
			clienteDAO = ClienteDAO.getInstance();
			imovelDAO = ImovelDAO.getInstance();
			proprietarioDAO = ProprietarioDAO.getInstance();
			aluguelDAO = AluguelDAO.getInstance();
			compraDAO = CompraDAO.getInstance();
		}
		
		public static void mostrarImoveis () throws SelectException {
			List<Imovel> temp= principal.imovelDAO.selectAll();
			if (temp==null) {
				System.out.println("Nenhum imóvel cadastrado");
			} else {
				System.out.println("Lista de Imóveis:");
				for (Imovel i : temp ) {
					if (i!= null) {
						System.out.println(i.getId() + " " + i.getArea() + " " + i.getPreco() + " " + i.getDescricao() + " " + i.getCep());
					}
				}	
			}
			
		}
		
		public static void mostrarProprietarios () throws SelectException {
			List<Proprietario> temp= principal.proprietarioDAO.selectAll();
			if (temp==null) {
				System.out.println("Nenhum proprietário cadastrado");
			} else {
				System.out.println("Lista de Proprietários: ");
				for (Proprietario i : temp ) {
					if (i!= null) {
						System.out.println(i.getId() + " " + i.getNomeprop() + " " + i.getTelefone());
					}
				}	
			}
			
		}
		
		public static void mostrarClientes () throws SelectException {
			List<Cliente> temp= principal.clienteDAO.selectAll();
			if (temp==null) {
				System.out.println("Nenhum cliente cadastrado");
			} else {
				System.out.println("Lista de Clientes: ");
				for (Cliente c : temp ) {
					if (c!= null) {
						System.out.println(c.getId() + " " + c.getNomecliente() + " " + c.getTelefone());
					}
				}	
			}
			
		}
}
