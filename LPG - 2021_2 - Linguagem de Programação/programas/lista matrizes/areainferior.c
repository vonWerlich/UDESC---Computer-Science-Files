#include <stdio.h>
#define tam_max 12

int main ()
{
double vetor [20] = {0,0,0,1,2,4,6,9,12,16,20,25,30,36,42,49,58,66,74,83};
int i,j,metade;
double matriz [tam_max][tam_max];
double soma=0,media;
char operacao;

scanf("%s", operacao);


for (i=0;i<tam_max;i++)
	{
	for (j=0;i<tam_max;j++)
		{
		scanf("%lf", &matriz[i][j]);
		}
	}
metade= tam_max/2.0;
	
for (i=0;i<tam_max;i++)	
	{
	for (j=0;i<tam_max;j++)
		{
		if (i>metade&&i+j>=tam_max)
			{
			soma=soma + matriz [i][j];
			}
		}
	}
media= soma/vetor[tam_max];

if (operacao== 'S')
printf("%lf\n", soma);
else 
	if (operacao== 'M') 
	printf("%lf\n", media);
	
	return 0;
}
