#include <stdio.h>
#include<stdlib.h>
#include <locale.h>
#include<time.h>


int valor, vet[10],i;
int main()
{
int inicio,fim;	
printf("Digite o limite inicial: ");
scanf("%d",&inicio);

printf("Digite o limite final: ");
scanf("%d",&fim);
	
  setlocale(LC_ALL, "Portuguese");
 
  // inicializa o gerador de números randômicos
   srand(time(NULL));
   for(i=0; i<10;i++)
   { // gera um número aleatório entre 1 e 1000 (inclusive)
    vet[i] =(rand()%(fim + 1 - inicio) +0 ); //vetor recebendo um número aleatório

    printf("%d ",vet[i]);
  }

}
