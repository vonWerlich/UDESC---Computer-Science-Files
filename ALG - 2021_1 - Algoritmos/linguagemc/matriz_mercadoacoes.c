#include <stdio.h>
#include <locale.h>
#define L 20
#define C 3

//no enunciado tinha 21 linhas na matriz, mas eu coloquei todas aqui mesmo sendo apenas 20
int main ()
{
setlocale(LC_ALL, "Portuguese");  
int lin,col,n,cont=0;
float alta;
float m[L][C]= {16.32,16.49,16.11,
                16.96,17.2,16.47,
                33.99,35.34,33.6,
                13.82,14.11,13.54,
                29.69,29.33,29,
                61.99,64.1,58.64,
                19.82,20.2,19.63,
                9.42,9.24,9.09,
                32.85,33.92,32.55,
                40.4,41.02,39.94,
                28.4,28.98,28.04,
                57.3,58.65,56.73,
                39.92,40.09,39.23,
                43.18,43.2,42.09,
                11.61,11.63,11.44,
                34.62,34.77,33.84,
                16.1,16.19,15.43,
                19.01,19.95,18.71,
                107,109.32,105.66,
                34.69,34.74,33.4,
                25.24,25.4,23.3};
//col 0 = última ; col 1 = máxima ; col 2 = mínima
for (lin=0;lin<L;lin++)
   {
	if (m[lin][1] > alta)
	   {alta = m[lin][1];
	    n = lin;
	   }
    }

printf ("Empresa %d tem o maior valor: %.2f\n",n,alta);

printf ("Empresas cujo último valor da ação supera o valor da máxima:\n");
for (lin=0;lin<L;lin++)
   {
	if (m[lin][0] > m[lin][1])
	   {printf ("Empresa %d : último (%.2f), máximo (%.2f)\n",lin,m[lin][0],m[lin][1]);
	   cont++;
	   }
    }	
    
if (cont++ ==0)  
   {printf ("Não há nenhuma empresa cujo último valor da ação supera o valor da máxima.");}  
 
return 0;	
}

