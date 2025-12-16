#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100
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
int excluir_por_nome();
int existe();
int existe2(char nome1[], char nome2[]);
void listagem_geral();
void listagem_nome();
void niver_mes(int mes);
void niver_dia(int dia, int mes);

char buscanome(char texto);
int i,mes_niver;


int inicio=0;
int fim=0;

int main ()
{
setlocale(LC_ALL, "Portuguese");
int escolha;


do{
 do{
  system("cls");
  printf("\n    Olá, bem vindo ao programa SUA AGENDA! \n\n    Para prosseguir, escolha um dos itens abaixo:\n");
  printf("\n 1 - Cadastrar novas pessoas na agenda");
  printf("\n 2 - Listagem de todos os nomes da agenda");
  printf("\n 3 - Buscar dados de uma pessoa específica");
  printf("\n 4 - Pesquisar os aniversariantes do mês");
  printf("\n 5 - Pesquisar os aniversariantes do dia");
  printf("\n 6 - Deletar Pessoa Específica da Agenda");
  printf("\n 7 - Sair do Programa.\n");
  scanf("%d", &escolha);
  if ((escolha!=1)&&(escolha!=2)&&(escolha!=3)&&(escolha!=4)&&(escolha!=5)&&(escolha!=6)&&(escolha!=7))
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
                    printf("\n Digite o mês desejado (1 para janeiro, 2 para fevereiro assim por diante): \n\n");
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
                       niver_dia(nv_dia, nv_mes);
                    
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
        
        case 7:{ printf("\n Obrigado por utilizar o programa SUA AGENDA! Agradecemos a preferência!");
                system("pause"); 
              }                             
      } // FIM DO switch
 
}while(escolha!=7); 
return 0;	
}//Fim do Programa

//====================================================
// Área das Funções
//====================================================

//função inserir nova pessoa na agenda
int leituradados()
{
//o ponteiro pes aponta para a struct pessoa, onde os dados serão armazenados
 struct pessoa *p = (struct pessoa *) malloc (sizeof(struct pessoa));

 if (fim==MAX) 
 { printf("\n  Agenda Cheia!"); 
   return 0;
 }
 printf("\n Digite o nome: ");
 fflush(stdin);
 do {fgets(p->nome,150,stdin);} while( (strlen(p->nome) < 1) == TRUE);
 fflush(stdin);
 printf("\n Digite o e-mail: ");
 do {fgets(p->email,150,stdin);} while( (strlen(p->email) < 1) == TRUE);
 fflush(stdin);
 printf("\n Digite a data de nascimento(formato DD/MM/AAAA):");
 printf("\n Informe o dia: ");
 scanf("%d",&p->Data.dia);
 printf("\n Informe o mês: ");
 scanf("%d",&p->Data.mes);
 printf("\n Informe o ano: ");
 scanf("%d",&p->Data.ano);
 printf("\n Digite o telefone:");
 printf("\nInforme o DDD do telefone: ");
 scanf("%d",&p->telefone.ddd);
 printf("\nInforme o número do telefone: ");
 scanf("%s",&p->telefone.tel);
 printf("\nDigite o endereço:");
 printf("\nInforme o país: ");
 do {gets(p->endereco.pais);} while((strlen(p->endereco.pais) < 1) == TRUE);
 printf("\nInforme o estado: ");
 do {gets(p->endereco.estado);} while((strlen(p->endereco.estado) < 1) == TRUE);
 printf("\nInforme a cidade: ");
 do {gets(p->endereco.cidade);} while( (strlen(p->endereco.cidade) < 1) == TRUE);
 printf("\nInforme o bairro: ");
 do {gets(p->endereco.bairro);} while( (strlen(p->endereco.bairro) < 1) == TRUE);
 printf("\nInforme o CEP: ");
 do {gets(p->endereco.cep);} while( (strlen(p->endereco.cep) < 1) == TRUE);
 printf("\nInforme a rua: ");
 do {gets(p->endereco.rua);} while( (strlen(p->endereco.rua) < 1) == TRUE);
 printf("\nInforme o número: ");
 do {gets(p->endereco.numero);} while( (strlen(p->endereco.numero) < 1) == TRUE);
 printf("\nInforme o complemento: ");
 do {gets(p->endereco.complemento);} while( (strlen(p->endereco.complemento) < 1) == TRUE);
 p->status=1;
 Pessoa[fim]=p;
 fim++;

}//fim função leituradados()

