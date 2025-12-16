#include <stdio.h>
#define tam_max 12

int main() 
{
int i,j;
int minima = 5,maxima = 6;
char operacao;
double m[12][12];
double soma = 0,media;
    
scanf("%c",&operacao);
    
    for (i=0;i<tam_max;i++)
	{
		for (j=0;j<tam_max;j++)
			{
            scanf("%lf", &m[i][j]);
            
            if (i>6&&j>=minima&&j<=maxima)
            soma += m[i][j];
        	}
        if (i > 6) {
            minima--;
            maxima++;
        }
    }
    if (operacao=='M')
    {
	media = soma/ 30.0;
    printf("%.1lf\n", media);
	}
    else
    	if (operacao =='S')
    	printf("%1.lf\n", soma);
    return 0;
}
