#include <stdio.h>

int main()
{

double quantia;

int n100,n50,n20,n10,n5,n2;

int m1, m05,m025,m010,m005,m001;

int qntInt, aux;
double qntReal;

scanf("%lf",&quantia);

qntInt = (int)quantia;
	
n100 = quantia / 100;
qntInt = qntInt % 100;
n50 = qntInt / 50;
qntInt = qntInt % 50;
n20 = qntInt / 20;
qntInt = qntInt % 20;
n10 = qntInt / 10;
qntInt = qntInt % 10;
n5 = qntInt / 5;
qntInt = qntInt % 5;
n2 = qntInt / 2;
m1 = qntInt % 2;

qntReal = quantia -((int)quantia);	
aux = qntReal *100;
	
m05 = aux / 50;
aux = aux % 50;
m025 = aux / 25;
aux = aux % 25;
m010 = aux / 10;
aux = aux % 10;
m005 = aux / 5;
m001 = aux % 5;

printf("NOTAS:\n");
printf("%d nota(s) de R$ 100.00\n",n100);
printf("%d nota(s) de R$ 50.00\n",n50);
printf("%d nota(s) de R$ 20.00\n",n20);
printf("%d nota(s) de R$ 10.00\n",n10);
printf("%d nota(s) de R$ 5.00\n",n5);
printf("%d nota(s) de R$ 2.00\n",n2);
	
printf("MOEDAS:\n");
printf("%d moeda(s) de R$ 1.00\n",m1);
printf("%d moeda(s) de R$ 0.50\n",m05);
printf("%d moeda(s) de R$ 0.25\n",m025);
printf("%d moeda(s) de R$ 0.10\n",m010);
printf("%d moeda(s) de R$ 0.05\n",m005);
printf("%d moeda(s) de R$ 0.01\n",m001);
 	
	return 0;
}
