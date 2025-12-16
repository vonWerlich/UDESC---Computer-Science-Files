#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX 200
#define TRUE 1
#define FALSE 0

typedef struct
{
int dia,mes,ano;
} data_evento;

typedef struct
{
int hora,minuto;	
} horario;

typedef struct
{
data_evento Data;
horario inicio;
horario final;
char local[200];
char descricao[200];
int status;
} evento;

evento Evento[MAX];
int posicao;

int main ()
{
setlocale(LC_ALL, "Portuguese");	
int escolha,dia2,mes2,ano2;

	

do{
FILE *file1;

file1 = fopen("DadosAgenda.bin", "rb");

int m=0,contador=0;
char string[200];

 

if(file1)
{
	do
	{
			fread(&Evento[m].Data.dia,sizeof(int),1,file1);
			fread(&Evento[m].Data.mes,sizeof(int),1,file1);
			fread(&Evento[m].Data.ano,sizeof(int),1,file1);
		
			fread(&Evento[m].inicio.hora,sizeof(int),1,file1);
			fread(&Evento[m].inicio.minuto,sizeof(int),1,file1);
			fread(&Evento[m].final.hora,sizeof(int),1,file1);
			fread(&Evento[m].final.minuto,sizeof(int),1,file1);
		
			fread(&Evento[m].local,sizeof(char),200,file1);
			fread(&Evento[m].descricao,sizeof(char),200,file1);
			
			fread(&Evento[m].status,sizeof(int),1,file1);
			
			contador++;
			m++;
		
	}
	while (!feof(file1));
		
}
posicao=contador;
if (posicao>0)
{posicao--;
}
fclose(file1);
	
 do{
  system("cls");
  fflush(stdin);
  printf("\n    Olá, bem vindo ao programa SEU EVENTO! \n\n    Para prosseguir, escolha um dos itens abaixo:\n");
  printf("\n 1 - Cadastrar novos eventos na agenda");
  printf("\n 2 - Listagem de todos os eventos da agenda");
  printf("\n 3 - Buscar dados de eventos de uma determinada data");
  printf("\n 4 - Mostrar os 5 próximos eventos a partir da data atual");
  printf("\n 5 - Remover um evento");
  printf("\n 6 - Sair do Programa e salvar as alterações.\n");
  scanf("%d", &escolha);
  if ((escolha!=1)&&(escolha!=2)&&(escolha!=3)&&(escolha!=4)&&(escolha!=5)&&(escolha!=6))
  {
    printf("\n\n\a DIGITE UM NÚMERO VÁLIDO DA PROXIMA VEZ \n");
    system("pause");
  }  
 }
 while ((escolha!=1)&&(escolha!=2)&&(escolha!=3)&&(escolha!=4)&&(escolha!=5)&&(escolha!=6));
      
switch (escolha){
       case 1: {
                    system("cls");
                    printf("\n CADASTRO DE EVENTOS \n\n");
                    leitura_dados();
                    system("pause");
                    break;
                 }
        case 2: {
					system("cls");
                    listagem_eventos();
				    system("pause");
                    break;
                 }  
		case 3:  {
					system("cls");
					int aux3;
					do
					{
					if (aux3>0)
					{
					printf("\n Digite uma data válida da próxima vez!");
					}
					printf("\n BUSCA DE EVENTO PELA DATA \n");
					printf("\n Digite a data do evento (formato DD/MM/AAAA):");
 					printf("\n Informe o dia: ");
 					scanf("%d",&dia2);
 					printf("\n Informe o mês: ");
 					scanf("%d",&mes2);
 					printf("\n Informe o ano: ");
 					scanf("%d",&ano2);
 					aux3++;
					}
					while (data_valida(dia2,mes2,ano2)==0);
					
 					
					buscar_por_data(dia2,mes2,ano2);
					system("pause");
					break;
				}		  
		case 4: {
                    system("cls");
                    mostrar_5_eventos();
                    system("pause");
                    break;
                }      
                 
        case 5: {
                    system("cls");
                    int opcao,aux1=0;
					int dia3,mes3,ano3;
					printf("\n REMOÇÃO DE EVENTO: ");
					do
					{
					if (aux1>0)
					{
					printf("\n Digite uma data válida da próxima vez!");
					}
					
					printf("\n Digite a data do evento (formato DD/MM/AAAA):");
	 				printf("\n Informe o dia: ");
	 				scanf("%d",&dia3);
	 				printf("\n Informe o mês: ");
	 				scanf("%d",&mes3);
	 				printf("\n Informe o ano: ");
	 				scanf("%d",&ano3);
	 				aux1++;
					}
					while (data_valida(dia3,mes3,ano3)!=1);

					 	
					remover_evento(dia3,mes3,ano3);
					
                    system("pause");
                    break;
                }        
        
        case 6:{ 	printf("\n Obrigado por utilizar o programa SEU EVENTO!\n Agradecemos a preferência!\n");
        			escreve_arquivo();
               		system("pause"); 
              }                             
      } // FIM DO switch
 
}
while(escolha!=6);

	
return 0;	
}

