#include <stdio.h>

int main() {
  long int a,b,c;
  int i,n,j,cont;

  printf("Digite quantos numeros da sequencia de Fibonacci voce quer:\n");
  scanf("%d", &n);

  if (n <= 1) {
    printf("Numero invalido!\n");
  }
  else {
    
    a = 1;
    b = 1;
    printf("\n%d\n%d\n",a,b);

    for (j=2;j<n;j++)
	{
	  cont=0;
      c = a + b;
      for (i=1;i<=c;i++)
      {
      if (c % i == 0)	
      	{cont++; }
	  }
	  
	  if (cont == 2)
	  {printf ("%d - primo\n",c);}
	  else
      {printf("%d \n", c);}
      
	  a = b;
      b = c;

    }
  }

  return(0);
}
