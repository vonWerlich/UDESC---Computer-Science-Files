#include <stdio.h>
#include <string.h>
#include <ctype.h>


char texto[1000]="De acordo com o ....";
int qtde_vogais,qtde_brancos,tamanho;
int qtde_pontuacao,qtde_letras;


// Protótipo das Funções
int tamanho_string (char *texto);
void maiusculas (char *texto, int tamanho);
int vogais (char texto[], int tamanho);
int brancos (char texto[], int tamanho);
int pontuacao (char texto[], int tamanho);
int numeros (char texto[], int tamanho);
int caracteres (char texto[], int tamanho);
int letras (char texto[], int tamanho);
int main()
{


fgets (texto,1000,stdin);
tamanho = tamanho_string (texto);
maiusculas(texto,tamanho);


qtde_vogais = vogais(texto,tamanho);
printf("vogais %d ", qtde_vogais);
qtde_letras = letras(texto,tamanho);
printf("\nletras %d ", qtde_letras);
qtde_pontuacao = pontuacao(texto,tamanho);
printf("\npontuacao %d ", qtde_pontuacao);
qtde_brancos = brancos(texto,tamanho);
printf("\nbrancos %d ", qtde_brancos);
}

//tamanho string
int tamanho_string (char *texto)
{
   int tamanho;
   tamanho = strlen(texto);	
   return tamanho;
}


//transformando em maiúsculo o conteúdo da string
void maiusculas (char *texto, int tamanho)
{
	int i;
    for(i=0; i<tamanho; i++)
    {                            // Converte cada caracter de Str
     texto[i] = toupper (texto[i]);  //para maiusculas
    }
 } 
 
//contando as vogais 
 int vogais (char *texto, int tamanho)
{
	int i, cont_vogal=0;

    for(i=0; i<tamanho; i++)
    {
	    if ((texto[i] =='A')||(texto[i] =='E')||(texto[i] =='I')||(texto[i] =='O')||(texto[i] =='U'))
	        cont_vogal++;
	}
	return cont_vogal;
}
//contando espaços brancos 
 int brancos (char *texto, int tamanho)
{
	int i, cont_brancos=0;
		
    for(i=0; i<tamanho; i++)
    {
	    if (texto[i] ==' ')
	        cont_brancos++;
	}
	return cont_brancos;
}

//contando pontuação 
 int pontuacao (char *texto, int tamanho)
{
	int i, cont_pontuacao=0;
		
    for(i=0; i<tamanho; i++)
    {
	    if ((texto[i] =='?')||(texto[i] =='!')||(texto[i] ==',')||(texto[i] =='.')||(texto[i] =='"')||(texto[i] =='-')||(texto[i] ==')')||(texto[i] =='('))
	        cont_pontuacao++;
	}
	return cont_pontuacao;
}
//contagem números
int numeros (char texto[], int tamanho)
{
int i, cont_numeros=0;

    for(i=0; i<tamanho; i++)
    {
	    if ((texto[i] =='0')||(texto[i] =='1')||(texto[i] =='2')||(texto[i] =='3')||(texto[i] =='4')||
	    (texto[i] =='5')||(texto[i] =='6')||(texto[i] =='7')||(texto[i] =='8')||(texto[i] =='9'))
	        cont_numeros++;
	}
	return cont_numeros;	
}

//contando caracteres especiais (alguns mais usados)
int caracteres (char texto[], int tamanho)
{
int i, cont_caracteres=0;

    for(i=0; i<tamanho; i++)
    {
	    if ((texto[i] =='*')||(texto[i] =='/')||(texto[i] =='+')||(texto[i] =='@')||(texto[i] =='#')||
	    (texto[i] =='%')||(texto[i] =='$')||(texto[i] =='&')||(texto[i] =='~')||(texto[i] =='^'))
	        cont_caracteres++;
	}
	return cont_caracteres;	
	
}

//contando letras 
 int letras (char *texto, int tamanho)
{
    int cont_letras=0;
	cont_letras= tamanho-caracteres(texto,tamanho)-numeros(texto,tamanho)-pontuacao(texto,tamanho)-brancos(texto,tamanho);
	
	return cont_letras;
}
