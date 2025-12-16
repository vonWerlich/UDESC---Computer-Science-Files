#include <stdio.h>
#include <math.h>

int main ()
{
int i,j,n;

scanf("%d", &n);

for	(i=1;i<=n;i++)
{
int PopA,PopB,CreA,CreB,PopTotA,PopTotB,TCreA,TCreB;

	scanf("%d", &PopA);
	scanf("%d", &PopB);
	scanf("%d", &CreA);
	scanf("%d", &CreB);
	
	for (j=1;j<=100;j++)
	{
	
	
	TCreA= 1+(CreA/100.0);
	TCreB= 1+(CreB/100.0);
	PopTotA= PopA*pow(TCreA,j);
	PopTotB= PopB*pow(TCreB,j);

	if (PopTotA>PopTotB)
	{printf("%d anos\n", j);
	}	
    }
	
}
	
	
	
	
	return 0;
}
