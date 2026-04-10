#include <stdio.h>
#include <string.h>
#include <locale.h>
// No programa abaixo o comando alarme() não funciona adequadamente

int main ()
{
setlocale(LC_ALL, "Portuguese");
int cod_event;
char ligacao[3];

printf ("Digite o código:\n");
printf ("0 - Entrada de pessoa não autorizada\n");
printf ("1 - Máquina de produção parada\n");
printf ("2 - Matéria-prima espalhada\n");
printf ("3 - Acidente de trabalho\n");
printf ("4 - Falta de luz\n");

scanf ("%d",&cod_event);

switch (cod_event)
{
case 0:{
	printf("Ligar para a segurança - ramal 0.");
	break;}

case 1:{
	printf ("Ligar para a manutenção - ramal 9.");
	break;}

case 2:{
	printf ("Esvaziar o recinto e proximidades.\n");
	//alarme()
	printf ("Informe a manutenção: ramal 9.");
	break;}

case 3:{
	printf ("Ligar para os bombeiros: 193\n");
	//alarme()
	
	printf ("Você conseguiu ligar? (escreva SIM ou NAO)\n");
	scanf ("%s",ligacao);

	if ((strcmp (ligacao,"NAO")==0)||(strcmp (ligacao,"Nao")==0)||(strcmp (ligacao,"nao")==0))
	//strcmpi é como strcmp mas ignora maiúscula e minúscula, diminui possível erro do usuário.
	
	printf ("Ligue para a segurança – ramal 0.");
	break;}

case 4:{
    printf("Esvaziar o recinto e proximidades.");
	break;}
	
default :{
	printf ("Erro no valor do código, por favor insira um dos códigos listados acima.");
	break;}
}
return 0;
}