//função inserir novo evento na agenda
int leitura_dados()
{
 int i,cont1=0,cont2=0,cont3=0,cont4=0,cont5=0,cont6=0,cont7=0;
 

 if (posicao==MAX) 
	 { printf("\n  Agenda de Eventos Cheia!"); 
	   return 0;
	 }
 fflush(stdin);
 printf("\n Digite a data do evento (formato DD/MM/AAAA):");
 do
	 {
	 	if (cont1>0)
		 	{
		 	printf("\n Data inválida: digite uma data que exista dessa vez! ");
		 	}
	
	 	cont1++;
	 	printf("\n Informe o dia: ");
	 	scanf("%d",&Evento[posicao].Data.dia);
		printf("\n Informe o mês: ");
	    scanf("%d",&Evento[posicao].Data.mes);
	    printf("\n Informe o ano: ");
	    scanf("%d",&Evento[posicao].Data.ano);
	 
	 }
  while (data_valida(Evento[posicao].Data.dia,Evento[posicao].Data.mes,Evento[posicao].Data.ano)!=1);

 
 do
 {
 	if (cont6>0)
 	{
 	printf("\n Digite um horário válido da próxima vez!");	
	}
 printf("\n Digite o horário de início (formato digital):");
 cont6++;
 cont2=0,cont3=0,cont4=0,cont5=0;
 do
	 {
	 	if (cont2>0)
		 	{
		 	printf("\n Formato inválido para a hora: digite um um valor inteiro de 0 até 23 dessa vez! ");
		 	}
	 	else
		 	{
			printf("\n Informe a hora (um valor inteiro de 0 até 23): ");
			}
	 	cont2++;
	 	
	 	scanf("%d",&Evento[posicao].inicio.hora);
	 
	 }
  while ((Evento[posicao].inicio.hora<0)||(Evento[posicao].inicio.hora>23));
 
 do
	 {
	 	if (cont3>0)
		 	{
		 	printf("\n Formato inválido para os minutos: digite um um valor inteiro de 0 até 59 dessa vez! ");
		 	}
	 	else
		 	{
			printf("\n Informe os minutos (de 0 até 59): ");
			}
	 	cont3++;
	 	
	 	scanf("%d",&Evento[posicao].inicio.minuto);
	 
	 }
  while ((Evento[posicao].inicio.minuto<0)||(Evento[posicao].inicio.minuto>59));

 printf("\n Digite o horário de término (formato digital):");
 do
	 {
	 	if (cont4>0)
		 	{
		 	printf("\n Formato inválido para a hora: digite um um valor inteiro de 0 até 23 dessa vez! ");
		 	}
	 	else
		 	{
			printf("\n Informe a hora (um valor inteiro de 0 até 23): ");
			}
	 	cont2++;
	 	
	 	scanf("%d",&Evento[posicao].final.hora);
	 
	 }
  while ((Evento[posicao].final.hora<0)||(Evento[posicao].final.hora>23));
 
 do
	 {
	 	if (cont5>0)
		 	{
		 	printf("\n Formato inválido para os minutos: digite um um valor inteiro de 0 até 59 dessa vez! ");
		 	}
	 	else
		 	{
			printf("\n Informe os minutos (de 0 até 59): ");
			}
	 	cont3++;
	 	
	 	scanf("%d",&Evento[posicao].final.minuto);	 
	 }
  while ((Evento[posicao].final.minuto<0)||(Evento[posicao].final.minuto>59));
}
while ((Evento[posicao].inicio.hora>Evento[posicao].final.hora)||((Evento[posicao].inicio.hora==Evento[posicao].final.hora)&&(Evento[posicao].inicio.minuto>Evento[posicao].final.minuto)));
 
 printf("\n Digite o local do evento: ");
 fflush(stdin);
 do {fgets(Evento[posicao].local,200,stdin);} while( (strlen(Evento[posicao].local) < 1) == TRUE);
 fflush(stdin);
 printf("\n Digite a descrição do evento: ");
 do {fgets(Evento[posicao].descricao,200,stdin);} while( (strlen(Evento[posicao].descricao) < 1) == TRUE);
 fflush(stdin);

 for (i=0;i<posicao;i++)
 {
 	if (strcmpi(Evento[i].descricao,Evento[posicao].descricao)==0)
 	{
 		printf("\n Já existe um evento com esse nome! Insira outro evento da próxima vez!\n");
 		cont7++;
 		break;
	}
 }
if (cont7>0)
{
}
else
{

 Evento[posicao].status=1;
 posicao++;
 
     int j, k;

     for(j=0;j<posicao;j++)
	 {
          for(k=1;k<(posicao-j);k++)
		  {
               if (comparar_datas(Evento[k-1].Data.dia,Evento[k-1].Data.mes,Evento[k-1].Data.ano,Evento[k-1].inicio.hora,Evento[k-1].inicio.minuto,Evento[k].Data.dia,Evento[k].Data.mes,Evento[k].Data.ano,Evento[k].inicio.hora,Evento[k].inicio.minuto)==0)
			   {
                   evento temporario;
                   temporario=Evento[k-1];
                   Evento[k-1]=Evento[k];
                   Evento[k]=temporario;
               }
          }
     }
     
FILE *file5;
			file5 = fopen ( "DadosAgenda.bin", "rb" );
    
			if (file5) 
				{
			    fclose(file5);  
			    remove("DadosAgenda.bin");
    			}
					
			FILE *file6;

			file6 = fopen("DadosAgenda.bin", "wb");

			int q;
			
			if(file6)
				{
				for (q=0;q<(posicao);q++)
					{
						fwrite(&Evento[q].Data.dia,sizeof(int),1,file6);
						fwrite(&Evento[q].Data.mes,sizeof(int),1,file6);
						fwrite(&Evento[q].Data.ano,sizeof(int),1,file6);
			
						fwrite(&Evento[q].inicio.hora,sizeof(int),1,file6);
						fwrite(&Evento[q].inicio.minuto,sizeof(int),1,file6);
						fwrite(&Evento[q].final.hora,sizeof(int),1,file6);
						fwrite(&Evento[q].final.minuto,sizeof(int),1,file6);
				
						fwrite(&Evento[q].local,sizeof(char),200,file6);
						fwrite(&Evento[q].descricao,sizeof(char),200,file6);
					
						fwrite(&Evento[q].status,sizeof(int),1,file6);
					}	
				}
			else
				{
					printf(" Erro ao criar o arquivo!");
				}
			
			fclose(file6);

} 
 
}//fim

