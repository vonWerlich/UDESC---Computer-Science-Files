#include <stdio.h>

int soma_valores (int);

int main () {
	
	int n;
	
	printf("Digite um valor: ");
	scanf("%d", &n);
	printf("= %d\n", soma_valores(n));
	
	return 0;
}

int soma_valores (int n)
{
	if (n<1)
	return 0;
	
	printf("%d+", n);
	return n+soma_valores(n-1);
	
	
}




