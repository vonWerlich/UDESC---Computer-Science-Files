#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define SA_MAX 1 //número de vizinhos analisados //30 funciona bem
//1 é o padrão da maioria dos algoritmos
#define N 100000 //numero de iterações total 
#define T0 100
#define Tn 0.001
#define K 1.0 //constante de Boltzmann -> quanto maior, maior probabilidade de aceitação
              // -> quanto menor, menor a probabilidade de aceitação

#define MAX_ALTERACOES 2
#define BOXPLOT_NUM 30

typedef struct {
    double x, y; // Coordenadas da cidade
} Cidade;

typedef struct {
    int literais[3];
} InstanciaSAT;

Cidade *cidades = NULL;
double **distancias = NULL;
int num_vars = 0;

InstanciaSAT *arquivoLido = NULL;

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
	double B = 0.0005;
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

void read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), file)) {
        if (strncmp(buffer, "DIMENSION", 9) == 0) {
            sscanf(buffer, "DIMENSION : %d", &num_vars);

            cidades = (Cidade *) malloc(num_vars * sizeof(Cidade));
            if (cidades == NULL) {
                perror("Erro ao alocar vetor de cidades");
                exit(EXIT_FAILURE);
            }

            // Só agora aloca matriz de distâncias também
            distancias = (double **) malloc(num_vars * sizeof(double *));
            if (distancias == NULL) {
                perror("Erro ao alocar matriz de distâncias");
                exit(EXIT_FAILURE);
            }
            for (int i = 0; i < num_vars; i++) {
                distancias[i] = (double *) malloc(num_vars * sizeof(double));
                if (distancias[i] == NULL) {
                    perror("Erro ao alocar linha da matriz de distâncias");
                    exit(EXIT_FAILURE);
                }
            }
        } else if (isdigit(buffer[0])) {
            int id;
            double x, y;
            sscanf(buffer, "%d %lf %lf", &id, &x, &y);
            cidades[id - 1].x = x;
            cidades[id - 1].y = y;
        }
    }
    fclose(file);

    // Preenche matriz de distâncias depois de ler tudo
    for (int i = 0; i < num_vars; i++) {
        for (int j = i; j < num_vars; j++) {
            if (i == j) {
                distancias[i][j] = 0.0;
            } else {
                double dx = cidades[i].x - cidades[j].x;
                double dy = cidades[i].y - cidades[j].y;
                double d = round(sqrt(dx * dx + dy * dy));
                distancias[i][j] = d;
                distancias[j][i] = d;
            }
        }
    }
}


double evaluate(int *vetor) {
	double soma = 0.0;
	
	int i;
	for (i = 0; i < num_vars - 1; i++) {
        soma += distancias[vetor[i]][vetor[i + 1]];
    }
    soma += distancias[vetor[num_vars - 1]][vetor[0]];
    return soma;
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

void copiarVetorInt(int *destino, int *origem, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        destino[i] = origem[i];
    }
}

//estratégia light -> só bit flip -> na prática não funcionou mt bem
void gerarVizinho0(int *vizinho, const int *solucao) {
    
    for (int i = 0; i < num_vars; i++) {
        vizinho[i] = solucao[i];
    }
    
    int a = rand() % num_vars;
    int b = rand() % num_vars;
    while (a == b) b = rand() % num_vars;
    
    int temp = vizinho[a];
    vizinho[a] = vizinho[b];
    vizinho[b] = temp;
}

//estratégia suave -> poucos vizinhos locais
void gerarVizinho1(int *vizinho, const int *solucao) {
    for (int i = 0; i < num_vars; i++) {
        vizinho[i] = solucao[i];
    }

    int metodo = rand() % 2;  // Escolhe o tipo de vizinho

    if (metodo == 0) {
        // Swap entre duas cidades
        int i = rand() % num_vars;
        int j = rand() % num_vars;
        while (i == j) j = rand() % num_vars;

        int temp = vizinho[i];
        vizinho[i] = vizinho[j];
        vizinho[j] = temp;
    } else {
        // Inversão de um pequeno trecho
        int i = rand() % num_vars;
        int j = rand() % num_vars;
        if (i > j) { int temp = i; i = j; j = temp; }  // garante i < j

        while (i < j) {
            int temp = vizinho[i];
            vizinho[i] = vizinho[j];
            vizinho[j] = temp;
            i++;
            j--;
        }
    }
}