// listagem de todos os Eventos Cadastrados na Agenda.
int listagem_eventos()
	{	 
	 int quantidade = 0,i;
	 printf("\n\n\n*** Eventos da Agenda:\n");

	 for (i=0; i < posicao; i++)
	 { 

	 
	 	if (Evento[i].status==1)
		{
		
	   	printf("\n %s ", Evento[i].descricao);
	   	printf(" Data: %02d/%02d/%d", Evento[i].Data.dia,Evento[i].Data.mes,Evento[i].Data.ano);
	   	printf("\n Horário de Início: %02d:%02d",Evento[i].inicio.hora,Evento[i].inicio.minuto);
		printf(" Horário de Término: %02d:%02d\n",Evento[i].final.hora,Evento[i].final.minuto);	
	   	quantidade++;
		}
	 }
	printf("\n\n === Total de Eventos Cadastrados na Agenda: %d.  ===\n\n\n" ,quantidade);
	}
//fim

//função buscar evento pela data
int buscar_por_data (int dia,int mes,int ano)
{
int i;
for (i=0;i<MAX;i++)	
{
	if ((dia==Evento[i].Data.dia)&&(mes==Evento[i].Data.mes)&&(ano==Evento[i].Data.ano)&&Evento[i].status==1)
	{
	printf(" Evento: %s", Evento[i].descricao);
	printf(" Data: %02d/%02d/%d", Evento[i].Data.dia,Evento[i].Data.mes,Evento[i].Data.ano);
	printf("\n Horário de Início: %02d:%02d",Evento[i].inicio.hora,Evento[i].inicio.minuto);
	printf(" Horário de Término: %02d:%02d\n",Evento[i].final.hora,Evento[i].final.minuto);
	}
}
}//fim

