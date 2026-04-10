#include <stdio.h>
#define tam_max 10

int main ()
{
int i,j,vet_num[tam_max];
int cont=0;

//leitura do vetor
//printf(" \nInforme os %d numeros para o vetor\n",tam_max);
for (i=0; i < tam_max; i++)
    scanf ("%d",&vet_num[i]);

for (i=0; i < tam_max; i++)
{
 //o for abaixo acha os divisores do número nessa posição do vetor
 for (j=1;j<=vet_num[i];j++) 
 {
   if (vet_num[i] % j == 0)
      cont++;
  }
  //verifica se o número dessa posição do vetor é primo, ou seja, se só tem 2 divisores
  if (cont==2)
      printf("Posicao %d: %d\n", i, vet_num[i]);
  cont=0;	  	
}

return 0;
}
