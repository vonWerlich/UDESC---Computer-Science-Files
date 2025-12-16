/*Kauan H. Werlich BCC UDESC
O programa abaixo gera um arquivo binário. O usuário informa um número de casos de testes,
e o programa utiliza a função rand (de time.h) para gerar um número de casos aleatório, e 
depois gera aleatoriamente essa mesma quantidade de números, e ao final acrescenta zero (para
indicar o fim dos casos de teste), no formato:

1 -3
7 1 2 3 4 5 6 7
3 -5 4 2
... etc
0 //fim

Nota: o programa gera números entre -100000 e 100000 (excluindo o zero), para que eles se
encaixem no intervalo avaliado pelo segundo programa. Mas é possível utilizar um intervalo
maior, aumentando o limite determinado em numero, na linha 49.


*/

#include <stdio.h> 
#include <locale.h>
#include <stdlib.h> 
#include <time.h> 

int main()
{
int i,j,testes,casos,numero,zero=0;
char string[]="\n", c[1];
setlocale(LC_ALL, "Portuguese");
FILE *file;

file = fopen("EntradaDados.bin", "wb");	

    if(file){
		printf("\n Quantos casos de teste deseja gerar? Digite um número entre 2 e 100000.\n Leve em conta que muitos casos de teste podem sobrecarregar o programa. \n");
		scanf("%d", &testes);
		
		srand(time(NULL));
		
		for (i=0;i<testes;i++)
		{
		casos = 1+rand()%25000+rand()%25000+rand()%25000+rand()%25000;
		fwrite(&casos,sizeof(int),1, file);
		
			for (j=0; j < casos; j++)
			{
			numero= -100000 + rand()%25000+rand()%25000+rand()%25000+rand()%25000+rand()%25000+rand()%25000+rand()%25000+rand()%25000 ;
			if(numero!=0)
				{fwrite(&numero,sizeof(int),1, file);
				
				}
			else
				{j--;
				}
			}
			if (i+1==testes)
			{
			fwrite(&zero,sizeof(int),1, file);
			}
		}
	
  
		
		fclose(file);
		printf("O arquivo EntradaDados.bin foi gerado com sucesso!");
	
    }
    else
        printf("\n\t--> ERRO ao abrir arquivo de entrada!\n");



return 0;
}
