#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define SA_MAX 1 //número de vizinhos analisados //30 funciona bem
//1 é o padrão da maioria dos algoritmos
#define N 12500 //numero de iterações total 
#define T0 100
#define Tn 0.001
#define K 1.0 //constante de Bolzmann -> quanto maior, maior probabilidade de aceitação
              // -> quanto menor, menor a probabilidade de aceitação

#define MAX_ALTERACOES 2
#define BOXPLOT_NUM 30

typedef struct {
    int indices[300]; // no máximo dois índices modificados
    int count;      // 1 ou 2
} Alteracao;

typedef struct {
    int literais[3];
} InstanciaSAT;

InstanciaSAT *arquivoLido = NULL;

int num_vars, num_clauses;

//linear
double coolingSchedule0 (int i, double Ti) {
	return T0 - i*(T0-Tn)/N;

}

//exponencial
double coolingSchedule1 (int i, double Ti) {
	return T0 * (pow((Tn/T0), ((double)i/N)));;
}

//hiperbolica inversa -> crescimento inversamente proporcional
double coolingSchedule2 (int i, double Ti) {
	double A = ((T0 - Tn)*(N+1))/N;
	double B = T0 - A;
	return (A/(i+1)) + B;
}

double coolingSchedule3 (int i, double Ti) {
	double A = (log(T0 - Tn))/(log(N));
	return T0 - pow(i, A);
}

//sigmoidal
double coolingSchedule4 (int i, double Ti) {
	double B = 3.0;
	//valores maiores, sigmoidal com mudança mais brusca
	//valores menores de B, curva mais suave
	return ((T0 - Tn)/(1 + pow(exp(1.0), (B * (i - N/2) ))  )) + Tn;
}

double coolingSchedule5 (int i, double Ti) {
	return ( ((T0 - Tn)/2.0) * (1 + cos((i * M_PI)/N) ) ) + Tn;
}

double coolingSchedule6 (int i, double Ti) {
	double k = 5;
	return ((T0 - Tn)/2.0 * (1 - tanh((k*i)/N - 5.0)) ) + Tn;
}

double coolingSchedule7 (int i, double Ti) {
	double k = 10;
	return ((T0 - Tn)/(cosh((k*i)/N)) ) + Tn;
}

double coolingSchedule8 (int i, double Ti) {
	double A = (1.0/(N*N))*(log(T0/Tn));
	return T0 * exp(-1.0 * A * i);
}

double coolingSchedule9 (int i, double Ti) {
	double A = (1.0/N)*(log(T0/Tn));
	return T0 * exp(-1.0 * A * i * i);
}

//---------------------------------------------------------------------------------------

bool* criarVetor(int tamanho) {
    bool* vetor = (bool*)malloc(tamanho * sizeof(bool));  // Aloca memória para o vetor
    if (vetor == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    return vetor;
}

void read_cnf_file(const char *filename) {
	int index = 0;
	
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

	char ch;
    while (fscanf(file, " %c", &ch) == 1) {  // Lê o primeiro caractere não branco da linha
        if (ch == 'c') {
            while (fgetc(file) != '\n');  // Ignora a linha do comentário
        } 
        else if (ch == 'p') {
            char format[10];
            fscanf(file, "%s %d %d", format, &num_vars, &num_clauses);  // Lê "cnf num_vars num_clauses"
        	
			arquivoLido = malloc(num_clauses * sizeof(InstanciaSAT));// Agora que sabemos quantas cláusulas são, aloca fórmula
			if (arquivoLido == NULL) {
			    fprintf(stderr, "Erro ao alocar memória para as cláusulas.\n");
			    exit(1);
			}
		} 
        else if  (ch == '%') {
            break;
		} else {  
            ungetc(ch, file);  // Devolve o caractere para ser lido corretamente
            
            
            int end;
            int lit [3];
            if (fscanf(file, "%d %d %d %d", &lit[0], &lit[1], &lit[2], &end) == 4 && end == 0) {
			
					
            	arquivoLido[index].literais[0] = lit [0];
            	arquivoLido[index].literais[1] = lit [1];
            	arquivoLido[index].literais[2] = lit [2];
        		index++;
            }
        }

    }
    
	printf("Numero de clausulas: %d\n", index);
    fclose(file);

}

int evaluate(bool *vetor) {
	int count_erros = 0;
	
	int i;
	for (i = 0; i < num_clauses; i++) {
        bool clause_satisfied = false;

        for (int j = 0; j < 3; j++) {
            int variavel = arquivoLido[i].literais[j];
            bool value;

            if (variavel > 0) {
                value = vetor[variavel - 1];  // variável positiva
            } else {
                value = !vetor[(-variavel) - 1];  // variável negativa
            }

            if (value) {
                clause_satisfied = true;
                break;  // Se qualquer literal satisfaz a cláusula, pode parar
            }
        }

        if (!clause_satisfied) {
            count_erros++;  // A cláusula não foi satisfeita
        }
    }
    
    return count_erros;
}

void printVetorInt(int *vetor, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

void printVetorBool(bool *vetor, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i] ? 1 : 0);
    }
    printf("\n");
}

