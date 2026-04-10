#include <stdio.h>
#include <stdlib.h>


int main()

{
   int num_cidades;

   int *itinerario;


   printf("\n");

   printf("Digite o numero de cidades do itinerario:");

   scanf("%f", &num_cidades);

    itinerario = (int *)malloc(num_cidades *  sizeof(int));
 

    free(itinerario);    

   return 0;

}
