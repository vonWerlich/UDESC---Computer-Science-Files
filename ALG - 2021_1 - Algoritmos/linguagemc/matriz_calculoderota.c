#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define tam_max 6

//0-cáceres, 1-bbugres, 2-cuiába, 3-vgrande, 4-tangará, 5-placerda

int main ()
{
setlocale(LC_ALL, "Portuguese"); 
int c,c2,i,j,k,x,distancia,distancia2;
int *v1,*v2;

int m [tam_max][tam_max] = {{0,63,210,190,0,190},
{63,0,160,150,95,0},
{210,160,0,10,0,0},
{190,150,10,0,0,0},
{0,95,0,0,0,80},
{190,0,0,0,80,0},
{181,0,104,96,0,0},
{0,0,401,0,149,391}};

v1 = (int *) malloc(tam_max * sizeof(int));
v2 = (int *) malloc(tam_max * sizeof(int));


scanf ("%d",&c);
for (i=0;i<c;i++)
{
scanf ("%d",&c2);
v1[i]=c2;
}


for (k=0;k<c-1;k++)
{v2[k]= m[v1[k]][v1[k+1]];
}

for (i=0;i<c-1;i++)
{if (v2[i]==0)
    {printf("Não há uma rota possível");
	break;}
else
{
}


}

for (j=0;j<(c-1);j++)
{distancia=distancia + v2[j];
}


x=distancia;


printf("%d\n",x);



}
