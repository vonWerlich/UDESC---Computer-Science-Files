#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
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
int deletar();
int existe (char palavra[], char frase[]);
void excluir_por_nome();
void listagem_geral();
void listagem_nome();
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


do{
 do{
  system("cls");
  printf("\n    Olá, bem vindo ao programa Sua Agenda! \n\n    Para prosseguir, escolha um dos itens abaixo:\n");
  printf("\n 1 - Cadastrar novas pessoas na agenda");
  printf("\n 2 - Listagem de todos os nomes da agenda");
  printf("\n 3 - Buscar dados de uma pessoa específica");
  printf("\n 4 - Pesquisar os aniversariantes do mês");
  printf("\n 5 - Pesquisar os aniversariantes do dia");
  printf("\n 6 - Deletar Definitivamente a 1a Pessoa da Agenda");
  printf("\n 7 - Deletar Pessoa Específica da Agenda");
  printf("\n 8 - Sair do Programa.\n");
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
					system("cls");
                    listagem_geral();
                    printf("\n\n");
				    system("pause");
                    break;
                 }  
		case 3:  {
					system("cls");
					listagem_nome();
					system("pause");
					break;
				}		  
		case 4: {
                    system("cls");
                    printf("\n Aniversariantes do Mês \n\n");
                    printf("\n Qual é o Mês Desejado? \n\n");
                    scanf("%d", &mes_niver);
                    niver_mes(mes_niver);
                    system("pause");
                    break;
                }      
                 
        case 5: {
                    system("cls");
					int resp,nv_dia,nv_mes; 
					   printf("\n Informe a data do Aniversário: \n\n");
                       printf("\n Qual é o Dia Desejado? \n\n");
                       scanf("%d", &nv_dia);
                       printf("\n Qual é o Mês Desejado? \n\n");
                       scanf("%d", &nv_mes);
                       niver_hj(nv_dia, nv_mes);
                    
                    system("pause");
                    break;
                }        
        case 6: {
                    system("cls");
                    printf("\n Deletar Definitivamente a 1a Pessoa da Agenda \n\n");
                    deletar();
                    system("pause");
                   break;
                 }
        
        case 7: {
                    system("cls");
                    printf("\n Deletar logicamente uma Pessoa da Agenda \n\n");
                    excluir_por_nome();
                    system("pause");
                    break;
                }
        case 8:{ printf("\n Obrigado por utilizar o programa Sua Agenda! Agradecemos a preferência!");
                system("pause"); 
              }                             
      } // FIM DO switch
 
}while(escolha!=8); 
return 0;	
}//Fim do Programa

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


int vazia()
{
	  if (fim==inicio) {return TRUE;}
	  else {return FALSE;};
}



//função excluir por nome - exclusão lógica
void excluir_por_nome()
{
 //struct pessoa *procura = (struct pessoa *) malloc (sizeof(struct pessoa));
 char novo_nome[150];
 char resp;
 int i;
 printf("\n Informe o nome da Pessoa que deseja Deletar:   ");
 fflush(stdin);
 fgets(novo_nome,150,stdin);
 fflush(stdin);
 for(i=0;i<MAX;i++)
     {
     if (strcmpi(Pessoa[i]->nome,novo_nome)==0)
     {
       printf("\n ALUNO ENCONTRADO");
       printf("\n DESEJA EXCLUIR? [S] ou [N]");
       scanf("%c",&resp);
       fflush(stdin);
       if ((resp=='S')||(resp=='s'))
       {
	       free(Pessoa[i]);
       }
    }
    
}
} //fim

// listagem pelo nome
void listagem_nome()
	{
	 struct pessoa *mostra;
	 int i, encontrei=0;
	 char novo_nome[150];
	 printf("\n\n\nBusca de dados pelo nome:");
	 printf("\n Informe o nome da Pessoa que deseja Mostrar: ");
    fflush(stdin);
	 fgets(novo_nome,150,stdin);
     fflush(stdin);
	 
     for (i = inicio; i < fim; i++)
	 { mostra = Pessoa[i];
	 
	 if (existe(novo_nome,mostra->nome)==1)
	   {
	     encontrei = 1;
        break;
        }
     }
     if (encontrei == 1) 
	 {
	 	 printf("\n ENCONTREI: ");
	    printf("\nNome: %s ", mostra->nome);
		printf("\nEmail: %s\n ", mostra->email);	   
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
	 printf("\n\n === Total de Aniversariantes: %d aniversariante(s) do dia %d / %d.  ===\n\n\n" ,quantidade,dia,mes);	
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
	 printf("\n\n === Total de Aniversariantes: %i aniversariante(s) do Mês: %i.  ===\n\n\n" ,quantidade,mes);	
	
}


//função auxiliar para buscar string em string
int testar (int teste [], int tam)
{
int i;
	for (i=0;i<tam;i++)
	{
	if (teste[i]==0)
	{return 0;}	
	}
	return 1;
}

//função para buscar string em string
int existe (char palavra[], char frase[])
{
	int teste [ strlen(palavra) ];
	int aux,i,k,j;
	
	if (strlen(palavra) > strlen(frase))
	{return 0;}
	 
	if (strcmpi(palavra,frase)==0)
	{return 1;} 
	
	for (i=0; i<(strlen(frase)-strlen(palavra)); i++)
	{if (frase[i]==palavra[0])
	
		for (k=0;k<strlen(palavra);k++)
		{
		teste[k]=0;
		}
		
		aux=i;
		for (j=0;j<strlen(palavra);j++)
		{
		if (palavra[j]==frase[aux])
		{
		teste[j]=1;
		aux++;
		}
		
		if (testar (teste,strlen(palavra)))
		{
		return 1;	
		}
		
		
		
		}
	}
	
	return 0;
	
}
//função para comparar strings alterada para verificar se já existe o contato na agenda
int existe2 (char nome1[], char nome2[])
{
	
	if (strcmpi(nome1,nome2)==0)
	{return 1;}
	else
	{return 0;
	}
	
}
