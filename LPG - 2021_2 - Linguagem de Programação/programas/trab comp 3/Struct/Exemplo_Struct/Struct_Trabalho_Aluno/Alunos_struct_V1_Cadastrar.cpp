/* Autora: Professora Claudia Werlich - clawer@gmail.com
Pode ser utilizado: mas insira os devidos créditos para a Autora */

//Data: 16/05/2019

/*PROGRAMA COM STRUCT
TABELA ALUNO = codigo,existe,nome,sobrenome,notas(limite de 10), 
               media (campo calculado), dt nasc, casado?, salário, curso (escolher os cadastrados).

*/
#include<string.h>
#include<stdio.h>
#include<iostream>
#include<conio.h>
#include<string.h>

using namespace std;
//#include<claudia.h> -- > INSIRA A SUA BIBLIOTECA AQUI <---

int const TAM=2;
int const TAM_curso=6;

typedef struct 
      { int dia;
        int mes;
        int ano;
        }datas;
  
       
 struct dados_aluno 
{ int codigo;
  char nome[45];
  char sobrenome[45];
  int cadastrado;
  float media;
  float notas[10];
  float salario;
  int casado;
  char curso[15];
  datas data;
        
};  
dados_aluno  Aluno[TAM];  


char cursos[TAM_curso][25]={"Informatica","Mecanica","Plastico","Metalurgia","Design","Edificacoes"};
int dd,mm,aa,data_ok;

//AREA DAS FUNÇÕES LOCAIS USADAS PARA SEPARAR AS TAREFAS
//Protótipos das funções

void cadastrar();


//void mostra_cursos();
//void consulta_por_nome();
//void consulta_por_curso();
//void consulta_por_media();
//void alterar_por_codigo();
//void alterar_por_nome();
//void alterar_por_sobrenome();
//void excluir_por_codigo();
//void excluir_por_nome();
//void relatorios_alunos_notas();
//void relatorios_alunos_cursos();
//int testa_data_informada(int dia,int mes,int ano);

//variaveis do programa principal
int opcao,opcao_cons,cadastrou=0;
char resp_op;
int op_curso_escolhido;

