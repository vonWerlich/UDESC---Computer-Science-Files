#include <stdio.h>
#define tam_max 12
int main()
{
int i,j,min=1,max=10;
char t;
double m[tam_max][tam_max], a=0;
scanf("%c",&t);
for (i=0; i<tam_max; i++) {
    for (j=0;j<tam_max;j++)
	{
        scanf("%lf", &m[i][j]);
        if (i < 5 && j >= min && j <= max)
		{
            a += m[i][j];
        }
    }
        min++;
        max--;
    }
    if (t=='M') a /= 30.0;
    printf("%.1lf\n", a);
    return 0;
}
