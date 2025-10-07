#include <string.h>
#include "ga_framework.h"
#include <stdbool.h>

// ==================================================================================
// IMPLEMENTAÇÃO DO PROBLEMA ESPECÍFICO (3-SAT)
// ==================================================================================

typedef struct {
    int literais[3];
} InstanciaSAT;

InstanciaSAT *arquivoLido = NULL; // Armazena todas as cláusulas lidas
int num_vars, num_clauses;     // Número de variáveis e cláusulas do problema

void read_cnf_file(const char *filename) {
    int index = 0;
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo da instancia SAT");
        exit(EXIT_FAILURE);
    }

    char line_buffer[256];
    while (fgets(line_buffer, sizeof(line_buffer), file)) {
        if (line_buffer[0] == 'c') {
            continue;
        } else if (line_buffer[0] == 'p') {
            char format[10];
            sscanf(line_buffer, "p %s %d %d", format, &num_vars, &num_clauses);
            
            arquivoLido = malloc(num_clauses * sizeof(InstanciaSAT));
            if (arquivoLido == NULL) {
                fprintf(stderr, "Erro ao alocar memória para as cláusulas.\n");
                exit(1);
            }
        } else if (line_buffer[0] == '%') {
            break;
        } else if (arquivoLido != NULL && index < num_clauses) {
            int lit1, lit2, lit3, end;
            if (sscanf(line_buffer, "%d %d %d %d", &lit1, &lit2, &lit3, &end) == 4 && end == 0) {
                arquivoLido[index].literais[0] = lit1;
                arquivoLido[index].literais[1] = lit2;
                arquivoLido[index].literais[2] = lit3;
                index++;
            }
        }
    }
    printf("Instancia SAT lida: %d variaveis, %d clausulas.\n", num_vars, num_clauses);
    fclose(file);
}

double calculate_fitness(const Individual* ind, const GA_Params* params) {
    int satisfeitas = 0;
    
    for (int i = 0; i < num_clauses; i++) {
        bool clausula_satisfeita = false;
        for (int j = 0; j < 3; j++) {
            int literal = arquivoLido[i].literais[j];
            bool valor_variavel;

            if (literal > 0) {
                valor_variavel = (ind->chromosome.bin_chrom[literal - 1] == 1);
            } else {
                valor_variavel = (ind->chromosome.bin_chrom[-literal - 1] == 0);
            }

            if (valor_variavel) {
                clausula_satisfeita = true;
                break;
            }
        }
        if (clausula_satisfeita) {
            satisfeitas++;
        }
    }
    
    return (double)satisfeitas;
}

void log_sat_details(FILE* file, int run_number, int generation, double best_fitness, 
                     double avg_fitness, const Individual* best_individual, const char* timestamp) 
{
    fprintf(file, "%s,%d,%d,%f,%f\n", 
            timestamp, run_number, generation, best_fitness, avg_fitness);
}

