#include <stdio.h>

int main ()
{
int i,j,k,n;
int x,y,soma,soma2;
int cont,cont2;

scanf("%d", &n);


for (i=1;i<=n;i++)
{
	soma=0;
	soma2=0;
    cont=1;
    cont2=0;
	scanf("%d", &x);
	scanf("%d", &y);
	
	if (x%2==0)
	{
	for (j=1;j<=y;j++)
	{
	soma=soma+x+cont;
	cont=cont+2;
	}
	printf("%d\n", soma);
	}
	
	else
	{
	for (k=1;k<=y;k++)
	{
	soma=soma+x+cont2;
	cont2=cont2+2;
	}
	printf("%d\n", soma);
	}
}


	return 0;
}