//função para remover evento
int remover_evento (int dia,int mes,int ano)
{
int i,j,a,contador=0;
char escolha,nome_evento2[200];
	for (i=0;i<posicao;i++)
		{
			if ((Evento[i].Data.dia==dia)&&(Evento[i].Data.mes==mes)&&(Evento[i].Data.ano==ano))
				{
				contador++;
				a=i;	
				}
		}
	if (contador==0)
		{
		printf("Nenhum evento encontrado nessa data!");	
		return 0;
		}
	if (contador==1)
	{
		printf("\n Evento encontrado: ");
		printf("%s", Evento[a].descricao);
		printf(" Data: %02d/%02d/%d", Evento[a].Data.dia,Evento[a].Data.mes,Evento[a].Data.ano);
		printf("\n Horário de Início: %02d:%02d",Evento[a].inicio.hora,Evento[a].inicio.minuto);
		printf(" Horário de Término: %02d:%02d\n",Evento[a].final.hora,Evento[a].final.minuto);
		printf(" Deseja excluir este evento? Se SIM digite 'S', se NÃO digite 'N': ");
		scanf(" %c", &escolha);
		if (escolha=='S'||escolha=='s')
			{	
			
			FILE *file3;
			file3 = fopen ( "DadosAgenda.bin", "rb" );
    
			if (file3) 
				{
			    fclose(file3);  
			    remove("DadosAgenda.bin");
    			}
					
			FILE *file4;

			file4 = fopen("DadosAgenda.bin", "wb");

			int k;
			
			if(file4)
				{
				for (k=0;k<(posicao);k++)
					{
					if((Evento[k].Data.dia==dia)&&(Evento[k].Data.mes==mes)&&(Evento[k].Data.ano==ano))
						{
						} 
					else
						{
						fwrite(&Evento[k].Data.dia,sizeof(int),1,file4);
						fwrite(&Evento[k].Data.mes,sizeof(int),1,file4);
						fwrite(&Evento[k].Data.ano,sizeof(int),1,file4);
			
						fwrite(&Evento[k].inicio.hora,sizeof(int),1,file4);
						fwrite(&Evento[k].inicio.minuto,sizeof(int),1,file4);
						fwrite(&Evento[k].final.hora,sizeof(int),1,file4);
						fwrite(&Evento[k].final.minuto,sizeof(int),1,file4);
				
						fwrite(&Evento[k].local,sizeof(char),200,file4);
						fwrite(&Evento[k].descricao,sizeof(char),200,file4);
					
						fwrite(&Evento[k].status,sizeof(int),1,file4);
						}
					
					}
				}
			else
				{
					printf(" Erro ao criar o arquivo!");
				}
			
			fclose(file4);
			
			}
	}
	if (contador>1)
	{
	printf("\n Múltiplos eventos encontrados: ");
	for (i=0;i<posicao;i++)
		{
			if ((Evento[i].Data.dia==dia)&&(Evento[i].Data.mes==mes)&&(Evento[i].Data.ano==ano))
				{
				printf("\n %s", Evento[i].descricao);
				printf(" Data: %02d/%02d/%d", Evento[i].Data.dia,Evento[i].Data.mes,Evento[i].Data.ano);
				printf("\n Horário de Início: %02d:%02d",Evento[i].inicio.hora,Evento[i].inicio.minuto);
				printf(" Horário de Término: %02d:%02d",Evento[i].final.hora,Evento[i].final.minuto);
				}
		}
	printf("\n Digite o nome do evento que você quer excluir: ");
	fflush(stdin);
	fgets(nome_evento2,200,stdin);
	
	FILE *file3;
	file3 = fopen ( "DadosAgenda.bin", "rb" );
	
	if (file3) 
				{
			    fclose(file3);  
			    remove("DadosAgenda.bin");
    			}	
					
    	FILE *file7;

		file7 = fopen("DadosAgenda.bin", "wb");	
	int k;				
	for (k=0;k<posicao;k++)
	{
		if (strcmpi(Evento[k].descricao,nome_evento2)!=0)
			{		
					fwrite(&Evento[k].Data.dia,sizeof(int),1,file7);
					fwrite(&Evento[k].Data.mes,sizeof(int),1,file7);
					fwrite(&Evento[k].Data.ano,sizeof(int),1,file7);
			
					fwrite(&Evento[k].inicio.hora,sizeof(int),1,file7);
					fwrite(&Evento[k].inicio.minuto,sizeof(int),1,file7);
					fwrite(&Evento[k].final.hora,sizeof(int),1,file7);
					fwrite(&Evento[k].final.minuto,sizeof(int),1,file7);
				
					fwrite(&Evento[k].local,sizeof(char),200,file7);
					fwrite(&Evento[k].descricao,sizeof(char),200,file7);
					
					fwrite(&Evento[k].status,sizeof(int),1,file7);
			
			}	
			else
			{
			}	
	}
	fclose(file7);
	}
}//fim

