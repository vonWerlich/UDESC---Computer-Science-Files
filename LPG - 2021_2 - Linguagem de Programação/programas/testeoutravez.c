#include <stdio.h>
#include <string.h>

void ordenarString(char *string, int tamanho);

int main()
{
   char string[100];
   int tamanho;
   
   printf("Introduza uma palavra\n");
   gets(string);
   
   tamanho=strlen(string);
   
   ordenarString(string,tamanho);
   
   scanf("%d",&string);
}

void ordenarString(char *string, int tamanho){
   int i, j, *aux[tamanho];
   
   for(i=0;i<10;i++){
        for(j=i+1;j<10;j++){
            if(strcmp(string[j], string[i])==-1){
                strcpy(aux, string[i]);
                strcpy(string[i], string[j]);
                strcpy(string[j], aux);

            }
        }
    }
}
