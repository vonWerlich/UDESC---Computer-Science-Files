#include <stdio.h>
#include <math.h>
#define prob 300 //a média de ocorrência dos eventos já está pré-definida, o usuário não precisa informar

/*solução usando a avaliação da distribuição poisson, encontrada em:
https://en.wikipedia.org/wiki/Poisson_distribution#Evaluating_the_Poisson_distribution  ,
que é matematicamente equivalente à fórmula original mas numericamente estável para
valores grandes*/
int main ()
{
double probabilidade=prob,evento; 
double resultado,expoente,logdegama,a;

scanf("%lf", &evento); //lê a quantidade de lampadas substituidas

logdegama = lgamma (evento + 1);
expoente = (evento*log(prob) - prob - logdegama);
resultado = pow (2.71828,expoente);

printf("%lf\n", resultado);
	
	return 0;
}

/*  resultados para as perguntas do enunciado:
	290 = 0.019787 = 1,98%
	320 = 0.011612 = 1,16%     */