//INICIO DO PROGRAMA
main()
{
  using namespace std;
        
  do{
      do{ //para testar a opcao errada do menu
          system("cls");
          cout<<"\n PROGRAMA CONTROLE DE ALUNOS";
          cout<<"\n\n ESCOLHA UM DOS ITENS ABAIXO:";
          cout<<"\n\n [1]- CADASTRAR";
          cout<<"\n\n [2]- CONSULTAR";
          cout<<"\n\n [3]- ALTERAR";
          cout<<"\n\n [4]- EXCLUIR";
          cout<<"\n\n [5]- RELATORIOS";
          cout<<"\n\n [6]- FIM \n\n";
          cin>> opcao;
          if ((opcao!=1)&&(opcao!=2)&&(opcao!=3)&&(opcao!=4)&&(opcao!=5)&&(opcao!=6))
               {
                 cout<<" \n DIGITE CERTO DA PROXIMA VEZ \n\n\n";
                 system("pause");
                 }  
        }while ((opcao!=1)&& (opcao!=2)&&(opcao!=3)&&(opcao!=4)&&(opcao!=5)&&(opcao!=6));
      
      switch (opcao){
       case 1: {
                 if (cadastrou==0) // somente cadastra se a tabela estiver vazia
                 {
                    system("cls");
                    cout<<"\n CADASTRO DE ALUNOS                 ";
                    cadastrar();
                    cadastrou=1; // Para cadastrar somente uma vez
                  }  
                  else
                    cout<<"\n Os dados ja foram cadastrados\n\n\n";
                    system("pause");
                   break;
                 }
       case 2: {
                 do{
                    system("cls");  
                    cout<<"\n CONSULTA AOS ALUNOS ";
                    if (cadastrou==1)
                    {
                     do{ //para testar a opcao errada do menu
                        system("cls");
                        cout<<"\n PROGRAMA CONTROLE DE ALUNOS";
                        cout<<"\n\n ESCOLHA UM DOS ITENS ABAIXO:";
                        cout<<"\n\n [1]- Consultar por Nome";
                        cout<<"\n\n [2]- Consultar por Curso";
                        cout<<"\n\n [3]- Consultar por Media  ";
                        cout<<"\n\n [4]- FIM \n\n";
                        cin>> opcao_cons;
                        if ((opcao_cons!=1)&&(opcao_cons!=2)&&(opcao_cons!=3)&&(opcao_cons!=4))
                        {
                           cout<<" \n DIGITE CERTO DA PROXIMA VEZ \n\n\n";
                           system("pause");
                        }  
                      }while ((opcao_cons!=1)&& (opcao_cons!=2)&&(opcao_cons!=3)&&(opcao_cons!=4));
                   
                    switch (opcao_cons){
                     case 1:{
                            //  consulta_por_nome();
                             break;
                            } 
                      case 2:{
                            //  consulta_por_curso();
                             break;
                            }    
                     case 3:{
                           //   consulta_por_media();
                             break;
                            }            
                      }// switch
                   }
                else
                    {
                       cout<<"\n Nao temos alunos cadastrados";
                       system("pause");
                       }     
                    
                 }while (opcao_cons!=4);    
                 
                  
                   break;
                 }
                 
           case 3: {
                   do{
                    system("cls");  
                    cout<<"\n ALTERANDO  REGISTROS ";
                    if (cadastrou==1)
                    {
                      do{ //para testar a opcao errada do menu
                        system("cls");
                        cout<<"\n\n ESCOLHA UM DOS ITENS ABAIXO:";
                        cout<<"\n\n [1]- Alterar por Codigo";
                        cout<<"\n\n [2]- Alterar por Nome";
                        cout<<"\n\n [3]- Alterar por Sobrenome  ";
                        cout<<"\n\n [4]- FIM \n\n";
                        cin>> opcao_cons;
                        if ((opcao_cons!=1)&&(opcao_cons!=2)&&(opcao_cons!=3)&&(opcao_cons!=4))
                        {
                           cout<<" \n DIGITE CERTO DA PROXIMA VEZ \n\n\n";
                           system("pause");
                           
                        }
                      }while ((opcao_cons!=1)&& (opcao_cons!=2)&&(opcao_cons!=3)&&(opcao_cons!=4));
                   switch (opcao_cons)
                   {
                     case 1:{
                           //   alterar_por_codigo();
                              break;
                            } 
                      case 2:
                            {
                           //   alterar_por_nome();
                              break;
                            }    
                     case 3:{
                           //   alterar_por_sobrenome();
                              break;
                            }            
                      }// switch
                   }
                else
                    {
                       cout<<"\n Nao temos alunos cadastrados";
                       cout<<"\n\n\n"; 
                       system("pause");
                     }     
                    
                 }while (opcao_cons!=4); 
                 break;
                 }  
            case 4: {
                   do{
                    system("cls");  
                    cout<<"\n EXCLUINDO  REGISTROS ";
                    if (cadastrou==1)
                    {
                      do{ //para testar a opcao errada do menu
                        system("cls");
                        cout<<"\n\n ESCOLHA UM DOS ITENS ABAIXO:";
                        cout<<"\n\n [1]- Excluir por Codigo";
                        cout<<"\n\n [2]- Excluir por Nome";
                        cout<<"\n\n [3]- FIM \n\n";
                        cin>> opcao_cons;
                        if ((opcao_cons!=1)&&(opcao_cons!=2)&&(opcao_cons!=3))
                        {
                           cout<<" \n DIGITE CERTO DA PROXIMA VEZ \n\n\n";
                           system("pause");
                           
                        }
                      }while ((opcao_cons!=1)&& (opcao_cons!=2)&&(opcao_cons!=3));
                   switch (opcao_cons)
                   {
                     case 1:{
                           //   excluir_por_codigo();
                              break;
                            } 
                      case 2:
                            {
                           //   excluir_por_nome();
                              break;
                            } 
                   }//switch
                   }//if 
                   }while ((opcao_cons!=1)&& (opcao_cons!=2)&&(opcao_cons!=3));        
                 break;
                }           
               case 5: 
                    {
                   do{
                    system("cls");  
                    cout<<"\n RELATÓRIOS ";
                    if (cadastrou==1)
                    {
                      do{ //para testar a opcao errada do menu
                        system("cls");
                        cout<<"\n\n ESCOLHA UM DOS ITENS ABAIXO:";
                        cout<<"\n\n [1]- Relatorio dos Alunos e Suas Notas";
                        cout<<"\n\n [2]- Relatorio dos Alunos e Seus Cursos";
                        cout<<"\n\n [3]- FIM \n\n";
                        cin>> opcao_cons;
                        if ((opcao_cons!=1)&&(opcao_cons!=2)&&(opcao_cons!=3))
                        {
                           cout<<" \n DIGITE CERTO DA PROXIMA VEZ \n\n\n";
                           system("pause");
                           
                        }
                      }while ((opcao_cons!=1)&& (opcao_cons!=2)&&(opcao_cons!=3));
                   switch (opcao_cons)
                   {
                     case 1:{
                          //    relatorios_alunos_notas();
                              break;
                            } 
                      case 2:
                            {
                           //   relatorios_alunos_cursos();
                              break;
                            }    
                      
                      }// switch
                   }//if
                else
                    {
                       cout<<"\n Nao temos alunos cadastrados";
                       system("pause");
                     }     
                    
                 }while (opcao_cons!=3); 
                   break;
                 } 
             case 6: 
                    { cout<<"\n Obrigada Por Utilizar Meu Programa";
                      cout<<"\n\n Se encontrar problemas:\n \tResolva e Mande-me a Resposta\n\n";
                      system("pause"); 
                    }                             
      } // FIM DO switch
 
}while(opcao!=6);     
      
  
   
} 
//FIM DO PROGRAMA     
//===============================================================================

