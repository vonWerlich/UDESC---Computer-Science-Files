#include <stdio.h>

#define numRows 3
#define numCols 4

// só funciona para sistemas n x n
void jacobi(double E[numRows][numCols], double chute[numRows], int n) {
    for (int i = 0; i < n; i++) {
        double resp[numRows] = {};
        for (int j = 0; j < numRows; j++) {
            double bj = E[j][numCols - 1];
            double soma = 0;
            for (int k = 0; k < numCols - 1; k++) {
                if (k != j) {
                    soma += E[j][k] * chute[k];
                }
            }
            double xj = (bj - soma) / E[j][j];
            resp[j] = xj;
            if (i+1==7||i+1==8||i+1==11||i+1==12||i+1==15||i+1==17||i+1==18||i+1==19) {
            	printf("%.16f,",xj);
			}
           // printf("x_%d^(%d) = %.16f\t", j + 1, i + 1, xj);
        }
        //printf("\n");
        for (int i = 0; i < numRows; i++) {
            chute[i] = resp[i];
        }
    }
}

int main() {
    double E[numRows][numCols] = {
        {-6.16,-2.88,+1.8,1.1},
		{4.88,+9,-2.63,3.7},
		{1.23,+4.51,+7.22,-3.65}
    };
    double chute[numRows] = {1.66, 4.48, -2.31};
    int n = 20;

    jacobi(E, chute, n);
}
