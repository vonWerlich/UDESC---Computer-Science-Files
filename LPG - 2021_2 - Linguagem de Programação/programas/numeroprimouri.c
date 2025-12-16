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
    
	for (j=1;j<=x;j++)
	{
	if (x%j==0)
	{cont++;}
		
	}

	if (cont==2)
	{printf("%d eh primo\n", x);}
	
	else
	{printf("%d nao eh primo\n", x);}
}	
	
	return 0;
}