int vazia()
{
	  if (fim==inicio) {return TRUE;}
	  else {return FALSE;};
}


//função excluir por nome - exclusão lógica
int excluir_por_nome()
{
 char novo_nome[150];
 char resp;
 int i,encontrei=0,cont=0;
 printf("\n Informe o nome da Pessoa que deseja Deletar: ");
 scanf("%s",novo_nome);
 fflush(stdin);
 
 
 struct pessoa *mostra;
 	 
	 

 	 	for(i=0;i<fim;i++)
     	{
     		mostra = Pessoa[i];
     	if ((existe(novo_nome,mostra->nome)==1)&&(mostra->status==1))
     		{
       		printf("\n Contato identificado: %s", mostra->nome);
      		printf("\n DESEJA EXCLUIR? [S] ou [N]");
      		scanf("%c",&resp);
       		fflush(stdin);
       		cont++;
       		if ((resp=='S')||(resp=='s'))
       		{
	       	mostra->status=0;
       		}
       		break;
    		}
		}
if 	(cont<1)
		 	{printf("Nenhum contato com esse nome foi encontrado.");
	 		return 0;
	 		}
}

//listagem pelo nome
void listagem_nome()
	{
	 struct pessoa *mostra;
	  
	 int i,encontrei=0,cont2=0;
	 char novo_nome[150];
	 printf("\n\n\nBusca de dados pelo nome:");
	 printf("\n Informe o nome da Pessoa que deseja Mostrar: ");
     scanf("%s", novo_nome);
     fflush(stdin);

	 
	 for (i = 0; i < fim; i++)
	 {
	mostra = Pessoa[i];
	
	 if (existe(novo_nome,mostra->nome)==1&&mostra->status==1)
	    {
	     cont2++; 	
    	}
     }
	 
	 for (i =0; i < fim; i++)
	 { 
	 mostra = Pessoa[i];
	 if (existe(novo_nome,mostra->nome)==1&&mostra->status==1)
	    {
	     
	 		printf("\n ENCONTREI: ");
	   		printf("\nNome: %s ", mostra->nome);
			printf("\nEmail: %s ", mostra->email);
			printf("\nTelefone: (%d) %s ", mostra->telefone.ddd, mostra->telefone.tel);   
	 		break;
    	}
     }
     
}	
// listagem de todos os Nomes Cadastrados na Agenda.
void listagem_geral()
	{
		
	 struct pessoa *mostra;
	 int quantidade = 0,i;
	 printf("\n\n\n*** Pessoas da Agenda:\n");
	 for (i = inicio; i < fim; i++)
	 { 
	 mostra = Pessoa[i];
	 	if (mostra->status==1)
		{
		
	   	printf("%s ", mostra->nome);
	   	quantidade++;
		}
	 }
	printf("\n\n === Total de Pessoas Cadastradas na Agenda: %i.  ===\n\n\n" ,quantidade);
	}
	
//Aniversariantes do mes
void niver_mes(int mes)
{
	struct pessoa *mostra;
	 int quantidade=0,i;
	 printf("\n\n\n*** Aniversariantes do Mês %i: ", mes);
	 for (i = inicio; i < fim; i++)
	 { 
	   mostra = Pessoa[i];
	   if ((mostra->Data.mes==mes)&&(mostra->status==1))
	    {
	   	printf("\n%s ", &mostra->nome);
	    quantidade++;
	   }
	   
	 }

}

//aniversariantes do dia
void niver_dia(int dia, int mes)
{
    struct pessoa *mostra;
	 int quantidade=0,i;
	 printf("\n\n\n*** Aniversariantes do dia:  %i / %i: ",dia,mes);
	 for (i = inicio; i < fim; i++)
	 { 
	   mostra = Pessoa[i];
	   if ((mostra->Data.dia==dia) && (mostra->Data.mes==mes) && (mostra->status==1))
	    {
	   	printf("\n%s ", &mostra->nome);
	    quantidade++;
	   }
	   
	 }
	
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