//estratégia agressiva -> não fica preso eternamente em máximo local
void gerarVizinho2(int *vizinho, const int *solucao) {
    for (int i = 0; i < num_vars; i++) {
        vizinho[i] = solucao[i];
    }

    int metodo = rand() % 3;  // Três métodos possíveis

    if (metodo == 0) {
        // Múltiplos swaps aleatórios
        int num_swaps = 1 + rand() % 5;  // Entre 1 e 5 trocas
        for (int s = 0; s < num_swaps; s++) {
            int i = rand() % num_vars;
            int j = rand() % num_vars;
            while (i == j) j = rand() % num_vars;

            int temp = vizinho[i];
            vizinho[i] = vizinho[j];
            vizinho[j] = temp;
        }
    } else if (metodo == 1) {
        // Inversão de um grande trecho
        int i = rand() % num_vars;
        int j = rand() % num_vars;
        if (i > j) { int temp = i; i = j; j = temp; }

        while (i < j) {
            int temp = vizinho[i];
            vizinho[i] = vizinho[j];
            vizinho[j] = temp;
            i++;
            j--;
        }
    } else {
        // Embaralhar uma subsequência aleatória
        int start = rand() % num_vars;
        int end = rand() % num_vars;
        if (start > end) { int temp = start; start = end; end = temp; }

        for (int i = start; i <= end; i++) {
            int j = start + rand() % (end - start + 1);
            int temp = vizinho[i];
            vizinho[i] = vizinho[j];
            vizinho[j] = temp;
        }
    }
}

void inicializarSolucao(int *solucao) {
    for (int i = 0; i < num_vars; i++) {
        solucao[i] = i;
    }
    for (int i = num_vars - 1; i > 0; i--) {
        int j = rand() % (i + 1);  // Sorteia entre 0 e i inclusive
        int temp = solucao[i];
        solucao[i] = solucao[j];
        solucao[j] = temp;
    }
}

int main () {
	setlocale(LC_ALL, "Portuguese");
	setlocale(LC_NUMERIC, "C");
	srand(time(NULL));
	
	//"TSP_100.txt"
	const char *nomearquivo = "TSP_100.txt";
	read_file(nomearquivo);
	
	FILE *saida = fopen("saida_boxplot_2.txt", "a");
		if (saida == NULL) {
			perror("Erro ao criar o arquivo de saída");
			exit(1);
		}
	int c = 1;
	while(c < (BOXPLOT_NUM + 1)){
		
		//printf("%d\n", num_vars);
		double T=T0;
		
		int *solution = (int *)malloc(num_vars * sizeof(int));
	    int *vizinho = (int *)malloc(num_vars * sizeof(int));
	    
	    inicializarSolucao(solution);
	    
	    double custoAtual = evaluate(solution);
	    double melhor_global = custoAtual;
		
		int i = 1; //iterações decaimento temperatura
		
		double currentValue;//distancia atual
		
		while (i < N) {
			//printf("\n%d", i);
			currentValue = evaluate(solution);
			////printf("%d", currentValue);
			int iterations = 0;
			while (iterations < SA_MAX) {
				//printf("%d", iterations);
				iterations++;
				gerarVizinho2(vizinho, solution);//gerar vizinho
				//printVetorBool(vizinho, num_vars);  //teste se a geração está funcionando
				int valueVizinho = evaluate(vizinho);
				
				int delta = valueVizinho - currentValue;//calcular delta entre performance atual e performance anterior
				
				if (delta < 0) {// if delta < 0 then Tcurrent = newT
					copiarVetorInt(solution, vizinho, num_vars);
					currentValue = valueVizinho;
					if (valueVizinho < melhor_global) {
						melhor_global = valueVizinho;//if f(newT) < f(Tcurrent) then melhor global = newT
						//if (melhor_global == 0) {
						//	break;
						//}
						//break;
					}
				} else {// else probabilidade e^alguma coisa (aceitar solução pior)
					double pPior = exp(-delta/(K * T));
					double r = (double)rand() / RAND_MAX;
					if (r < pPior) {
						copiarVetorInt(solution, vizinho, num_vars);
						currentValue = valueVizinho;
					}
				}
				
				//fprintf(saida, "%d,%.6f,%d,%d\n", i, T, currentValue, melhor_global); // Salva os dados
			}
			////printf("%d", currentValue);
			//fprintf(saida, "%d,%.6f,%.6f,%.6f\n", i, T, currentValue, melhor_global);
			//if (melhor_global == 0) {
				//break;
			//}
			
			//T = pow(1.0 - ((double)i / (double)N), 1); //t = fator de resfriamento. Admissível, por exemplo entre 1 e 5.
			//T = T * 0.999; //-> diminui rápido d+
			T = coolingSchedule4(i, T); // nova temperatura
			//1 legal, 2 pior que 1
			//3 e 5 estão funcionando legal
			// 7 também
			//9 +- 
			i++;
			if (i % 100 == 0) {
				float k = (100.0 * i) / N;
			    printf("%.2f%% Completos\n", k);
			}
			iterations = 0;
			
		}
		fprintf(saida, "%.2f\n", currentValue);
		free(vizinho);
		
		free(solution);
		
		c++;
	}
	
	fclose(saida);
	
	//print melhor global;
	
	//printf("\n%.2f\n", currentValue);
	
	//system("python --version");
	//system("python Simulated_Annealing-SAT.py");
	
	for (int i = 0; i < num_vars; i++) {
    	free(distancias[i]);
	}
	free(distancias);
	
	// Libera vetor de cidades
	free(cidades);
	
	free(arquivoLido);
	return 0;
}



