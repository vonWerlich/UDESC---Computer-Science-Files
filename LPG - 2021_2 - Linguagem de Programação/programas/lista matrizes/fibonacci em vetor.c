#include <stdio.h>

int fibonacci (int a);

int main ()
{
int T,N,i;	

scanf("%d", &T);
	
for (i=0;i<T;i++)
{
scanf("%d", &N);

printf("Fib(%d) = %d\n", N, fibonacci(N));
}
	
	return 0;
}

int fibonacci (int a)
{
int resultado;
if (a==0)
{resultado=0;
}

if (a==1)
{resultado=1;
}

if (a>1)
{resultado= a + fibonacci(a-1);
}

return resultado;
}
