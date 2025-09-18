#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define M_PI 3.14159265358979323846

#define DIM 30
#define NUM_PARTICLES 30
#define MAX_ITER 1000

#define PROBLEM 2 // 1: Griewank, 2: Ackley

typedef struct {
    double position[DIM];
    double velocity[DIM];
    double best_position[DIM];
    double best_value;
} Particle;

double rand_double(double min, double max) {
    return min + ((double)rand() / RAND_MAX) * (max - min);
}

double objective_function(double sol[DIM]) {
    int i;
    double aux = 0, aux1 = 0, top = 0, top1 = 0, top2 = 1;

    switch (PROBLEM) {
        case 1: // Griewank
            for (i = 0; i < DIM; i++) {
                top1 += pow(sol[i], 2.0);
                //top2 *= cos(sol[i] / sqrt(i + 1)); //radianos -> C
                top2 *= cos((sol[i] / sqrt(i + 1)) * M_PI / 180.0);//versão em graus
            }
            top = (1.0 / 4000.0) * top1 - top2 + 1.0;
            return top;

        case 2: // Ackley
            for (i = 0; i < DIM; i++) {
                aux += sol[i] * sol[i];
                aux1 += cos(2.0 * M_PI * sol[i]);
            }
            return (-20.0 * exp(-0.2 * sqrt(aux / DIM)) - exp(aux1 / DIM) + 20.0 + exp(1.0));

        default:
            return 1e20; // erro
    }
}

void initialize_swarm(Particle swarm[], double xmin, double xmax, double vmin, double vmax) {
    for (int i = 0; i < NUM_PARTICLES; i++) {
        for (int j = 0; j < DIM; j++) {
            swarm[i].position[j] = rand_double(xmin, xmax);
            swarm[i].velocity[j] = rand_double(vmin, vmax);
            swarm[i].best_position[j] = swarm[i].position[j];
        }
        swarm[i].best_value = objective_function(swarm[i].position);
    }
}

void update_particles(Particle swarm[], double gbest_position[], double w, double c1, double c2, double xmin, double xmax, double vmin, double vmax) {
    for (int i = 0; i < NUM_PARTICLES; i++) {
        for (int j = 0; j < DIM; j++) {
            double r1 = rand_double(0.0, 1.0);
            double r2 = rand_double(0.0, 1.0);

            swarm[i].velocity[j] = w * swarm[i].velocity[j]
                + c1 * r1 * (swarm[i].best_position[j] - swarm[i].position[j])
                + c2 * r2 * (gbest_position[j] - swarm[i].position[j]);

            if (swarm[i].velocity[j] > vmax) swarm[i].velocity[j] = vmax;
            if (swarm[i].velocity[j] < vmin) swarm[i].velocity[j] = vmin;

            swarm[i].position[j] += swarm[i].velocity[j];

            if (swarm[i].position[j] > xmax) swarm[i].position[j] = xmax;
            if (swarm[i].position[j] < xmin) swarm[i].position[j] = xmin;
        }

        double val = objective_function(swarm[i].position);
        if (val < swarm[i].best_value) {
            swarm[i].best_value = val;
            for (int j = 0; j < DIM; j++)
                swarm[i].best_position[j] = swarm[i].position[j];
        }
    }
}

void find_gbest(Particle swarm[], double gbest_position[], double *gbest_value) {
    for (int i = 0; i < NUM_PARTICLES; i++) {
        if (swarm[i].best_value < *gbest_value) {
            *gbest_value = swarm[i].best_value;
            for (int j = 0; j < DIM; j++)
                gbest_position[j] = swarm[i].best_position[j];
        }
    }
}

int main() {
    srand(time(NULL));

    Particle swarm[NUM_PARTICLES];
    double gbest_position[DIM];
    double gbest_value = 1e20;

    double xmin = (PROBLEM == 1) ? -600.0 : -32.0;
    double xmax = (PROBLEM == 1) ? 600.0 : 32.0;
    double vmin = -1.0, vmax = 1.0;

    double w = 0.729, c1 = 2.05, c2 = 2.05;

    initialize_swarm(swarm, xmin, xmax, vmin, vmax);
    find_gbest(swarm, gbest_position, &gbest_value);

    for (int t = 0; t < MAX_ITER; t++) {
        update_particles(swarm, gbest_position, w, c1, c2, xmin, xmax, vmin, vmax);
        find_gbest(swarm, gbest_position, &gbest_value);
    }

    printf("Melhor valor encontrado: %.10f\n", gbest_value);
    return 0;
}