//função para dizer se uma data é válida, 0 para não e 1 para sim
int data_valida (int dia,int mes,int ano)
{
if (mes<1||mes>12)	
{
	return 0;
}
if (dia<1||dia>31)
{
	return 0;
}
if ((mes==4||mes==6||mes==7||mes==9||mes==11)&&(dia==31))
{
	return 0;
}
if (mes==2)
{
	if (dia>29)
	{
		return 0;
	}
	if (dia==29)
	{
		if (ano_bissexto(ano)==1)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 1;
	}
}
else
{
	return 1;
}
	
}//fim

//função para mostrar os 5 próximos eventos a partir da data atual
int mostrar_5_eventos ()
{
struct tm *data_hoje;	

//variável do tipo time_t para armazenar o tempo em segundos  
time_t segundos;
    
time(&segundos);   
  
//para converter de segundos para o tempo local    
data_hoje = localtime(&segundos);  	
	
int day1,month1,year1,hour1,minute1,day2,month2,year2,hour2,minute2,l;
day1=data_hoje->tm_mday;
month1=data_hoje->tm_mon+1;
year1=data_hoje->tm_year+1900;
hour1=data_hoje->tm_hour;
minute1=data_hoje->tm_min;
	
for (l=0;l<=posicao;l++)
	{
	int n=l;
	day2=Evento[l].Data.dia;
	month2=Evento[l].Data.mes;
	year2=Evento[l].Data.ano;
	hour2=Evento[l].final.hora;
	minute2=Evento[l].final.minuto;
	
	if (comparar_datas(day1,month1,year1,hour1,minute1,day2,month2,year2,hour2,minute2)==1)
		{
			for (n;n<l+5;n++)
			{
			if (n==posicao)
				{
				break;
				}
			else
				{
				printf("\n Evento: %s ",Evento[n].descricao);
				printf("Data: %02d/%02d/%d",Evento[n].Data.dia,Evento[n].Data.mes,Evento[n].Data.ano);
				printf("\n Horário de Início: %02d:%02d",Evento[n].inicio.hora,Evento[n].inicio.minuto);
				printf(" Horário de Término: %02d:%02d\n",Evento[n].final.hora,Evento[n].final.minuto);	
				}
			
			}
		break;
		}	
	}
	
	
}//fim

