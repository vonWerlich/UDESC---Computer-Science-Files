#ifndef GA_FRAMEWORK_H
#define GA_FRAMEWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>
#include <limits.h>
#include <math.h>

// ==================================================================================
// 1. DEFINIÇÃO DE ESTRUTURAS E ENUMS GLOBAIS
// ==================================================================================
typedef enum { BIN, INT_PERM, REAL, INT } ReprType;
typedef enum { ROULETTE, TOURNAMENT } SelectionType;
typedef enum { ONE_POINT, TWO_POINT, UNIFORM } BinCrossoverType;
typedef enum { PMX, CX } IntPermCrossoverType;

typedef struct {
    ReprType cod;
    int runs;
    int generations;
    int pop_size;
    int dim;
    int elitism;
    double pc;
    double pm;
    SelectionType selection_method;
    int tournament_k;
    double tournament_kp;
    BinCrossoverType bin_crossover;
    IntPermCrossoverType int_perm_crossover;
} GA_Params;

typedef struct {
    union {
        char* bin_chrom;
        int* int_perm_chrom;
    } chromosome;
    double fitness;
} Individual;

typedef struct {
    Individual* individuals;
    int pop_size;
} Population;

// ==================================================================================
// 2. DECLARAÇÃO DE PROTÓTIPO DA FUNÇÃO DE FITNESS
// ==================================================================================
double calculate_fitness(const Individual* ind, const GA_Params* params);


// ==================================================================================
// 3. DEFINIÇÃO DAS FUNÇÕES DO FRAMEWORK (com 'static')
// ==================================================================================

// --- Funções Utilitárias ---
static void init_rand() { srand((unsigned int)time(NULL)); }
static int rand_int(int min, int max) { return min + rand() % (max - min + 1); }
static double rand_double() { return (double)rand() / (double)RAND_MAX; }

static void shuffle_array(int* array, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand_int(0, i);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

static int bin_to_int(const char* chromosome, int start, int length) {
    int value = 0;
    int power = 1;
    for (int i = start + length - 1; i >= start; i--) {
        if (chromosome[i] == 1) {
            value += power;
        }
        power *= 2;
    }
    return value;
}

// --- Funções de Configuração ---
static int load_params(const char* filename, GA_Params* params) {
    FILE* file = fopen(filename, "r");
    if (!file) return 0;
    
    char line[256], key[256], value[256];

    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '#' || line[0] == '\n') continue;
        if (sscanf(line, "%s = %s", key, value) == 2) {
            if (strcmp(key, "COD") == 0) {
                if(strcmp(value, "BIN")==0) params->cod = BIN;
                if(strcmp(value, "INT-PERM")==0) params->cod = INT_PERM;
            }
            else if (strcmp(key, "RUN") == 0) params->runs = atoi(value);
            else if (strcmp(key, "GEN") == 0) params->generations = atoi(value);
            else if (strcmp(key, "POP") == 0) params->pop_size = atoi(value);
            else if (strcmp(key, "DIM") == 0) params->dim = atoi(value);
            else if (strcmp(key, "ELITISM") == 0) params->elitism = atoi(value);
            else if (strcmp(key, "PC") == 0) params->pc = atof(value);
            else if (strcmp(key, "PM") == 0) params->pm = atof(value);
            else if (strcmp(key, "SELECTION_METHOD") == 0) {
                if(strcmp(value, "ROULETTE")==0) params->selection_method = ROULETTE;
                if(strcmp(value, "TOURNAMENT")==0) params->selection_method = TOURNAMENT;
            }
            else if (strcmp(key, "TOURNAMENT_K") == 0) params->tournament_k = atoi(value);
            else if (strcmp(key, "TOURNAMENT_KP") == 0) params->tournament_kp = atof(value);
            else if (strcmp(key, "BIN_CROSSOVER") == 0) {
                 if(strcmp(value, "ONE_POINT")==0) params->bin_crossover = ONE_POINT;
                 if(strcmp(value, "TWO_POINT")==0) params->bin_crossover = TWO_POINT;
                 if(strcmp(value, "UNIFORM")==0) params->bin_crossover = UNIFORM;
            }
            else if (strcmp(key, "INT_PERM_CROSSOVER") == 0) {
                if(strcmp(value, "PMX")==0) params->int_perm_crossover = PMX;
                if(strcmp(value, "CX")==0) params->int_perm_crossover = CX;
            }
        }
    }
    fclose(file);
    return 1;
}

