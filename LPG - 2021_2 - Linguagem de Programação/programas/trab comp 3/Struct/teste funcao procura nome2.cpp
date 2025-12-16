#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool testar (int teste [], int tam)
{
	for (int i=0;i<tam;i++)
	{
	if (teste[i]==0)
	{return false;}	
	}
	return true;
}

bool existe (char palavra[], char frase[])
{
	int teste [ strlen(palavra) ];
	int aux;
	
	if (strlen(palavra) > strlen(frase))
	{return false;}
	 
	if (strcmpi(palavra,frase)==0)
	{return true;}
	
	for (int i =0; i<(strlen(frase)-strlen(palavra)); i++)
	{if (frase[i]==palavra[0])
	
		for (int k=0;k<strlen(palavra);k++)
		{
		teste[k]=0;
		}
		
		aux=i;
		for (int j=0;j<strlen(palavra);j++)
		{
		if (palavra[j]==frase[aux])
		{
		teste[j]=1;
		aux++;
		}
		
		if (testar (teste,strlen(palavra)))
		{
		return true;	
		}
		
		
		
		}
	}
	
	return false;
	
}

int main ()
{
	
	
	system("pause");
	return 0;
	
}
