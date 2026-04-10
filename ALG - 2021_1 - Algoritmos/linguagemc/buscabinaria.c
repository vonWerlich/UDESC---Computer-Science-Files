#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//esse algoritmo recebe um vetor de inteiros e verifica se um determinado inteiro pertence
//ao vetor.
int main()
{
setlocale(LC_ALL, "Portuguese");  
int i,tam_vetor,controle; 
int inicio,meio,fim;
int numero,encontrar,*v;
    
printf("Digite o tamanho do vetor: ");
scanf("%d", &tam_vetor);

//aloca espaço de memória para o vetor 
v = (int *) malloc(tam_vetor * sizeof(int));

//mensagem de erro   
if (v == NULL)
{ 
printf("Erro ao alocar vetor!");
return 0;        
}
    
    //leitura do vetor
    else
    {  
    for (i=0;i<tam_vetor;i++)
    {
    scanf("%d", &numero);
    v[i] = numero;
    }
        
    printf("Digite o número a ser pesquisado no vetor: ");
    scanf("%d",&encontrar);
        
    fim = (tam_vetor - 1);
        
    for (inicio=0;inicio<tam_vetor;)
    {     
        meio = (inicio + fim) / 2;
              
        if (encontrar == v[meio])
        {
        controle = 0;
        break;
        }
              
        else if (encontrar < v[meio])
        {
        fim = (meio - 1);
        }
              
        else if(encontrar > v[meio])
        {
        inicio = (meio + 1);
        }    
    	else
        {
        controle = 1;
        break;
        }   
    }
        
    if (controle == 0)
	{
    printf("O número %d foi encontrado! Posição: %d - Valor: %d", encontrar, meio, v[meio]);                      
    }
	else
	{
    printf("O número %d não foi encontrado!", encontrar);
    }

    return 0;
        
    }
    
}
