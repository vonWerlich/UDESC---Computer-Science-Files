#include <stdio.h>
#include <math.h>
#include <locale.h>
/*Tentei fazer o programa abaixo por tentativa e erro, mas algo deu errado na implementação
da minha ideia e o programa não funciona (fica sempre retornando zero)*/
int main ()
{
setlocale(LC_ALL, "Portuguese");
int i,j,p,x;
double vfinanciado,vprestacao,taxa,vtotal,vjuros;
double meses,expoente,variavel;

printf("Informe o valor financiado: ");	
scanf("%lf", &vfinanciado);
printf("\nInforme o valor da prestação: ");	
scanf("%lf", &vprestacao);
printf("\nInforme o número de parcelas (meses): ");	
scanf("%lf", &meses);

for (i=0;p-vprestacao<0.000001;i++)
{x=i;
variavel=pow(1+x,-meses);
p=x*vfinanciado/(1-variavel);
taxa= x-1.0;}

for (i=i;p-vprestacao<0.000001;i++)
{x=i/10;
variavel=pow(1+x,-meses);
p=x*vfinanciado/(1-variavel);
taxa= x-0.1;}

for (i=i;p-vprestacao<0.000001;i++)
{x=i/100;
variavel=pow(1+x,-meses);
p=x*vfinanciado/(1-variavel);
taxa= x-0.01;}

for (i=i;p-vprestacao<0.000001;i++)
{x=i/1000;
variavel=pow(1+x,-meses);
p=x*vfinanciado/(1-variavel);
taxa= x-0.001;}

for (i=i;p-vprestacao<0.000001;i++)
{x=i/10000;
variavel=pow(1+x,-meses);
p=x*vfinanciado/(1-variavel);
taxa= x-0.0001;}

for (i=i;p-vprestacao<0.000001;i++)
{x=i/100000;
variavel=pow(1+x,-meses);
p=x*vfinanciado/(1-variavel);
taxa= x-0.00001;}

for (i=i;p-vprestacao<0.000001;i++)
{x=i/1000000;
variavel=pow(1+x,-meses);
p=x*vfinanciado/(1-variavel);
taxa= x-0.000001;}

printf("\nA taxa de juros é: %lf %%", taxa);

	return 0;
}
