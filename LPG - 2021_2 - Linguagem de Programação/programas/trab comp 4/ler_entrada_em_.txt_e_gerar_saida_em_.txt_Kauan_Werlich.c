#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#define Tam_Max_Casos_Teste 20000

int main ()
{
setlocale(LC_ALL, "Portuguese");
int i,j,testes,casos;

	FILE *file1;
	FILE *file2;
	
	file1 = fopen("EntradaDados.txt", "r");
	
	file2 = fopen("SaidaDados.txt", "w");
	
	if (file1)
	{
		while(!feof(file1)) 
			{
			int positivos,negativos;
			fscanf(file1,"%d", &testes);
			
			if (testes!=0)
			{	positivos=0,negativos=0;
				
				if (testes<2||testes>100000)
					{
						for (j=0;j<testes;j++)
						{
						fscanf(file1,"%d",&casos);
						}
					fprintf(file2,"quantidade inválida de casos\n");
					}
				
				else 
				{
					for (j=0;j<testes;j++)
						{
						fscanf(file1,"%d",&casos);
						if (casos>0)
							{
							positivos++;
							}
						else
							{
							negativos++;
							}
		
						}
						
				if (positivos>1&&negativos>1)
			{
			fprintf(file2,"%d negativos, %d positivos\n", negativos,positivos);	
			}
			if (positivos>1&&negativos==1)
			{
			fprintf(file2,"%d negativo, %d positivos\n", negativos,positivos);	
			}
			if (positivos>1&&negativos==0)
			{
			fprintf(file2,"%d positivos\n", positivos);	
			}
			if (positivos==1&&negativos>1)
			{
			fprintf(file2,"%d negativos, %d positivo\n", negativos,positivos);	
			}
			if (positivos==1&&negativos==1)
			{
			fprintf(file2,"%d negativo, %d positivo\n", negativos,positivos);	
			}
			if (positivos==1&&negativos==0)
			{
			fprintf(file2,"%d positivo\n", positivos);	
			}
			if (positivos==0&&negativos>1)
			{
			fprintf(file2,"%d negativos\n", negativos);	
			}
			if (positivos==0&&negativos==1)
			{
			fprintf(file2,"%d negativo\n", negativos);	
			}
			if (positivos==0&&negativos==0)
			{
			fprintf(file2,"Erro na contagem dos números! Não é possível ter uma linha sem números ou só com o zero!\n", negativos,positivos);	
			}
					
						
				}	
					
			}
			else
			{
			break;		
			}
			
			
			
			}
			fclose(file1);
			fclose(file2);
			printf("Arquivo: SaidaDados.txt gerado com sucesso!");
	}
	else
	{
		printf("Erro ao abrir o arquivo!");
	}
	

	
	
	return 0;
}
