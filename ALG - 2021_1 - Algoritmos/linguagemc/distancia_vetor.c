#include <stdio.h>
#define tam_max 10
//se não existir um valor igual a n no vetor, o algoritmo só funciona se existirem
//no máximo 2 valores a mesma distância de n

int main ()
{
int n,i,j,k,achou=0,menor,posicao,posicao2;
int vetor[tam_max],vet2[tam_max];

//leitura no inteiro n
	scanf ("%d",&n);
//leitura do vetor
for (i=0; i < tam_max; i++)
    scanf ("%d",&vetor[i]);
//verificar se existem números iguais a n no vetor
for (i=0; i < tam_max; i++)

{
if (vetor[i] == n)
{printf ("%d\nPosicao %d",n,i);
  achou++;}
}
//verifica o(s) número(s) mais próximo de n no vetor
	if (achou==0)
{
	for (i=0; i < tam_max; i++)
{
	if (n-vetor[i]>0)
	{vet2[i]=n-vetor[i];}
	else
	{vet2[i]=-(n - vetor[i]);}

}
	for (j=0;j<tam_max;j++)
{
	if (j==0)
	{menor=vet2[j];
	posicao=j;}
	
	if (menor>vet2[j])
	{menor=vet2[j];
	posicao=j;}
}
	for (k=0;k<tam_max;k++)
{
	if (vet2[k]==menor)
	{posicao2=k;}
}
	if (posicao2==posicao)
	{printf("Mais proximo %d posicao %d",vetor[posicao],posicao);}
	else
	{printf("Mais proximo %d posicao %d",vetor[posicao],posicao);
	printf ("\nMais proximo %d posicao %d",vetor[posicao2],posicao2);}
}
return 0;
}