static void print_params(const GA_Params* params) {
    printf("--- Parametros do AG ---\n");
    printf("Execucoes (RUN): %d | Geracoes (GEN): %d | Populacao (POP): %d\n", params->runs, params->generations, params->pop_size);
    printf("Dimensao (DIM): %d | Elitismo: %s\n", params->dim, params->elitism ? "Sim" : "Nao");
    printf("PC: %.2f | PM: %.2f\n", params->pc, params->pm);
    printf("------------------------\n");
}


// --- Funções de População ---
static Population* create_population(const GA_Params* params) {
    Population* pop = (Population*)malloc(sizeof(Population));
    pop->pop_size = params->pop_size;
    pop->individuals = (Individual*)malloc(params->pop_size * sizeof(Individual));
    for (int i = 0; i < params->pop_size; i++) {
        if (params->cod == BIN) {
            pop->individuals[i].chromosome.bin_chrom = (char*)malloc(params->dim * sizeof(char));
        } else if (params->cod == INT_PERM) {
            pop->individuals[i].chromosome.int_perm_chrom = (int*)malloc(params->dim * sizeof(int));
        }
    }
    return pop;
}

static void free_population(Population* pop, const GA_Params* params) {
    if (!pop) return;
    for (int i = 0; i < pop->pop_size; i++) {
        if (params->cod == BIN) {
            free(pop->individuals[i].chromosome.bin_chrom);
        } else if (params->cod == INT_PERM) {
            free(pop->individuals[i].chromosome.int_perm_chrom);
        }
    }
    free(pop->individuals);
    free(pop);
}

static void initialize_population(Population* pop, const GA_Params* params) {
    for (int i = 0; i < pop->pop_size; i++) {
        if (params->cod == BIN) {
            for (int j = 0; j < params->dim; j++) {
                pop->individuals[i].chromosome.bin_chrom[j] = rand_int(0, 1);
            }
        } else if (params->cod == INT_PERM) {
            int* p = pop->individuals[i].chromosome.int_perm_chrom;
            for (int j = 0; j < params->dim; j++) p[j] = j;
            shuffle_array(p, params->dim);
        }
    }
}

static Individual* find_best_individual(const Population* pop) {
    Individual* best = &pop->individuals[0];
    for (int i = 1; i < pop->pop_size; i++) {
        if (pop->individuals[i].fitness > best->fitness) {
            best = &pop->individuals[i];
        }
    }
    return best;
}

static void copy_individual(const Individual* src, Individual* dest, int dim, ReprType cod) {
    if(dest->chromosome.bin_chrom == NULL) {
        if (cod == BIN) {
            dest->chromosome.bin_chrom = (char*)malloc(dim * sizeof(char));
        } else if (cod == INT_PERM) {
             dest->chromosome.int_perm_chrom = (int*)malloc(dim * sizeof(int));
        }
    }
    if (cod == BIN) {
        memcpy(dest->chromosome.bin_chrom, src->chromosome.bin_chrom, dim * sizeof(char));
    } else if (cod == INT_PERM) {
        memcpy(dest->chromosome.int_perm_chrom, src->chromosome.int_perm_chrom, dim * sizeof(int));
    }
    dest->fitness = src->fitness;
}

// --- Funções de Avaliação e Seleção ---
static void evaluate_population(Population* pop, const GA_Params* params) {
    #pragma omp parallel for
    for (int i = 0; i < pop->pop_size; i++) {
        pop->individuals[i].fitness = calculate_fitness(&pop->individuals[i], params);
    }
}

static int selection_tournament(const Population* pop, const GA_Params* params) {
    int best_idx = -1;
    double best_fitness = -1.0;
    int competitors[params->tournament_k];
    for (int i = 0; i < params->tournament_k; i++) {
        competitors[i] = rand_int(0, pop->pop_size - 1);
        if (pop->individuals[competitors[i]].fitness > best_fitness) {
            best_fitness = pop->individuals[competitors[i]].fitness;
            best_idx = competitors[i];
        }
    }
    if (rand_double() < params->tournament_kp) {
        return best_idx;
    } else {
        int random_competitor_idx = rand_int(0, params->tournament_k - 1);
        return competitors[random_competitor_idx];
    }
}

