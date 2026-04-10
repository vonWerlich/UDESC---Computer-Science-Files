//Ev
//EVERLIN FIGHERA COSTA MARQUES
//14:14
#include <stdio.h>
int soma (int n1, int n2 );
int main()
{
int a, b, somaDois;
printf("\n");
printf("Digite o valor de a:");
scanf("%i", &a);
printf("\n");
printf("Digite o valor de b:");
scanf("%i", &b);
if ( a > 0 && b > 0){
somaDois = soma( a, b);
printf("\n");
printf("Valor da soma=%i", somaDois);
}
return 0;
}
int soma (int n1, int n2 ){
int x;
x = n1 + n2;
return x;
}