void copiarVetorBool(bool *destino, bool *origem, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        destino[i] = origem[i];
    }
}

//estratégia light -> só bit flip -> na prática não funcionou mt bem
Alteracao gerarVizinho0(bool *vizinho, const bool *solucao) {
	Alteracao alt;
    alt.count = 0;
    
    for (int i = 0; i < num_vars; i++) {
        vizinho[i] = solucao[i];
    }
    
    int i = rand() % num_vars;
    vizinho[i] = !vizinho[i];

    alt.indices[0] = i;
    alt.count = 1;

    return alt;
}

//estratégia suave -> poucos vizinhos locais
Alteracao gerarVizinho1(bool *vizinho, const bool *solucao) {
    Alteracao alt;
    alt.count = 0;

    for (int i = 0; i < num_vars; i++) {
        vizinho[i] = solucao[i];
    }

    int metodo = rand() % 2;

    if (metodo == 0) {
	
	//int num_flips = 1 + rand() % MAX_ALTERACOES;  // entre 1 e MAX_ALTERACOES bitflips
	int num_flips = MAX_ALTERACOES;
	int k;
        for (k = 0; k < num_flips; k++) {
            int idx = rand() % num_vars;

            // Evita flipar o mesmo índice mais de uma vez
            int repetido = 0;
            for (int j = 0; j < alt.count; j++) {
                if (alt.indices[j] == idx) {
                    repetido = 1;
                    break;
                }
            }
            if (repetido) {
                k--;  // tenta outro
                continue;
            }

            vizinho[idx] = !vizinho[idx];
            alt.indices[alt.count++] = idx;

            if (alt.count >= MAX_ALTERACOES) break;  // limite de segurança
        }

    } else {  // inverte um bit
        int i = rand() % num_vars;
        vizinho[i] = !vizinho[i];

        alt.indices[0] = i;
        alt.count = 1;
    }

    return alt;
}

//estratégia agressiva -> não fica preso eternamente em máximo local
Alteracao gerarVizinho2(bool *vizinho, const bool *solucao) {
    Alteracao alt;
    alt.count = 0;

    for (int i = 0; i < num_vars; i++) {
        vizinho[i] = solucao[i];
    }
    
    int metodo = rand() % 3; // Escolhe um dos três métodos
	
	if (metodo == 0) {
	
	//int num_flips = 1 + rand() % MAX_ALTERACOES;  // entre 1 e MAX_ALTERACOES bitflips
	int num_flips = MAX_ALTERACOES;
	int k;
        for (k = 0; k < num_flips; k++) {
            int idx = rand() % num_vars;

            // Evita flipar o mesmo índice mais de uma vez
            int repetido = 0;
            for (int j = 0; j < alt.count; j++) {
                if (alt.indices[j] == idx) {
                    repetido = 1;
                    break;
                }
            }
            if (repetido) {
                k--;  // tenta outro
                continue;
            }

            vizinho[idx] = !vizinho[idx];
            alt.indices[alt.count++] = idx;

            if (alt.count >= MAX_ALTERACOES) break;  // limite de segurança
        }

    } else if (metodo == 1) {  // inverte um bit
        int i = rand() % num_vars;
        vizinho[i] = !vizinho[i];

        alt.indices[0] = i;
        alt.count = 1;
    } else if (metodo == 2) {
    	alt.count = 0;
    	for (int i = 0; i < num_vars; i++) {
        	vizinho[i] = rand() % 2;
        	alt.indices[i] = i;
        	alt.count = alt.count + 1;
    	}
	}
    return alt;
}

