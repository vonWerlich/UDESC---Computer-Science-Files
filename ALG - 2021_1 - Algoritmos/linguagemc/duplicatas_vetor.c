#include<stdio.h>
#define tam_max  20
//o programa só funciona para valores inteiros diferentes de -9999

int main()
{
int i,j,cont;
int vetor[tam_max],copia[tam_max],ocorrencias[tam_max];

for (i=0;i<tam_max;i++)
	{
    scanf("%d", &vetor[i]);
    copia[i]= vetor[i];
	}
 
for (i=0;i<tam_max;i++)
	{
  	cont=0;
        for (j=0;j<tam_max;j++)
			{
            if(copia[i]==vetor[j])
			{cont++;
            vetor[j]= -9999;}
        }
        ocorrencias[i]=cont;
    }

    for (i=0;i<tam_max;i++)
  {
   if (ocorrencias[i]>1)
	  {
	  	printf("%d : ocorre %d x \n",copia[i],ocorrencias[i]);
	  }
}
return 0;
}
