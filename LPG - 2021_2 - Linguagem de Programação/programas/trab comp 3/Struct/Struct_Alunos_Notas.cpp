#include <iostream>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <stdio.h>

using namespace std;

  /*Criando a struct */
  
struct dados_aluno
  {
    char nome[50];
    char disciplina[50];
    float nota_prova1;
    float nota_prova2;
    float nota_prova3;
    float nota_prova4;
    float media_nota;
    int situacao;
    int idade;
  };

dados_aluno Aluno [5];
int i;
int j;
int op;
char pornome[50];
int porsituacao;
char pordisciplina[50];
main()
{

  /*Criando a variável aluno que será do
  tipo struct dados_aluno */
  setlocale(LC_ALL, "Portuguese");
  cout<<" \n---------- Cadastro de Alunos -----------\n\n\n";
  for (i=0; i<5;i++)
  {
  cout<<"\n \n Informe os dados do:  "<<i+1<< "º Aluno";
  cout<<"\n Nome do aluno ......: ";
  fflush(stdin); //Para limpar o buffer em Windows, use o: fflush(stdin) 
 
  gets(Aluno[i].nome);
  
  cout<<" \n Disciplina ......: ";
  fflush(stdin);
  gets(Aluno[i].disciplina);
  cout<<"\nInforme a Idade do Aluno ..: ";
  cin>>Aluno[i].idade;
  cout<<"\nInforme a 1a. nota ..: ";
  
  do
  {
  	cin>>Aluno[i].nota_prova1;
  	if (Aluno[i].nota_prova1<0 || Aluno[i].nota_prova1>10 )
  	{
  	cout<<"\n Favor digitar notas entre 0 e 10";
	cout<<"\n Favor digitar novamente a nota da prova 1 :   ";
  	cin>>Aluno[i].nota_prova1;	 	  	
	  }
  }while (Aluno[i].nota_prova1<0 || Aluno[i].nota_prova1>10 );
  
  
  cout<<"\nInforme a 2a. nota ..: ";
  
    do
  {
  cin>>Aluno[i].nota_prova2;
    if (Aluno[i].nota_prova2<0 || Aluno[i].nota_prova2>10 )
  	{
  	cout<<"\n Favor digitar notas entre 0 e 10";
	cout<<"\n Favor digitar novamente a nota da prova 2 :   ";
  	cin>>Aluno[i].nota_prova2;	 	  	
	}
  }while (Aluno[i].nota_prova2<0 || Aluno[i].nota_prova2>10 );
  
  
  
  
  cout<<"\nInforme a 3a. nota ..: ";
  
  
      do
  {
  cin>>Aluno[i].nota_prova3;
if (Aluno[i].nota_prova3<0 || Aluno[i].nota_prova3>10 )
  	{
  	cout<<"\n Favor digitar notas entre 0 e 10";
	cout<<"\n Favor digitar novamente a nota da prova 3 :   "; 
  	cin>>Aluno[i].nota_prova3;	 	
	  }
  }while (Aluno[i].nota_prova3<0 || Aluno[i].nota_prova3>10 );
  
  
  
  cout<<"\nInforme a 4a. nota ..: ";
        do
  {
  cin>>Aluno[i].nota_prova4;
  if (Aluno[i].nota_prova4<0 || Aluno[i].nota_prova4>10 )
  	{
  	cout<<"\n Favor digitar notas entre 0 e 10";
	cout<<"\n Favor digitar novamente a nota da prova 4 :   ";
  	cin>>Aluno[i].nota_prova4;	  	
	  }
  }while (Aluno[i].nota_prova4<0 || Aluno[i].nota_prova4>10 );
 }
 
 
   for (i=0; i<5;i++)
   {
   	Aluno[i].media_nota=(Aluno[i].nota_prova1+Aluno[i].nota_prova2+Aluno[i].nota_prova3+Aluno[i].nota_prova4)/4;	
   }
 
   for (i=0; i<5;i++)
   {
   	if (Aluno[i].media_nota>=7)	
	{
   	Aluno[i].situacao=1;	
    }
    else
    {
    Aluno[i].situacao=0;
	}
   }
 
 
 
 
 
 
  cout<<"\n\n --------------------------------------------------";
  cout<<"\n\n --------- IMPRIMINDO os dados da struct ---------";
  for (i=0; i<5;i++)
  {
  cout<<"\n\n ____________________________________________________";
  cout<<"\n\n Nome ...........:";
  puts (Aluno[i].nome);
  cout<<"\n Disciplina .....: ";
  puts(Aluno[i].disciplina);
  cout<<"\n Idade do Aluno ...: " << Aluno[i].idade;
  cout<<"\n Nota da Prova 1 ...: " << Aluno[i].nota_prova1;
  cout<<"\n Nota da Prova 2 ...: " << Aluno[i].nota_prova2;
  cout<<"\n Nota da Prova 3 ...: " << Aluno[i].nota_prova3;
  cout<<"\n Nota da Prova 4 ...: " << Aluno[i].nota_prova4;
  cout<<"\n Média do Aluno ...: " << Aluno[i].media_nota;
  if (Aluno[i].situacao==1)
  {
  cout<<"\n Aluno Aprovado ";
  }
  else if (Aluno[i].situacao==0)
  {
  cout<<"\n Aluno Reprovado";	
  }
  }
  
  do
{
cout<<"\n \n \n Menu Principal de Relatórios";
cout<<"\n [1] Mostrar somente o aluno XX - Pesquisa pelo código do aluno";
cout<<"\n [2] Mostrar somente o aluno XX - Pesquisa pelo nome do aluno";
cout<<"\n [3] Mostrar todos os alunos Aprovados ou Reprovados (o usuário escolherá)";
cout<<"\n [4] Mostrar todos os alunos de determina disciplina";
cout<<"\n [5] Relatório mostrando todos os alunos cadastrados";
cout<<"\n [6] Digite 6 para sair deste menu";
cout<<"\n\n\n\n ESCOLHA UMA OPÇÃO --> ";
cin>>op;

switch (op)
{
		
	
case 1:{
  cout<< "Digite o número do aluno :   ";
  cin>>i;
  i=i-1;
  cout<<"\n\n ____________________________________________________";
  cout<<"\n\n Nome ...........:";
  puts (Aluno[i].nome);
  cout<<"\n Disciplina .....: ";
  puts(Aluno[i].disciplina);
  cout<<"\n Idade do Aluno ...: " << Aluno[i].idade;
  cout<<"\n Nota da Prova 1 ...: " << Aluno[i].nota_prova1;
  cout<<"\n Nota da Prova 2 ...: " << Aluno[i].nota_prova2;
  cout<<"\n Nota da Prova 3 ...: " << Aluno[i].nota_prova3;
  cout<<"\n Nota da Prova 4 ...: " << Aluno[i].nota_prova4;
  cout<<"\n Média do Aluno ...: " << Aluno[i].media_nota;
  if (Aluno[i].situacao==1)
  {
  cout<<"\n Aluno Aprovado ";
  }
  else if (Aluno[i].situacao==0)
  {
  cout<<"\n Aluno Reprovado";	
  }
	
getch(); // espera digitar algo
break;
}

case 2:{

	cout<<"\n Digite o nome do aluno :   ";
		fflush(stdin);
	cin>>pornome;	
  
  for (i=0; i<5;i++)
  {
  	if (strcmpi (Aluno[i].nome, pornome) == 0)
  	{
  cout<<"\n\n ____________________________________________________";
  cout<<"\n\n Nome ...........:";
  puts (Aluno[i].nome);
  cout<<"\n Disciplina .....: ";
  puts(Aluno[i].disciplina);
  cout<<"\n Idade do Aluno ...: " << Aluno[i].idade;
  cout<<"\n Nota da Prova 1 ...: " << Aluno[i].nota_prova1;
  cout<<"\n Nota da Prova 2 ...: " << Aluno[i].nota_prova2;
  cout<<"\n Nota da Prova 3 ...: " << Aluno[i].nota_prova3;
  cout<<"\n Nota da Prova 4 ...: " << Aluno[i].nota_prova4;
  cout<<"\n Média do Aluno ...: " << Aluno[i].media_nota;
  if (Aluno[i].situacao==1)
  {
  cout<<"\n Aluno Aprovado ";
  }
  else if (Aluno[i].situacao==0)
  {
  cout<<"\n Aluno Reprovado";	
  }
  }

}

getch();
break;

}



case 3:{
	cout<<"\n Você quer filtrar pelos aprovados ( Digite 1) ou reprovados ( Digite 0) ? :   ";
	fflush(stdin);
	cin>>porsituacao;



	 for (i=0; i<5;i++)
  {
  	if (porsituacao==Aluno[i].situacao)
  	{
  cout<<"\n\n ____________________________________________________";
  cout<<"\n\n Nome ...........:";
  puts (Aluno[i].nome);
  cout<<"\n Disciplina .....: ";
  puts(Aluno[i].disciplina);
  cout<<"\n Idade do Aluno ...: " << Aluno[i].idade;
  cout<<"\n Nota da Prova 1 ...: " << Aluno[i].nota_prova1;
  cout<<"\n Nota da Prova 2 ...: " << Aluno[i].nota_prova2;
  cout<<"\n Nota da Prova 3 ...: " << Aluno[i].nota_prova3;
  cout<<"\n Nota da Prova 4 ...: " << Aluno[i].nota_prova4;
  cout<<"\n Média do Aluno ...: " << Aluno[i].media_nota;
  if (Aluno[i].situacao==1)
  {
  cout<<"\n Aluno Aprovado ";
  }
  else if (Aluno[i].situacao==0)
  {
  cout<<"\n Aluno Reprovado";	
  }
  }

}

getch();
break;

}

case 4:{
	cout<<"\n Digite o nome da disciplina :   ";
		fflush(stdin);
	cin>>pordisciplina;	
  
  for (i=0; i<5;i++)
  {
  	if (strcmpi (Aluno[i].disciplina, pordisciplina) == 0)
  	{
  cout<<"\n\n ____________________________________________________";
  cout<<"\n\n Nome ...........:";
  puts (Aluno[i].nome);
  cout<<"\n Disciplina .....: ";
  puts(Aluno[i].disciplina);
  cout<<"\n Idade do Aluno ...: " << Aluno[i].idade;
  cout<<"\n Nota da Prova 1 ...: " << Aluno[i].nota_prova1;
  cout<<"\n Nota da Prova 2 ...: " << Aluno[i].nota_prova2;
  cout<<"\n Nota da Prova 3 ...: " << Aluno[i].nota_prova3;
  cout<<"\n Nota da Prova 4 ...: " << Aluno[i].nota_prova4;
  cout<<"\n Média do Aluno ...: " << Aluno[i].media_nota;
  if (Aluno[i].situacao==1)
  {
  cout<<"\n Aluno Aprovado ";
  }
  else if (Aluno[i].situacao==0)
  {
  cout<<"\n Aluno Reprovado";	
  }
  }

}
getch();
break;

}

case 5:{



getch();
break;

}




}
} while(op!=6);


  
  
  

}
