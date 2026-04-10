#include<stdio.h>
#define tam_max 20

//Kauan Henrique Werlich
int main ()
{
int i,j,k,l,vetor[tam_max];
int pares[tam_max],impares[tam_max];
int cont=0,cont2=0,cont0=0;

//lê um vetor de 20 inteiros
for (i=0;i<tam_max;i++)
	{
    scanf("%d", &vetor[i]);
    }

//verifica os pares e ímpares
for (j=0;j<tam_max;j++)    
    {
     if (vetor[j]%2 == 0)	
    	{
		pares[cont]= vetor [j];
    	cont++;
		}
	 else 
	 {
	 impares[cont2]= vetor[j];
	 cont2++;
	 }
	}
	
//verifica quantos zeros há no vetor
for (l=0;l<tam_max;l++)
    {
    if (vetor[l]==0)
    {
	cont0++;}		
    }

    printf("Pares:\n");
    
    for (k=0;k<cont;k++)
    {
     printf ("%d ",pares[k]);
	}
    
    printf("\nImpares:\n");
    
	for (k=0;k<cont2;k++)
    {
     
     printf ("%d ",impares[k]);
	} 
    printf("\nTotal de zeros\n%d",cont0);
    
   
return 0;
}
