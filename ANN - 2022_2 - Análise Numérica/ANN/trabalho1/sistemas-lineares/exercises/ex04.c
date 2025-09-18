#include "../methods.h"

int main(void) {
	int *rows = malloc(sizeof(int));
	int *cols = malloc(sizeof(int));
	double **matrix = Matrix(rows, cols);
	double *arr = malloc((*rows) * sizeof(double));
	arr[0] = -3.15;
	arr[1] = -1.4;
	arr[2] = -4.64;
	int iterations[] = {4, 6, 8, 12, 13, 14, 16, 19};
	int numIterations = 8;

	printMatrix(matrix, *rows, *cols);
	jacobi(matrix, *rows, *cols, arr, iterations[numIterations-1] + 1, iterations);

	return 0;
}
