#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_E
#define M_E 2.71828182845904523536
#endif

#define NUM_PARTICLES 30
#define DIM 5
#define MAX_ITER 5000

// Enumerações
typedef enum { GRIEWANK = 1, ACKLEY = 2 } Problem;
typedef enum { STANDARD = 0, INERTIA = 1, CONSTRICTION = 2 } Variant;

// Estrutura da partícula
typedef struct {
    double position[DIM];
    double velocity[DIM];
    double best_position[DIM];
    double best_value;
} Particle;

// Aleatório entre min e max
double rand_double(double min, double max) {
    return min + ((double)rand() / RAND_MAX) * (max - min);
}

// Funções-objetivo
double f_griewank(const double x[]) {
    double sum = 0, prod = 1;
    for (int i = 0; i < DIM; i++) {
        sum += x[i] * x[i];
        prod *= cos(x[i] / sqrt(i + 1));
    }
    return sum / 4000.0 - prod + 1.0;
}

double f_ackley(const double x[]) {
    double sum1 = 0, sum2 = 0;
    for (int i = 0; i < DIM; i++) {
        sum1 += x[i] * x[i];
        sum2 += cos(2.0 * M_PI * x[i]);
    }
    return -20.0 * exp(-0.2 * sqrt(sum1 / DIM))
           - exp(sum2 / DIM) + 20.0 + M_E;
}

double objective(const double x[], Problem prob) {
    return (prob == GRIEWANK) ? f_griewank(x) : f_ackley(x);
}

void initialize_swarm(Particle swarm[], double xmin, double xmax,
                      double vmin, double vmax, Problem prob) {
    for (int i = 0; i < NUM_PARTICLES; i++) {
        swarm[i].best_value = 1e20;
        for (int j = 0; j < DIM; j++) {
            swarm[i].position[j] = rand_double(xmin, xmax);
            swarm[i].velocity[j] = rand_double(vmin, vmax);
            swarm[i].best_position[j] = swarm[i].position[j];
        }
        swarm[i].best_value = objective(swarm[i].position, prob);
    }
}

void update_particle(Particle *p, const double gbest_pos[], double *gbv,
                     double w, double c1, double c2,
                     double xmin, double xmax,
                     double vmin, double vmax,
                     double chi,
                     Problem prob,
                     Variant variant) {
    for (int j = 0; j < DIM; j++) {
        double r1 = rand_double(0,1);
        double r2 = rand_double(0,1);
        double cog = c1 * r1 * (p->best_position[j] - p->position[j]);
        double soc = c2 * r2 * (gbest_pos[j] - p->position[j]);
        double vel = p->velocity[j] + cog + soc; // padrão
        if (variant == INERTIA) vel = w * p->velocity[j] + cog + soc;
        else if (variant == CONSTRICTION) vel = chi * (p->velocity[j] + cog + soc);
        // limites
        if (vel > vmax) vel = vmax;
        if (vel < vmin) vel = vmin;
        p->velocity[j] = vel;
        p->position[j] += vel;
        if (p->position[j] > xmax) p->position[j] = xmax;
        if (p->position[j] < xmin) p->position[j] = xmin;
    }
    double val = objective(p->position, prob);
    if (val < p->best_value) {
        p->best_value = val;
        memcpy(p->best_position, p->position, sizeof p->position);
    }
    if (p->best_value < *gbv) {
        *gbv = p->best_value;
        memcpy((void*)gbest_pos, p->best_position, sizeof p->position);
    }
}

double run_pso(Problem prob, Variant variant) {
    Particle swarm[NUM_PARTICLES];
    double gbest_pos[DIM];
    double gbest_val = 1e20;

    double xmin = (prob==GRIEWANK?-600:-32);
    double xmax = (prob==GRIEWANK? 600: 32);
    double vmin = xmin, vmax = xmax;
    double w = 0.5; //peso de inércia
	double c1 = 2.05, c2 = 2.05;  //c1 -> pessoal // c2 -> social
    double phi = c1 + c2; // lembrar que se usar chi, c1+c2 >=4
    double chi = 2.0 / (fabs(2.0 - phi - sqrt(phi*phi - 4*phi)));

    initialize_swarm(swarm, xmin, xmax, vmin, vmax, prob);

    for (int t = 0; t < MAX_ITER; t++) {
        for (int i = 0; i < NUM_PARTICLES; i++) {
            update_particle(&swarm[i], gbest_pos, &gbest_val,
                            w, c1, c2, xmin, xmax,
                            vmin, vmax, chi,
                            prob, variant);
        }
        double best_current = 1e20;
		for (int i = 0; i < NUM_PARTICLES; i++) {
		    double val = objective(swarm[i].position, prob);
		    if (val < best_current)
		        best_current = val;
		}

    }
 
    
    
    return gbest_val;
}

int main() {
    
    srand(time(NULL));
    FILE *f = fopen("boxplot_1_semSTD.txt", "w");
    if (!f) {
        perror("Erro ao abrir o arquivo de saída");
        return 1;
    }
	
	Problem problema = GRIEWANK;
	Variant variante = INERTIA;
	int i;
	for (i=0; i<30; i++) {
		double result = run_pso(problema, variante);
		fprintf(f, "%.10f\n", result);
		printf("%.10f\n", result);
	}
	problema = ACKLEY;
	for (i=0; i<30; i++) {
		double result = run_pso(problema, variante);
		fprintf(f, "%.10f\n", result);
		printf("%.10f\n", result);
	}
	problema = GRIEWANK;
	variante = CONSTRICTION;
	for (i=0; i<30; i++) {
		double result = run_pso(problema, variante);
		fprintf(f, "%.10f\n", result);
		printf("%.10f\n", result);
	}
	problema = ACKLEY;
	for (i=0; i<30; i++) {
		double result = run_pso(problema, variante);
		fprintf(f, "%.10f\n", result);
		printf("%.10f\n", result);
	}
	
    
    return 0;
}
/*

só precisa trocar estas duas linhas no `main()` para escolher o problema e a variante:

Problem problema = ACKLEY;         // ACKLEY ou GRIEWANK
Variant variante = INERTIA;        // INERTIA ou STANDARD, CONSTRICTION

*/

