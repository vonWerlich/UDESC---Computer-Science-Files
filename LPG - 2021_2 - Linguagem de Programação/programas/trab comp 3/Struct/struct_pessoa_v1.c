#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <time.h>

#define MAX 10
#define TRUE 1
#define FALSE 0
	
typedef struct 
{int dia,mes,ano;
} dt_nasc;
	
typedef struct
{int ddd;
char tel[10];
} num_tel;
	
typedef struct
{char pais[50],estado[50],cidade[60],cep[15],bairro[50],rua[50],numero[10],complemento[50];
} end;
	
struct pessoa
{
    char nome[150];
    char email[150];
    dt_nasc Data;
    num_tel telefone;
    end endereco;
    int status;
} *Pessoa[MAX];
	
int leituradados();
int vazia();
void deletar();
void excluir_por_nome();
void listagem_geral();
void listagem_nome(struct pessoa *p);
void niver_mes(int mes);
void niver_hj(int dia, int mes);
void niver_dia(int dia, int mes);

char buscanome(char texto);
int i,mes_niver;


int inicio=0;
int fim=0;

int main ()
{
setlocale(LC_ALL, "Portuguese");
time_t dt_hoje;
dt_hoje = time(NULL);
struct tm tm = *localtime(&dt_hoje);
int escolha;

/*struct pessoa * p;

p = (struct pessoa *) malloc(sizeof(struct pessoa));*/
do{
 do{
  system("cls");
  printf("\n Olá, bem vindo ao programa Sua_Agenda.\n\nPara prosseguir, escolha um item:\n");
  printf("\n1 - Cadastrar novas pessoas na agenda");
  printf("\n2 - Relatórios");
  printf("\n3 - Pesquisar os aniversariantes do mês");
  printf("\n4 - Pesquisar os aniversariantes do dia");
  printf("\n5 - Deletar Definitivamente a 1a Pessoa da Agenda");
  printf("\n6 - Deletar Pessoa Específica da Agenda");
  printf("\n7 - Restaurar arquivos excluídos");
  printf("\n8 - Sair do Programa.\n");
  scanf("%d", &escolha);
  if ((escolha!=1)&&(escolha!=2)&&(escolha!=3)&&(escolha!=4)&&(escolha!=5)&&(escolha!=6)&&(escolha!=7)&&(escolha!=8))
  {
    printf("\n\n\a DIGITE CERTO DA PROXIMA VEZ \n");
    system("pause");
  }  
 }while ((escolha!=1)&&(escolha!=2)&&(escolha!=3)&&(escolha!=4)&&(escolha!=5)&&(escolha!=6)&&(escolha!=7)&&(escolha!=8));
      
switch (escolha){
       case 1: {
                    system("cls");
                    printf("\n CADASTRO DE PESSOAS \n\n");
                    leituradados();
                    system("pause");
                   break;
                 }
        case 2: {
                    int resp;
					system("cls");
                    printf("\n ÁREA DE RELATÓRIOS \n\n");
                    printf("\n Escolha um dos Relatórios: \n\n");
                    printf("\n [1] LISTAGEM DOS NOMES \n\n");
                    printf("\n [2] LISTAGEM DOS DADOS DE UMA PESSOA \n\n");
                    scanf("%d", &resp);
                    if (resp==1)
                        listagem_geral();
                    if (resp==2)
                        listagem_nome(Pessoa);
                
				   system("pause");
                   break;
                 }   
		case 3: {
                    system("cls");
                    printf("\n Aniversariantes do Mês \n\n");
                    printf("\n Qual é o Mês Desejado? \n\n");
                    scanf("%d", &mes_niver);
                    niver_mes(mes_niver);
                    system("pause");
                    break;
                }      
                 
        case 4: {
                    system("cls");
					int resp,nv_dia,nv_mes;
                    printf("\n Escolha um dos Tipos de Pesquisa: \n\n");
                    printf("\n [1] Pesquisa por Data de Aniversário \n\n");
                    printf("\n [2] Aniversariantes de Hoje \n\n");
                    scanf("%d", &resp);
                    if (resp==1)
                    {  
					   printf("\n Informe a data do Aniversário: \n\n");
                       printf("\n Qual é o Dia Desejado? \n\n");
                       scanf("%d", &nv_dia);
                       printf("\n Qual é o Mês Desejado? \n\n");
                       scanf("%d", &nv_mes);
                       niver_hj(nv_dia, nv_mes);
                    }
                                            
                    if (resp==2)
                    {
					   printf("\n Aniversariantes de Hoje \n\n");
                       printf("\n Hoje é dia:  ");
					   printf(" %d/%d/%d \n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
                       niver_hj(tm.tm_mday, tm.tm_mon);
                    }
                    system("pause");
                    break;
                }        
        case 5: {
                    system("cls");
                    printf("\n Deletar Definitivamente a 1a Pessoa da Agenda \n\n");
                    deletar();
                    system("pause");
                   break;
                 }
        
       case 6: {
                    system("cls");
                    printf("\n Deletar logicamente uma Pessoa da Agenda \n\n");
                    excluir_por_nome();
                    system("pause");
                    break;
                }
       case 8:{ printf("\n Obrigado Por Utilizar o Programa");
                printf("\n\n Aguarde Melhorias \n\n");
                system("pause"); 
              }                             
      } // FIM DO switch
 
}while(escolha!=8); 




return 0;	
}





//====================================================
// Área das Funções
//====================================================

//função inserir nova pessoa na agenda
int leituradados()
{
 struct pessoa *pes = (struct pessoa *) malloc (sizeof(struct pessoa));
 if (fim==MAX) 
 { printf("\n  Agenda Cheia!"); 
   return 0;
 }
 printf("\n Digite o nome: ");
 do {gets(pes->nome);} while( (strlen(pes->nome) < 1) == TRUE);
 printf("\n Digite o e-mail: ");
 do {gets(pes->email);} while( (strlen(pes->email) < 1) == TRUE);
 printf("\n Digite a data de nascimento(formato DD/MM/AAAA):");
 printf("\n Informe o dia: ");
 scanf("%d",&pes->Data.dia);
 printf("\n Informe o mês: ");
 scanf("%d",&pes->Data.mes);
 printf("\n Informe o ano: ");
 scanf("%d",&pes->Data.ano);
 printf("\n Digite o telefone:");
 printf("\nInforme o DDD do telefone: ");
 scanf("%d",&pes->telefone.ddd);
 printf("\nInforme o número do telefone: ");
 scanf("%ls",&pes->telefone.tel);
 printf("\nDigite o endereço:");
 printf("\nInforme o país: ");
 do {gets(pes->endereco.pais);} while((strlen(pes->endereco.pais) < 1) == TRUE);
 printf("\nInforme o estado: ");
 do {gets(pes->endereco.estado);} while((strlen(pes->endereco.estado) < 1) == TRUE);
 printf("\nInforme a cidade: ");
 do {gets(pes->endereco.cidade);} while( (strlen(pes->endereco.cidade) < 1) == TRUE);
 printf("\nInforme o bairro: ");
 do {gets(pes->endereco.bairro);} while( (strlen(pes->endereco.bairro) < 1) == TRUE);
 printf("\nInforme o CEP: ");
 do {gets(pes->endereco.cep);} while( (strlen(pes->endereco.cep) < 1) == TRUE);
 printf("\nInforme a rua: ");
 do {gets(pes->endereco.rua);} while( (strlen(pes->endereco.rua) < 1) == TRUE);
 printf("\nInforme o número: ");
 do {gets(pes->endereco.numero);} while( (strlen(pes->endereco.numero) < 1) == TRUE);
 printf("\nInforme o complemento: ");
 do {gets(pes->endereco.complemento);} while( (strlen(pes->endereco.complemento) < 1) == TRUE);
 pes ->status=1;
 Pessoa[fim]=pes;
 fim++;

}//fim função leituradados()

char buscanome(char texto)
{
}

int vazia()
{
	  if (fim==inicio) {return TRUE;}
	  else {return FALSE;};
}

// funçao que Deleta a 1a Pessoa Incluída na Agenda
void deletar()
	{
	 struct pessoa *saida = (struct pessoa *) malloc(sizeof(struct pessoa));
	
	if (vazia()) 
	{printf("\n  A Agenda esta Vazia!"); 
	 return 0;
	}
	else
	{
	  saida = Pessoa[inicio];
	  inicio++;
	}
	  printf("\n*** Foi Deletado a seguinte Pessoa:");
	  printf(" %s ",saida->nome);
	  free(saida);
	}
// fim deletar()

//função excluir por nome - exclusão lógica
void excluir_por_nome()
{
 //struct pessoa *procura = (struct pessoa *) malloc (sizeof(struct pessoa));
 char novo_nome[45];
 char resp;
 int i;
 printf("\n Informe o nome da Pessoa que deseja Deletar:   ");
 //fgets(novo_nome,150,stdin);
 scanf("%ls",novo_nome);
 fflush(stdin);
 for(i=0;i<MAX;i++)
     {
    // if (strcmpi(procura->nome,novo_nome)==0)
     if (strcmpi(Pessoa[i]->nome,novo_nome)==0)
     {
       printf("\n ALUNO ENCONTRADO");
       printf("\n DESEJA EXCLUIR? [S] ou [N]");
       scanf("%c",&resp);
       fflush(stdin);
       if ((resp=='S')||(resp=='s'))
       {
	     //procura = Pessoa[i];
         free(Pessoa[i]);
       }
    }
    
}
} //fim

// listagem dos dados de Uma Pessoa Específica da Agenda.
	void listagem_nome(struct pessoa *p)
	{
	 //struct pessoa *mostra;
	 int i, encontrei=0;
	 char novo_nome[45];
	 printf("\n\n\n*** Pessoas da Agenda:");
	 printf("\n Informe o nome da Pessoa que deseja Mostrar:   ");
     scanf("%s",novo_nome);
     fflush(stdin);
	 for (i = inicio; i < fim; i++)
	 { 
	  if (strcmpi(*p[i].nome,novo_nome)==0)
	   {
	     encontrei = 1;
         break;
        }
     }
     if (encontrei == 1) 
	 {
	 	 printf("\n ENCONTREI");
	 	 printf("\n%s ", *p[i].nome);
	     printf("\n%s ", *p[i].email);
	     
	 }
}
	
	
// listagem de todos os Nomes Cadastrados na Agenda.
void listagem_geral()
	{
		
	 struct pessoa *mostra;
	 int quantidade = 0,i;
	 printf("\n\n\n*** Pessoas da Agenda:");
	 for (i = inicio; i < fim; i++)
	 { mostra = Pessoa[i];
	   printf("\n%s ", &mostra->nome);
	   quantidade++;
	 }
	printf("\n\n === Total de Pessoas Cadastradas na Agenda: %i.  ===\n\n\n" ,quantidade);
	}
	
// Aniversariantes do mes
void niver_mes(int mes)
{
	struct pessoa *mostra;
	 int quantidade=0,i;
	 printf("\n\n\n*** Aniversariantes do Mês %i: ", mes);
	 for (i = inicio; i < fim; i++)
	 { 
	   mostra = Pessoa[i];
	   if (mostra->Data.mes==mes)
	    {
	   	printf("\n%s ", &mostra->nome);
	    quantidade++;
	   }
	   
	 }
	 printf("\n\n === Total de Aniversariantes: %i   do Mês: %i.  ===\n\n\n" ,quantidade,mes);
}
// Aniversariantes de Hoje - Usando a Data do Sistema
void niver_hj(int dia, int mes)
{
    struct pessoa *mostra;
	 int quantidade=0,i;
	 printf("\n\n\n*** Aniversariantes do dia:  %i / %i: ",dia,mes);
	 for (i = inicio; i < fim; i++)
	 { 
	   mostra = Pessoa[i];
	   if ((mostra->Data.dia==dia) && (mostra->Data.mes==mes))
	    {
	   	printf("\n%s ", &mostra->nome);
	    quantidade++;
	   }
	   
	 }
	 printf("\n\n === Total de Aniversariantes: %i   do Mês: %i.  ===\n\n\n" ,quantidade,mes);	
}
void niver_dia(int dia, int mes)
{
     struct pessoa *mostra;
	 int quantidade=0,i;
	 printf("\n\n\n*** Aniversariantes do dia:  %i / %i: ",dia,mes);
	 for (i = inicio; i < fim; i++)
	 { 
	   mostra = Pessoa[i];
	   if ((mostra->Data.dia==dia) && (mostra->Data.mes==mes))
	    {
	   	printf("\n%s ", &mostra->nome);
	   	
	    quantidade++;
	   }
	 }
	 printf("\n\n === Total de Aniversariantes: %i   do Mês: %i.  ===\n\n\n" ,quantidade,mes);	
	
}
