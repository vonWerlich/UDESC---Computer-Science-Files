#include <stdio.h>
#include <string.h>

/* Lembrando que a primavera começa no dia 23 de setembro, o verão em 21 de dezembro,
o outono em 21 de março e o inverno em 21 de junho. -> definições do professor
Nesse programa eu usei essas definições, contudo nesse ano as datas da mudança de 
estações são diferentes.*/
char* estacao(int dia, int mes);

int main ()
{

int dia,mes;
char season[15];

printf("Insira o dia: ");
scanf("%d", &dia);
printf("\nInsira o mes: ");
scanf("%d", &mes);	

strncpy(season,estacao(dia,mes),15);

printf("%s\n", season);
	
	return 0;
}

char* estacao(int dia, int mes)
{ if (mes<3)
	{return "verao";}
	
  if (mes==3&&dia<21)
	{return "verao";}
		
  if (mes==3&&dia>=21)
	{return "outono";}
	
  if (mes>=4&&mes<6)
	{return "outono";}
	
  if (mes==6&&dia<21)
	{return "outono";}

  if (mes==6&&dia>=21)
	{return "inverno";}
	
  if (mes>=7&&mes<9)
	{return "inverno";}
	
  if (mes==9&&dia<23)
	{return "inverno";}
	
  if (mes==9&&dia>=23)
	{return "primavera";}
	
  if (mes>=10&&mes<12)
	{return "primavera";}
	
  if (mes==12&&dia<21)
	{return "primavera";}
  
  if (mes==12&&dia>=21)
	{return "verao";}
}
