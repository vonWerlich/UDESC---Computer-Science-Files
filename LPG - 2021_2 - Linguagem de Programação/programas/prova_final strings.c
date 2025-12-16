#include <stdio.h>
#include <string.h>


int main()
{
char palavra[200];
fgets(palavra,200,stdin);
char aux;

int i, j;
for(i=0;i<200;i++)
	{
        for(j=i+1;j<(200);j++)
		{
            if (palavra[i]>palavra[j])
			{
                
                aux=palavra[i];
                palavra[i]=palavra[j];
                palavra[j]=aux;
            }
        }
    }
    
    printf("%s", palavra);
	
	return 0;
}
