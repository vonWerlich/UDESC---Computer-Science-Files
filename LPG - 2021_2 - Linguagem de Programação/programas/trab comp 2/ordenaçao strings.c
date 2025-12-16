#include<stdio.h>
#include<string.h>
#define tam_max 10
//o programa lê tam_max linhas de tamanho máximo 40, se for necessário é possível aumentar esse valor.

int main()
{
int i,j;
char str[tam_max][40],aux[40];

   printf("Insira as strings uma a uma: ");
   for(i=0;i<tam_max;i++)
      {scanf("%s", str[i]);}
      
   for(i=0;i<tam_max;i++)
   {
      for(j=i+1;j<tam_max;j++)
	  {
         if(strcmp(str[i],str[j])>0)
		 {
            strcpy(aux,str[i]);
            strcpy(str[i],str[j]);
            strcpy(str[j],aux);
         }
      }
	}
	
   printf("Strings em ordem alfabetica crescente: \n");
   for(i=0;i<tam_max;i++)
      printf("%s\n", str[i]);
   
   return 0;
}
