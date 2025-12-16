#include <stdio.h>

int main ()
{
int x,z,total,cont,cont2=0;
int i;

scanf("%d", &x);
z=x+1;

for (i=x;i<z;i++)
	{
	scanf("%d",&z);
	}
	cont=x;
	
	
	for(cont2=0; cont2<z; cont2++)
    {
        cont2+=cont;
        total++;
    }
    printf("%d\n", total);
    
/*    
    
for (i=1;i<z;i++)
	{
	cont=cont+cont+1;
	cont2++;
	}
	printf("%d",cont2);
	*/
	return 0;
}