//função para dizer se o ano é bissexto - 1 para sim 0 para não
int ano_bissexto (int ano)
{
	if (ano%4==0)
	{
		if (ano%100==0)
		{
			if (ano%400==0)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 1;
		}
	}
	else 
	{
		return 0;
	}
}//fim

//função para comparar datas e decidir qual é mais antiga
//1 para data1 mais antiga do que data2 ou 0 para data1 mais avançada no futuro do que data2
int comparar_datas (int dia1,int mes1,int ano1,int hora1,int minuto1,int dia2,int mes2,int ano2,int hora2,int minuto2)
{
	if (ano1<ano2)
	{
		return 1;
	}
	if (ano1>ano2)
	{
		return 0;
	}
	if (ano1==ano2)
	{
		if (mes1<mes2)
		{
			return 1;
		}
		if (mes1>mes2)
		{
			return 0;
		}
		if (mes1==mes2)
		{
			if (dia1<dia2)
			{
				return 1;
			}
			if (dia1>dia2)
			{
				return 0;
			}
			if (dia1==dia2)
			{
				if (hora1<hora2)
				{
					return 1;
				}
				if (hora1>hora2)
				{
					return 0;
				}
				if (hora1==hora2)
				{
					if (minuto1<minuto2)
					{
						return 1;
					}
					if (minuto1>minuto2)
					{
						return 0;
					}
					if (minuto1==minuto2)
					{
						return 1;//se os evenetos são na mesma hora então tanto faz a ordem que eles estão
					}
				}
			}
		}
	}
}//fim

//função para colocar dados no arquivo ao finalizar o programa
int escreve_arquivo ()
{
FILE *file2;

file2 = fopen("DadosAgenda.bin", "wb");

int i;

if(file2)
{
	for (i=0;i<posicao;i++)
	{
		fwrite(&Evento[i].Data.dia,sizeof(int),1,file2);
		fwrite(&Evento[i].Data.mes,sizeof(int),1,file2);
		fwrite(&Evento[i].Data.ano,sizeof(int),1,file2);
	
		fwrite(&Evento[i].inicio.hora,sizeof(int),1,file2);
		fwrite(&Evento[i].inicio.minuto,sizeof(int),1,file2);
		fwrite(&Evento[i].final.hora,sizeof(int),1,file2);
		fwrite(&Evento[i].final.minuto,sizeof(int),1,file2);
	
		fwrite(&Evento[i].local,sizeof(char),200,file2);
		fwrite(&Evento[i].descricao,sizeof(char),200,file2);
		
		fwrite(&Evento[i].status,sizeof(int),1,file2);
	}	
}
else
{
	printf(" Erro ao criar o arquivo!");
}

fclose(file2);
printf("\n O arquivo DadosAgenda.bin foi criado com sucesso!\n");

}//fim
