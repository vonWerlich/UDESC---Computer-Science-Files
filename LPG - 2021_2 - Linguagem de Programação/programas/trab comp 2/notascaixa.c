#include <stdio.h>

int main()
{

double quantia;

int n50,n20,n10,n5,n2,n1;

int qntInt;

scanf("%lf",&quantia);

qntInt = (int)quantia;
	
n50 = quantia / 50;
qntInt = qntInt % 50;
n20 = qntInt / 20;
qntInt = qntInt % 20;
n10 = qntInt / 10;
qntInt = qntInt % 10;
n5 = qntInt / 5;
qntInt = qntInt % 5;
n2 = qntInt / 2;
n1 = qntInt % 2;
	
if (n50==1)
{printf("%d nota de R$ 50,00\n",n50);}
if (n50>1)
{printf("%d notas de R$ 50,00\n",n50);}
if (n20==1)
{printf("%d nota de R$ 20,00\n",n20);}
if (n20>1)
{printf("%d notas de R$ 20,00\n",n20);}
if (n10==1)
{printf("%d nota de R$ 10,00\n",n10);}
if (n10>1)
{printf("%d notas de R$ 10,00\n",n10);}
if (n5==1)
{printf("%d nota de R$ 5,00\n",n5);}
if (n5>1)
{printf("%d notas de R$ 5,00\n",n5);}
if (n2==1)
{printf("%d nota de R$ 2,00\n",n2);}
if (n2>1)
{printf("%d notas de R$ 2,00\n",n2);}
if (n1==1)
{printf("%d nota de R$ 1,00\n",n1);}
if (n1>1)
{printf("%d notas de R$ 1,00\n",n1);}	
 	
	return 0;
}