static int selection_roulette(const Population* pop) {
    double total_fitness = 0;
    for (int i = 0; i < pop->pop_size; i++) {
        if(pop->individuals[i].fitness > 0)
            total_fitness += pop->individuals[i].fitness;
    }
    if (total_fitness == 0) return rand_int(0, pop->pop_size -1);
    double slice = rand_double() * total_fitness;
    double current_sum = 0;
    for (int i = 0; i < pop->pop_size; i++) {
        if(pop->individuals[i].fitness > 0)
            current_sum += pop->individuals[i].fitness;
        if (current_sum >= slice) {
            return i;
        }
    }
    return pop->pop_size - 1;
}

// --- Operadores Genéticos ---
static void crossover_bin(Individual* p1, Individual* p2, Individual* o1, Individual* o2, const GA_Params* params) {
    if(!o2) {
        copy_individual(p1, o1, params->dim, params->cod);
        return;
    }
    switch (params->bin_crossover) {
        case ONE_POINT: {
            int point = rand_int(1, params->dim - 2);
            for (int i = 0; i < params->dim; i++) {
                o1->chromosome.bin_chrom[i] = (i < point) ? p1->chromosome.bin_chrom[i] : p2->chromosome.bin_chrom[i];
                o2->chromosome.bin_chrom[i] = (i < point) ? p2->chromosome.bin_chrom[i] : p1->chromosome.bin_chrom[i];
            }
            break;
        }
        case TWO_POINT: {
            int p1_idx = rand_int(1, params->dim - 2);
            int p2_idx = rand_int(1, params->dim - 2);
            if(p1_idx > p2_idx) { int temp = p1_idx; p1_idx = p2_idx; p2_idx = temp; }
             for (int i = 0; i < params->dim; i++) {
                if (i < p1_idx || i >= p2_idx) {
                    o1->chromosome.bin_chrom[i] = p1->chromosome.bin_chrom[i];
                    o2->chromosome.bin_chrom[i] = p2->chromosome.bin_chrom[i];
                } else {
                    o1->chromosome.bin_chrom[i] = p2->chromosome.bin_chrom[i];
                    o2->chromosome.bin_chrom[i] = p1->chromosome.bin_chrom[i];
                }
            }
            break;
        }
        case UNIFORM: {
            for (int i = 0; i < params->dim; i++) {
                if (rand_double() < 0.5) {
                    o1->chromosome.bin_chrom[i] = p1->chromosome.bin_chrom[i];
                    o2->chromosome.bin_chrom[i] = p2->chromosome.bin_chrom[i];
                } else {
                    o1->chromosome.bin_chrom[i] = p2->chromosome.bin_chrom[i];
                    o2->chromosome.bin_chrom[i] = p1->chromosome.bin_chrom[i];
                }
            }
            break;
        }
    }
}
static void mutation_bin(Individual* ind, const GA_Params* params) {
    for (int i = 0; i < params->dim; i++) {
        if (rand_double() < params->pm) {
            ind->chromosome.bin_chrom[i] = 1 - ind->chromosome.bin_chrom[i];
        }
    }
}

