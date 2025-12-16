#include <stdio.h>

int main ()
{

double salario,imposto1,imposto2,imposto3;

scanf("%lf", &salario);

imposto1= (salario - 2000)*0.08;
imposto2= (salario - 3000)*0.18 + 80;
imposto3= (salario - 4500)*0.28 + 350;

if (0<=salario&&salario<=2000)
{printf("Isento\n");
}
else
	{	
	if (2000<salario&&salario<=3000)
	{printf("R$ %.2lf\n",imposto1);
	}
	else
		{
		if (3000<salario&&salario<=4500)
		{printf("R$ %.2lf\n",imposto2);
		}
		else
			{
			if (4500<salario)
			{printf("R$ %.2lf\n",imposto3);
			}
			}
		}	
	}
	return 0;
}
