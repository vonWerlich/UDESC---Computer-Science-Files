#include <stdio.h>
#include <locale.h>
#include <string.h>

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
	
struct 
{
    char nome[150];
    char email[150];
    dt_nasc Data;
    num_tel telefone;
    end endereco;
    int status;
} pessoa;	

int leituradados();

char buscanome(char texto);

int main ()
{
setlocale(LC_ALL, "Portuguese");
	
int escolha;

printf("Olá, bem vindo ao programa Sua_Agenda!\nPara prosseguir, digite:");
printf("\n1 - para cadastrar novas pessoas na agenda;");
printf("\n2 - para buscar pessoas na agenda de acordo com o nome;");
printf("\n3 - para buscar os aniversariantes do mês;");
printf("\n4 - para buscar os aniversariantes do dia;");
printf("\n5 - para apagar uma pessoa da agenda.\n");
scanf("%d", &escolha);

if ((escolha!=1)&&(escolha!=2)&&(escolha!=3)&&(escolha!=4)&&(escolha!=5))
  {
    printf("\n\n\a DIGITE CERTO DA PROXIMA VEZ \n");
    system("pause");
  }  
 while ((escolha!=1)&&(escolha!=2)&&(escolha!=3)&&(escolha!=4)&&(escolha!=5)&&(escolha!=6)&&(escolha!=7)&&(escolha!=8));
      
switch (escolha){
       case 1: {
                	system("cls");
                    printf("\n CADASTRO DE PESSOAS \n\n");
                    leituradados();
                    system("pause");
                    break;
                 }
                          
      } // FIM DO switch


return 0;	
}

//função inserir nova pessoa na agenda
int leituradados()
{
int num_pessoas,i;

for (i=0;i<num_pessoas;i++)
{
char a[100],b[100],c[100],d[100],e[100],f[100];
printf("Digite o nome: ");
fgets(pessoa.nome,150,stdin);
printf("\nDigite o e-mail: ");
scanf("%ls",pessoa.email);
fflush(stdin);
printf("\nDigite a data de nascimento(formato DD/MM/AAAA):");
printf("\nInforme o dia: ");
scanf("%d",&pessoa.Data.dia);
printf("\nInforme o mês: ");
scanf("%d",&pessoa.Data.mes);
printf("\nInforme o ano: ");
scanf("%d",&pessoa.Data.ano);
printf("\nDigite o telefone:");
printf("\nInforme o DDD do telefone: ");
scanf("%d",&pessoa.telefone.ddd);
printf("\nInforme o número do telefone: ");
scanf("%ls",pessoa.telefone.tel);
fflush(stdin);
printf("\nDigite o endereço:");
printf("\nInforme o país: ");
fgets(pessoa.endereco.pais,50,stdin);
printf("\nInforme o estado: ");
fgets(pessoa.endereco.estado,50,stdin);
printf("\nInforme a cidade: ");
fgets(pessoa.endereco.cidade,60,stdin);
printf("\nInforme o bairro: ");
fgets(pessoa.endereco.bairro,50,stdin);
printf("\nInforme o CEP: ");
fgets(pessoa.endereco.cep,15,stdin);
printf("\nInforme a rua: ");
fgets(pessoa.endereco.rua,50,stdin);
printf("\nInforme o número: ");
fgets(pessoa.endereco.numero,10,stdin);
printf("\nInforme o complemento: ");
fgets(pessoa.endereco.complemento,50,stdin);
pessoa.status=1;
}

}

char buscanome(char texto)
{
}
