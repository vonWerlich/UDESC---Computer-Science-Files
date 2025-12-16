#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

int main ()
{
char frase [200];
char palavra [50];

	printf("Digite uma frase: ");
	scanf("%s",frase);
	fflush(stdin);
	
	printf("Digite uma palavra ou trecho a ser procurado: ");
	scanf("%s",palavra);
	fflush(stdin);
	
	if (existe(palavra,frase)==1)
	{printf("trecho encontrado!");
	}
	
	
	system("pause");
	return 0;
	
}
