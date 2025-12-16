#include <stdio.h> 
#include <locale.h>
#include <stdlib.h> 
#include <time.h> 

int main()
{
int i,j,testes,casos,numero;
setlocale(LC_ALL, "Portuguese");
FILE *file;

file = fopen("EntradaDados.txt", "w");	

    if(file){
		printf("\n Quantos casos de teste deseja gerar? Digite um número entre 2 e 100000.\n Leve em conta que muitos casos de teste podem sobrecarregar o programa. \n");
		scanf("%d", &testes);
		
		srand(time(NULL));
		
		for (i=0;i<testes;i++)
		{casos = 1+rand()%25000+rand()%25000+rand()%25000+rand()%25000;
		fprintf(file,"%d ", casos);
		
			for (j=0; j < casos; j++)
			{
			numero= -100000 + rand()%25000+rand()%25000+rand()%25000+rand()%25000+rand()%25000+rand()%25000+rand()%25000+rand()%25000 ;
			if(numero!=0)
				{fprintf(file,"%d ", numero);
				if (j+1==casos)
					{fprintf(file,"\n");
					}
				}
			else
				{j--;
				}
			}
			
			if (i+1==testes)
			{
			fprintf(file,"0");
				}	
		}
		fclose(file);
		printf("O arquivo EntradaDados.txt foi gerado com sucesso!");
    }
    else
        printf("\n\t--> ERRO ao abrir arquivo de entrada!\n");






return 0;
}