//AREA DAS FUNÇÕES LOCAIS




//===============================================================================

// FUNÇÃO CADASTRO DO REGISTRO 
void cadastrar()
{
  int i,codigo_novo,qtde_notas;
  float soma=0;
  
  for(i=0;i<TAM;i++)
   {
        soma=0;
        cout<<"\n\n==================================================\n";
        Aluno[i].cadastrado=1;
        
        cout<<"\n Digite o Codigo do Aluno   " <<i+1<<" :  ";
        cin>>codigo_novo; 
		
		 // Gerar com numeros aleatórios
        Aluno[i].codigo=codigo_novo;
        
        printf("Digite o Nome do Aluno:  "); //leitura para o char nome[45]
        scanf("%s",&Aluno[i].nome);
        
        
        
        printf("Digite o Sobrenome do Aluno:  ");
        scanf("%s",&Aluno[i].sobrenome);
        
        
        cout<<"\n Digite o Salario do Aluno:  ";
        cin>>Aluno[i].salario;
        
        
        
       // mostra_cursos();
        cout<<"\n Escolha uma Opcao:  ";
        cin>>op_curso_escolhido;
        switch (op_curso_escolhido){
            case 1: {//copia o curso de informatica ( q é um vetor de char para a variavel Aluno[i].curso
                     strcpy(Aluno[i].curso,cursos[op_curso_escolhido-1]); // serve para copiar um texto para outro texto
                     break;
                     } 
            case 2: {
                     strcpy(Aluno[i].curso,cursos[op_curso_escolhido-1]);
                     break;
                     } 
            case 3: {
                     strcpy(Aluno[i].curso,cursos[op_curso_escolhido-1]);
                     break;
                     } 
            case 4: {
                     strcpy(Aluno[i].curso,cursos[op_curso_escolhido-1]);
                     break;
                     } 
            case 5: {
                     strcpy(Aluno[i].curso,cursos[op_curso_escolhido-1]);
                     break;
                     }                                        
        
        }//fecha o switch
        cout<<" \n\n CURSO ESCOLHIDO CONFERIR? "<<Aluno[i].curso;  //ARRUMAR PARA TEM CERTEZA? QUER TROCAR?
        do{
         cout<<"\n Quantas notas esse aluno possui? Limite deve ser 10:  ";                     
         cin>>qtde_notas;
         if ((qtde_notas<0)||(qtde_notas>10))
              cout<<"\n\a\n\a ERRO LIMITE É DE 10 NOTAS:  ";
         }while ((qtde_notas<0)||(qtde_notas>10));
         for(int cont_i=0;cont_i<qtde_notas;cont_i++)
            {
              cout<<"\n Informe a  "<<cont_i+1<<" a Nota ";
              cin>>Aluno[i].notas[cont_i];
              soma=soma+Aluno[i].notas[cont_i];
            }  
         Aluno[i].media=soma/qtde_notas;
         cout<<"\n Sua Media eh:  "<<Aluno[i].media;
         cout<<"\n Digite: [0] - Solteiro   [1] - Casado "; // ARRUMAR PARA NÃO ENTRAR VALOR ERRADO
         cin>>Aluno[i].casado; // arrumar com o do
         do{
         cout<<"\n Informe a data do seu aniversario";
         cout<<"\n Informe o dia: ";  
         cin>>dd;
         cout<<"\n Informe o mes:  ";
         cin>>mm;
         cout<<"\n Informe o ano:  ";
         cin>>aa;
        // data_ok=testa_data_informada(dd,mm,aa);
         if(data_ok==0)
          { 
            Aluno[i].data.dia=dd;
            Aluno[i].data.mes=mm;
            Aluno[i].data.ano=aa;
          }
         else
         {cout<<"\n\n ERRO - DATA INVALIDA - INFORME A DATA NOVAMENTE ";
         }
         }while(data_ok==1);  
         } 
}  //fim
//===============================================================================

// função consultar por nome


//===============================================================================

//função consultar por curso

 
 //===============================================================================          

//função consultar pela media dos alunos           


 
//===============================================================================                   
      


//===============================================================================

//função alterar os registros - procura pelo nome
     

//===============================================================================

//função para alterar o registro por sobrenome


//===============================================================================

//função excluir por código - exclusão lógica


//===============================================================================
    
//função excluir por nome - exclusão lógica

                 
//===============================================================================

//função relatórios - listagem 


//===============================================================================

//função relatórios - listagem     


//======================================================
// funçao testa a data informada


 