// ==================================================================================
// FUNÇÃO PRINCIPAL
// ==================================================================================
int main(int argc, char *argv[]) {
    init_rand();

    // Lê o problema SAT uma única vez, já que será o mesmo para todos os configs
    const char* sat_filename = "uf100-01.cnf.txt";
    printf("Lendo instancia do problema 3-SAT: '%s'...\n", sat_filename);
    read_cnf_file(sat_filename);

    int file_counter = 1;

    // --- INÍCIO DO LAÇO PRINCIPAL DE EXPERIMENTOS ---
    while (1) {
        char config_filename[128];
        sprintf(config_filename, "config%d.ini", file_counter);

        // Verifica se o arquivo de configuração da vez existe
        FILE* test_file = fopen(config_filename, "r");
        if (test_file == NULL) {
            if (file_counter == 1) {
                printf("Nenhum arquivo 'config1.ini' encontrado. Encerrando.\n");
            } else {
                printf("\n>>> Nao foram encontrados mais arquivos de configuracao. Processamento em lote concluido.\n");
            }
            break; // Sai do laço while
        }
        fclose(test_file);

        printf("\n===================================================================\n");
        printf(">>> INICIANDO EXPERIMENTO COM ARQUIVO: %s\n", config_filename);
        printf("===================================================================\n");

        // ---- Início da lógica de um experimento ----
        GA_Params params;
        if (!load_params(config_filename, &params)) {
            fprintf(stderr, "\nERRO CRITICO AO LER '%s'. Pulando para o proximo.\n", config_filename);
            file_counter++;
            continue; // Pula para a próxima iteração
        }
        
        params.dim = num_vars;
        print_params(&params);

        char base_name[128];
        strcpy(base_name, config_filename);
        char *last_dot = strrchr(base_name, '.');
        if (last_dot != NULL) {
            *last_dot = '\0';
        }

        char summary_filename[256];
        char details_filename[256];
        sprintf(summary_filename, "resultados_%s.csv", base_name);
        sprintf(details_filename, "detalhes_%s.csv", base_name);

        printf("Arquivo de saida de resultados: '%s'\n", summary_filename);
        printf("Arquivo de saida de detalhes: '%s'\n", details_filename);

        FILE *summary_csv = fopen(summary_filename, "w");
        FILE *details_csv = fopen(details_filename, "w");

        if (summary_csv == NULL || details_csv == NULL) {
            perror("ERRO: Nao foi possivel criar os arquivos CSV");
            file_counter++;
            continue;
        }

        fprintf(summary_csv, "Timestamp,Run,ClausesMet,TotalClauses,IsOptimal,PopSize,Generations,PC,PM\n");
        fprintf(details_csv, "Timestamp,Run,Generation,BestFitness,AvgFitness\n");
        
        time_t t = time(NULL);
        struct tm *tm_info = localtime(&t);
        char timestamp_str[64];
        strftime(timestamp_str, sizeof(timestamp_str), "%Y-%m-%d %H:%M:%S", tm_info);
        
        double* results = (double*)malloc(params.runs * sizeof(double));
        double total_fitness_sum = 0.0;
        double best_overall_fitness = 0.0;

        Individual best_ind_of_run;
        best_ind_of_run.chromosome.bin_chrom = (char*)malloc(params.dim * sizeof(char));

        printf("\n--- INICIANDO EXECUCOES DO AG PARA %s ---\n", config_filename);
        for (int i = 0; i < params.runs; i++) {
            run_genetic_algorithm(&params, &best_ind_of_run, details_csv, i + 1, timestamp_str, log_sat_details);
            
            results[i] = best_ind_of_run.fitness;
            total_fitness_sum += best_ind_of_run.fitness;

            if (i == 0 || results[i] > best_overall_fitness) {
                best_overall_fitness = results[i];
            }
            if ((i + 1) % 1 == 0 || i == params.runs - 1) { // Imprime o progresso
                 printf("... Run %d de %d concluida | Melhor Fitness: %.0f de %d\n", i + 1, params.runs, best_ind_of_run.fitness, num_clauses);
            }

            int is_optimal = (best_ind_of_run.fitness == num_clauses) ? 1 : 0;
            fprintf(summary_csv, "%s,%d,%.0f,%d,%d,%d,%d,%.2f,%.2f\n",
                    timestamp_str, i + 1, best_ind_of_run.fitness, num_clauses, is_optimal, 
                    params.pop_size, params.generations, params.pc, params.pm);
        }
        
        fclose(summary_csv);
        fclose(details_csv);
        printf("\nResultados para '%s' salvos com sucesso.\n", config_filename);

        double average_best_fitness = total_fitness_sum / params.runs;

        printf("\n--- RESULTADOS FINAIS PARA %s ---\n", config_filename);
        printf("Total de execucoes: %d\n", params.runs);
        printf("Melhor resultado global (clausulas): %.0f / %d\n", best_overall_fitness, num_clauses);
        printf("Media dos melhores resultados: %.2f / %d\n", average_best_fitness, num_clauses);
        printf("---------------------------------------------------\n");

        free(best_ind_of_run.chromosome.bin_chrom);
        free(results);
        // ---- Fim da lógica de um experimento ----

        file_counter++; // Prepara para procurar o próximo arquivo
    }
    // --- FIM DO LAÇO PRINCIPAL DE EXPERIMENTOS ---
    
    free(arquivoLido); // Libera a memória do problema SAT no final de tudo

    printf("\nExecucao finalizada. Pressione Enter para sair...");
    getchar();
    return 0;
}
