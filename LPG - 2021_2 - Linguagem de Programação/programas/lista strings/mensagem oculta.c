#include <stdio.h>
#include <string.h>

int main() {
    
int n,i;
char linha[51];	

scanf("%d ", &n);
scanf("%s", linha);

for (i=0;i<50;i++)
{
	if (linha[i]==' ')
	{i++;
	break;
	}
		else
		if (linha[i+1]!=' ')
		{printf("%s", linha[i]);
		i=i+2;
		break;
		}
			else
			{printf("%s", linha[i]);
			i++;
			break;
			}
	
}

    return 0;
}
