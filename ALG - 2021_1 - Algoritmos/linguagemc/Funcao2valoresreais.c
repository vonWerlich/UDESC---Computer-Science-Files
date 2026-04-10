#include <stdio.h>
#include <locale.h>

float maior(float n1, float n2) 
{
  int resultado;
  if (n1>n2)
  {resultado = -1;}
  else if (n1<n2)
  {resultado = 1;}
  //se não se encaixar em nenhuma das duas possibilidades (n1=n2) o programa retorna 0
  return (resultado); 
}

int main(void)
{
setlocale(LC_ALL, "Portuguese");  
float n1,n2;
int resultado;

printf("Digite o primeiro número: ");
scanf("%f", &n1);
printf("Digite o segundo número: ");
scanf("%f", &n2);
  
resultado = maior(n1,n2);

 switch ( resultado )
  {
    case -1 :
    printf ("Primeiro valor (maior)\n%.2f",n1);
    break;
    
    case 0 :
    printf ("Dois valores iguais\n%.2f",n1);
    break;
    
    case 1 :
    printf ("Segundo valor (maior)\n%.2f",n2);
    break;
    
    default :
    printf ("Erro nos números inseridos\n");
  }

return 0;
}

