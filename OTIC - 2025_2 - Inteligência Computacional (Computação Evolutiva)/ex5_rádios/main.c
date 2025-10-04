#include "ga_framework.h"

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
    const char* config_filename = "config.ini";
    printf("Procurando pelo arquivo de configuracao: '%s'...\n", config_filename);
    
    GA_Params params;
    if (!load_params(config_filename, &params)) {
        fprintf(stderr, "\nERRO CRITICO: Nao foi possivel encontrar ou ler o arquivo '%s'.\n", config_filename);
        fprintf(stderr, "Certifique-se de que o arquivo 'config.ini' esta na mesma pasta que o executavel.\n");
        printf("\nPressione Enter para sair...");
        getchar();
        return 1;
    }
    
    print_params(&params);
    init_rand();

    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char timestamp_base[64];
    strftime(timestamp_base, sizeof(timestamp_base), "%Y-%m-%d_%H-%M-%S", tm_info);


    FILE *summary_csv = fopen("resultados_gerais.csv", "w");
    FILE *details_csv = fopen("detalhes_geracoes.csv", "w");

    if (summary_csv == NULL || details_csv == NULL) {
        perror("ERRO: Nao foi possivel criar os arquivos CSV de resultados");
        printf("\nPressione Enter para sair...");
        getchar();
        return 1;
    }

    fprintf(summary_csv, "Timestamp,Run,BestFitness,Final_Profit,Is_Feasible,PopSize,Generations,PC,PM\n");
    fprintf(details_csv, "Timestamp,Run,Generation,BestFitness,AvgFitness,Best_ST,Best_LX,Best_Profit\n");
    
    char timestamp_str[64];
    strftime(timestamp_str, sizeof(timestamp_str), "%Y-%m-%d %H:%M:%S", tm_info);
    
    double* results = (double*)malloc(params.runs * sizeof(double));
    double total_fitness_sum = 0.0;
    double best_overall_fitness = 0.0;

    Individual best_ind_of_run;
    best_ind_of_run.chromosome.bin_chrom = (char*)malloc(params.dim * sizeof(char));


    printf("\n=== INICIANDO EXECUCOES DO AG ===\n");
    for (int i = 0; i < params.runs; i++) {
        printf("\n--- Execucao (Run) %d de %d ---\n", i + 1, params.runs);
        
        // ALTERAÇÃO: A função agora preenche a estrutura 'best_ind_of_run'.
        run_genetic_algorithm(&params, &best_ind_of_run, details_csv, i + 1, timestamp_str);
        
        results[i] = best_ind_of_run.fitness;
        total_fitness_sum += best_ind_of_run.fitness;

        if (i == 0 || results[i] > best_overall_fitness) {
            best_overall_fitness = results[i];
        }
        printf("--- Fim da Execucao %d | Melhor Fitness: %f ---\n", i + 1, results[i]);

        // --- INÍCIO DA LÓGICA ADICIONADA ---
        // Decodifica o cromossomo do melhor indivíduo da execução
        int d_ST = bin_to_int(best_ind_of_run.chromosome.bin_chrom, 0, 5);
        int d_LX = bin_to_int(best_ind_of_run.chromosome.bin_chrom, 5, 5);
        const double max_int_val = 31.0;

        const double xmin_ST = 0.0, xmax_ST = 24.0;
        double ST = floor(xmin_ST + ((xmax_ST - xmin_ST) / max_int_val) * (double)d_ST);

        const double xmin_LX = 0.0, xmax_LX = 16.0;
        double LX = floor(xmin_LX + ((xmax_LX - xmin_LX) / max_int_val) * (double)d_LX);

        // Calcula a função objetivo (Lucro) final
        double final_profit = 30.0 * ST + 40.0 * LX;

        // Verifica se a solução é viável (não quebra a restrição)
        int is_feasible = ((ST + (2.0 * LX)) - 40.0 <= 1e-9) ? 1 : 0; // Usar epsilon para comparação de float

        // ALTERAÇÃO: Escreve os novos dados no CSV
        fprintf(summary_csv, "%s,%d,%f,%.2f,%d,%d,%d,%.2f,%.2f\n",
                timestamp_str, i + 1, best_ind_of_run.fitness, final_profit, is_feasible, 
                params.pop_size, params.generations, params.pc, params.pm);
        // --- FIM DA LÓGICA ADICIONADA ---
    }
    
    fclose(summary_csv);
    fclose(details_csv);
    printf("\nResultados salvos com sucesso ");

    double average_best_fitness = total_fitness_sum / params.runs;

    printf("\n\n==============================================\n");
    printf("            RESULTADOS FINAIS\n");
    printf("==============================================\n");
    printf("Total de execucoes: %d\n", params.runs);
    printf("Melhor fitness global: %f\n", best_overall_fitness);
    printf("Media do melhor fitness: %f\n", average_best_fitness);
    printf("==============================================\n");

    // ALTERAÇÃO: Libera a memória alocada para o cromossomo do indivíduo.
    free(best_ind_of_run.chromosome.bin_chrom);
    free(results);

    printf("\nExecucao finalizada. Pressione Enter para sair...");
    getchar();
    return 0;
}
