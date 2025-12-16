#include <stdio.h>

int main()
{
	return 0;
}

int somatorio(int n)
{
    if(n==1)
        {
		return 1;}
    else
        {
		return n + somatorio(n - 1);}
}
