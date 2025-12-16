#include <stdio.h>
#define tam_max 12

int main()
{
int i,j,max=0;
char operacao;
double m[tam_max][tam_max], a=0;

scanf("%c",&operacao);
for (i=0;i<tam_max;i++)
	{
    for (j=0;j<tam_max;j++)
		{
        scanf("%lf", &m[i][j]);
        if (j<max)
			{
            a += m[i][j];
        	}
    	}
        if (i<5)
	    {max++;
		}
		if (i>5)
		{
		max--;
		}
    }
    if (operacao=='M') a /= 30.0;
    printf("%.1lf\n", a);
    return 0;
}
