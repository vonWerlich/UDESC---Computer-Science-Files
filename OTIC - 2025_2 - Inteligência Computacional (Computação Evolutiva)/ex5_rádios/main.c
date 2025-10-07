#include "ga_framework.h"
#include <string.h>

// ==================================================================================
// IMPLEMENTAÇÃO DO PROBLEMA ESPECÍFICO (FÁBRICA DE RÁDIOS)
// ==================================================================================

/**
 * Calcula a aptidão (fitness) de um indivíduo.
 * Esta é a função que define o problema a ser resolvido.
 */
double calculate_fitness(const Individual* ind, const GA_Params* params) {
    // Decodifica o cromossomo para as variáveis do problema
    int d_ST = bin_to_int(ind->chromosome.bin_chrom, 0, 5);
    int d_LX = bin_to_int(ind->chromosome.bin_chrom, 5, 5);
    
    const double max_int_val = 31.0;

    // Escala as variáveis para o domínio correto
    const double xmin_ST = 0.0, xmax_ST = 24.0;
    double ST = floor(xmin_ST + ((xmax_ST - xmin_ST) / max_int_val) * (double)d_ST);

    const double xmin_LX = 0.0, xmax_LX = 16.0;
    double LX = floor(xmin_LX + ((xmax_LX - xmin_LX) / max_int_val) * (double)d_LX);

    // Calcula a função objetivo (Lucro)
    double fo = 30.0 * ST + 40.0 * LX;

    // Calcula a violação da restrição
    double violacao = (ST + (2.0 * LX)) - 40.0;
    if (violacao < 0) {
        violacao = 0;
    }

    // Normaliza e aplica a penalidade
    double fo_n = fo / 1360.0;
    double h_n = violacao / 16.0;
    double fitness = fo_n - h_n;
    
    return (fitness < 0) ? 0 : fitness;
}


// ==================================================================================
// FUNÇÃO PRINCIPAL
// ==================================================================================
int main(int argc, char *argv[]) {
    init_rand(); // Semente aleatória no início de tudo

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
            break; // Sai do laço while se não encontrar o próximo arquivo
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
            continue; // Pula para a próxima iteração do laço
        }
        
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
            perror("ERRO: Nao foi possivel criar os arquivos CSV de resultados");
            file_counter++;
            continue;
        }

        fprintf(summary_csv, "Timestamp,Run,BestFitness,Final_Profit,Is_Feasible,PopSize,Generations,PC,PM\n");
        fprintf(details_csv, "Timestamp,Run,Generation,BestFitness,AvgFitness,Best_ST,Best_LX,Best_Profit\n");
        
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
            run_genetic_algorithm(&params, &best_ind_of_run, details_csv, i + 1, timestamp_str);
            
            results[i] = best_ind_of_run.fitness;
            total_fitness_sum += best_ind_of_run.fitness;

            if (i == 0 || results[i] > best_overall_fitness) {
                best_overall_fitness = results[i];
            }

            int d_ST = bin_to_int(best_ind_of_run.chromosome.bin_chrom, 0, 5);
            int d_LX = bin_to_int(best_ind_of_run.chromosome.bin_chrom, 5, 5);
            const double max_int_val = 31.0;
            const double xmin_ST = 0.0, xmax_ST = 24.0;
            double ST = floor(xmin_ST + ((xmax_ST - xmin_ST) / max_int_val) * (double)d_ST);
            const double xmin_LX = 0.0, xmax_LX = 16.0;
            double LX = floor(xmin_LX + ((xmax_LX - xmin_LX) / max_int_val) * (double)d_LX);
            double final_profit = 30.0 * ST + 40.0 * LX;
            int is_feasible = ((ST + (2.0 * LX)) - 40.0 <= 1e-9) ? 1 : 0;

            fprintf(summary_csv, "%s,%d,%f,%.2f,%d,%d,%d,%.2f,%d\n",
                    timestamp_str, i + 1, best_ind_of_run.fitness, final_profit, is_feasible, 
                    params.pop_size, params.generations, params.pc, (int)params.pm);
        }
        
        fclose(summary_csv);
        fclose(details_csv);
        printf("\nResultados para '%s' salvos com sucesso.\n", config_filename);

        double average_best_fitness = total_fitness_sum / params.runs;

        printf("\n--- RESULTADOS FINAIS PARA %s ---\n", config_filename);
        printf("Total de execucoes: %d\n", params.runs);
        printf("Melhor fitness global: %f\n", best_overall_fitness);
        printf("Media do melhor fitness: %f\n", average_best_fitness);
        printf("---------------------------------------------------\n");

        free(best_ind_of_run.chromosome.bin_chrom);
        free(results);
        // ---- Fim da lógica de um experimento ----

        file_counter++; // Prepara para procurar o próximo arquivo (config2.ini, etc.)
    }
    // --- FIM DO LAÇO PRINCIPAL DE EXPERIMENTOS ---

    printf("\nExecucao finalizada. Pressione Enter para sair...");
    getchar();
    return 0;
}
