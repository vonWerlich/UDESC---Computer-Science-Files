#include <stdio.h>
#define tam_max 10

int main ()
{
int V [10] = {34,23,3,40,100,31,70,8,7,50};
int i,j;
int cont=0;


for (i=0; i < tam_max; i++)
{
	
 //o for abaixo acha os divisores do número nessa posição do vetor
 for (j=1;j<=V[i];j++) 
 {
   if (V[i] % j == 0)
      cont++;
  }
  //verifica se o número dessa posição do vetor é primo, ou seja, se só tem 2 divisores
  if (cont==2)
      printf("\nPosicao %d: %d", i, V[i]);
  cont=0;	  	
}

return 0;
}
