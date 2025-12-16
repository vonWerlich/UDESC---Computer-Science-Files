#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
int dia, mes, ano;	
}data_nascimento;

typedef struct
{
   int matricula;
   char nome[100];
   data_nascimento Data;
   float notas[5];
} Aluno;

double medias[200];

Aluno alunos[200];

int main ()
{
setlocale(LC_ALL, "Portuguese");
FILE *file1;

file1 = fopen("Arquivo.bin", "rb");

int m=0,contador=0;
char string[200];

if(file1)
{
	do
	{
			fread(&alunos[m].matricula,sizeof(int),1,file1);
			fread(&alunos[m].nome,sizeof(char),100,file1);
			fread(&alunos[m].Data.dia,sizeof(int),1,file1);
			fread(&alunos[m].Data.mes,sizeof(int),1,file1);
			fread(&alunos[m].Data.ano,sizeof(int),1,file1);
			fread(&alunos[m].notas[0],sizeof(float),1,file1);
			fread(&alunos[m].notas[1],sizeof(float),1,file1);
			fread(&alunos[m].notas[2],sizeof(float),1,file1);
			fread(&alunos[m].notas[3],sizeof(float),200,file1);
			fread(&alunos[m].notas[4],sizeof(float),1,file1);
			
			m++;
		
	}
	while (!feof(file1));
		
}
int i;
for (i=0;i<m;i++)
{double med=0;
med=alunos[i].notas[0]+alunos[i].notas[1]+alunos[i].notas[2]+alunos[i].notas[3]+alunos[i].notas[4];
med=med/5.0;
medias[i]=med;	
	
}

FILE *file2;

file2 = fopen("Saida.bin", "wb");

int j;

if(file2)
{
	for (j=0;j<m;j++)
	{
		fwrite(&alunos[j].matricula,sizeof(int),1,file2);
		fwrite(&medias[j],sizeof(int),1,file2);
	
	}	
}
else
{
	printf(" Erro ao criar o arquivo!");
}

fclose(file2);
printf("\n O arquivo Saida.bin foi criado com sucesso!\n");

return 0;
}