// --- Lógica Principal do AG (O "Motor") ---
// ALTERAÇÃO: A função agora recebe um ponteiro para um Individual (best_ind_out)
// em vez de um ponteiro para double, para retornar o indivíduo completo.
static void run_genetic_algorithm(const GA_Params* params, Individual* best_ind_out, FILE* details_csv, int run_number, const char* timestamp_str) {
    Population* current_pop = create_population(params);
    Population* next_pop = create_population(params);
    initialize_population(current_pop, params);
    evaluate_population(current_pop, params);

    Individual* best_gen_ind = find_best_individual(current_pop);
    Individual best_overall_ind;
    best_overall_ind.chromosome.bin_chrom = NULL;
    copy_individual(best_gen_ind, &best_overall_ind, params->dim, params->cod);
    
    printf("Geracao 0 | Melhor Fitness: %f\n", best_overall_ind.fitness);

    {
        double gen_total_fitness = 0.0;
        for(int i = 0; i < params->pop_size; i++) {
            gen_total_fitness += current_pop->individuals[i].fitness;
        }
        double avg_fitness = gen_total_fitness / params->pop_size;
        int d_ST = bin_to_int(best_gen_ind->chromosome.bin_chrom, 0, 5);
        int d_LX = bin_to_int(best_gen_ind->chromosome.bin_chrom, 5, 5);
        const double max_int_val = 31.0;
        int best_ST = (int)floor(0.0 + ((24.0 - 0.0) / max_int_val) * (double)d_ST);
        int best_LX = (int)floor(0.0 + ((16.0 - 0.0) / max_int_val) * (double)d_LX);
        double best_profit = 30.0 * best_ST + 40.0 * best_LX;
        fprintf(details_csv, "%s,%d,0,%f,%f,%d,%d,%.2f\n", 
                timestamp_str, run_number, best_gen_ind->fitness, avg_fitness, best_ST, best_LX, best_profit);
    }

    for (int g = 1; g < params->generations; g++) {
        int next_pop_idx = 0;
        if (params->elitism) {
            Individual* best_current = find_best_individual(current_pop);
            copy_individual(best_current, &next_pop->individuals[0], params->dim, params->cod);
            next_pop_idx = 1;
        }
        while(next_pop_idx < params->pop_size) {
            int p1_idx, p2_idx;
            if (params->selection_method == TOURNAMENT) {
                p1_idx = selection_tournament(current_pop, params);
                do { p2_idx = selection_tournament(current_pop, params); } while (p1_idx == p2_idx);
            } else {
                p1_idx = selection_roulette(current_pop);
                do { p2_idx = selection_roulette(current_pop); } while (p1_idx == p2_idx);
            }
            Individual* parent1 = &current_pop->individuals[p1_idx];
            Individual* parent2 = &current_pop->individuals[p2_idx];
            Individual* offspring1 = &next_pop->individuals[next_pop_idx];
            Individual* offspring2 = (next_pop_idx + 1 < params->pop_size) ? &next_pop->individuals[next_pop_idx + 1] : NULL;
            if (rand_double() < params->pc) {
                if (params->cod == BIN) crossover_bin(parent1, parent2, offspring1, offspring2, params);
            } else {
                copy_individual(parent1, offspring1, params->dim, params->cod);
                if (offspring2) copy_individual(parent2, offspring2, params->dim, params->cod);
            }
            if (params->cod == BIN) {
                mutation_bin(offspring1, params);
                if(offspring2) mutation_bin(offspring2, params);
            }
            next_pop_idx += (offspring2) ? 2 : 1;
        }

        Population* temp = current_pop;
        current_pop = next_pop;
        next_pop = temp;

        evaluate_population(current_pop, params);
        
        best_gen_ind = find_best_individual(current_pop);
        if (best_gen_ind->fitness > best_overall_ind.fitness) {
            copy_individual(best_gen_ind, &best_overall_ind, params->dim, params->cod);
        }
        
        if (g % 10 == 0 || g == params->generations - 1) {
             printf("Geracao %d | Melhor Fitness: %f\n", g, best_overall_ind.fitness);
        }

        {
            double current_total_fitness = 0.0;
            for(int i = 0; i < params->pop_size; i++) {
                current_total_fitness += current_pop->individuals[i].fitness;
            }
            double avg_fitness = current_total_fitness / params->pop_size;
            int d_ST = bin_to_int(best_gen_ind->chromosome.bin_chrom, 0, 5);
            int d_LX = bin_to_int(best_gen_ind->chromosome.bin_chrom, 5, 5);
            const double max_int_val = 31.0;
            int best_ST = (int)floor(0.0 + ((24.0 - 0.0) / max_int_val) * (double)d_ST);
            int best_LX = (int)floor(0.0 + ((16.0 - 0.0) / max_int_val) * (double)d_LX);
            double best_profit = 30.0 * best_ST + 40.0 * best_LX;
            fprintf(details_csv, "%s,%d,%d,%f,%f,%d,%d,%.2f\n", 
                    timestamp_str, run_number, g, best_gen_ind->fitness, avg_fitness, best_ST, best_LX, best_profit);
        }
    }

    // ALTERAÇÃO: Copia o melhor indivíduo encontrado para a variável de saída.
    copy_individual(&best_overall_ind, best_ind_out, params->dim, params->cod);
    
    free(best_overall_ind.chromosome.bin_chrom);
    free_population(current_pop, params);
    free_population(next_pop, params);
}

#endif // GA_FRAMEWORK_H
