#include <stdio.h>
#include <string.h>

int main ()
{
int i;
char palavra[200],frase[200]; 

printf("Digite frase: ");
scanf(" %200[^\n]", frase);
printf("Digite palavra: ");
scanf(" %50[^\n]", palavra);


char *result = strstr(frase,palavra);

    printf("Resultado: ");
    for (i = 0; i < strlen(palavra); i++)
        printf("%c", *(result + i));

    return 0;
}
