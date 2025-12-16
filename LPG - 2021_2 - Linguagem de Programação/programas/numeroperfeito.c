#include <stdio.h>

int main ()
{
int numcasos,x,i,j;
int cont;

scanf("%d", &numcasos);

for (i=1;i<=numcasos;i++)	
{
	scanf("%d", &x);
    cont=0;
    
	for (j=1;j<x;j++)
	{
	if (x%j==0)
	{cont=cont+j;}
		
	}

	if (cont==x)
	{printf("%d eh perfeito\n", x);}
	
	else
	{printf("%d nao eh perfeito\n", x);}
}	
	
	return 0;
}
