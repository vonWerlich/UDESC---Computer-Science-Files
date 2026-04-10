#include <stdio.h>

int main ()
{
int i,numero;
scanf (numero);
i=0;
for (i=0; i <= numero; i++)
{
  if (numero % i == 0)
  printf ("\n%i",i);
}
return 0;

}
