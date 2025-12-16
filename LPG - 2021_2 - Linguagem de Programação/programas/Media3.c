#include <stdio.h>

int main ()
{
double nota1,nota2,nota3,nota4,notaexame,media,mediafinal;

	scanf("%lf", &nota1);
	scanf("%lf", &nota2);
	scanf("%lf", &nota3);
	scanf("%lf", &nota4);
	
	media= ((nota1*2.0) + (nota2*3.0) + (nota3*4.0) + (nota4*1.0))/10.0;
	
	if (media>=7.0)
	{
	printf("Media: %.1lf\n", media);
	printf("Aluno aprovado.\n");
	}
	else{
	
		if (media<5.0)
		{
		printf("Media: %.1lf\n", media);
		printf("Aluno reprovado.\n");
		}
		else{
			printf("Media: %.1lf\n", media);
			printf("Aluno em exame.\n");
			scanf("%lf", &notaexame);		
			printf("Nota do exame: %.1lf\n", notaexame);
			mediafinal= (media + notaexame)/2.0;
			if (mediafinal>=5.0)
			{
			printf("Aluno aprovado.\n");
			printf("Media final: %.1lf\n", mediafinal);
			}
			else
			{
			printf("Aluno reprovado.\n");
			printf("Media final: %.1lf\n", mediafinal);
			}
			
		}	
	}
	
	return 0;
}
