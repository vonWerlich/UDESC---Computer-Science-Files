#include <stdio.h>
#include <math.h>
#define tam_max 10

int main ()
{
int x,y,a,i,vetor[tam_max];
	
scanf("%d", &x);	
	
	for (i=0;i<tam_max;i++)
	{
	a=pow(2,i);
	y=x*a;
	printf("N[%d] = %d\n",i,y);		
	}

	return 0;
}