int main () {// nessa versão analisa todos os vizinhos e se decide pelo melhor entre eles
// Aceitação com Probabilidade em Cada Vizinho
	srand(time(NULL));
	
	//"uf20-01.cnf"
	//"uf100-01.cnf"
	const char *nomearquivo = "uf250-01.cnf";
	read_cnf_file(nomearquivo);
	
	FILE *saida = fopen("saida_boxplot_3.txt", "a");
		if (saida == NULL) {
			perror("Erro ao criar o arquivo de saída");
			exit(1);
		}
	
	int c = 1;
	while(c < (BOXPLOT_NUM + 1)){
		int melhor_global = num_clauses;
		
		
		//printf("%d\n", num_vars);
		double T=T0;
		
		// Inicializar solução aleatória
		bool *solution = criarVetor(num_vars);
	    for (int i = 0; i < num_vars; i++) {
	        solution[i] = rand() % 2;
	    }
	    //printVetorBool(solution, num_vars); //teste aleatoriedade
	    bool *vizinho = criarVetor(num_vars); // apenas uma vez
		
		int i = 1; //iterações decaimento temperatura
		
		int currentValue;//numero de erros agora
		
		
		while (T > Tn && i <= N) {
			//printf("\n%d", i);
			currentValue = evaluate(solution);
			////printf("%d", currentValue);
			int iterations = 0;
			while (iterations < SA_MAX) {
				//printf("%d", iterations);
				iterations++;
				Alteracao alt = gerarVizinho0(vizinho, solution);//gerar vizinho
				//printVetorBool(vizinho, num_vars);  //teste se a geração está funcionando
				int valueVizinho = evaluate(vizinho);
				
				int delta = valueVizinho - currentValue;//calcular delta entre performance atual e performance anterior
				
				if (delta < 0) {// if delta < 0 then Tcurrent = newT
					for (int k = 0; k < alt.count; k++) {
				        solution[alt.indices[k]] = vizinho[alt.indices[k]];
				    }
					currentValue = valueVizinho;
					if (valueVizinho < melhor_global) {
						melhor_global = valueVizinho;//if f(newT) < f(Tcurrent) then melhor global = newT
						if (melhor_global == 0) {
							break;
						}
						//break;
					}
				} else {// else probabilidade e^alguma coisa (aceitar solução pior)
					double pPior = exp(-delta/(K * T));
					double r = (double)rand() / RAND_MAX;
					if (r < pPior) {
						for (int k = 0; k < alt.count; k++) {
					        solution[alt.indices[k]] = vizinho[alt.indices[k]];
					    }
						currentValue = valueVizinho;
					}
				}
				
				//fprintf(saida, "%d,%.6f,%d,%d\n", i, T, currentValue, melhor_global); // Salva os dados
			}
			////printf("%d", currentValue);
			//fprintf(saida, "%d,%.6f,%d,%d\n", i, T, currentValue, melhor_global);
			if (melhor_global == 0) {
				break;
			}
			
			//T = T * 0.999; //-> diminui rápido d+
			T = coolingSchedule2(i, T); // nova temperatura
			
			i++;
			if (i % 100 == 0) {
				float k = (100.0 * i) / N;
			    printf("%.2f%% Completos\n", k);
			}
			iterations = 0;
			
		}
		fprintf(saida, "%d\n", currentValue);
		free(vizinho);
		
		
		free(solution);
		c++;
	}
	
	fclose(saida);
	//print melhor global;
	
	//printf("\n%d\n", currentValue);
	
	//system("python Simulated_Annealing-SAT-boxplot.py");
	
	
	
	//bool teste[20] = {true, false, false, true, false, false, false, true, false, true, false, false, true, true, true, false, true, false, false, true};
	
	free(arquivoLido);
	return 0;
}




