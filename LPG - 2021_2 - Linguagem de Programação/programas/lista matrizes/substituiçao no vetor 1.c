#include <stdio.h>

int main ()
{
int X[10],i,j;

for (i=0;i<10;i++)
{
scanf("%d", &X[i]);
}

for (j=0;j<10;j++)
{
if (X[j]<=0)
	{
	X[j]=1;
	}
printf("X[%d] = %d\n", j, X[j]);
}

	return 0;
}
