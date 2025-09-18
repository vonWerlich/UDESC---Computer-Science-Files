#include <stdio.h>

#define numRows 7
#define numCols 8

// só funciona para sistemas n x n
void seidel(double E[numRows][numCols], double chute[numRows], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < numRows; j++) {
            double bj = E[j][numCols - 1];
            double soma = 0;
            for (int k = 0; k < numCols - 1; k++) {
                if (k != j) {
                    soma += E[j][k] * chute[k];
                }
            }
            double xj = (bj - soma) / E[j][j];
            chute[j] = xj;
           // if (i+1==1||i+1==3||i+1==4||i+1==5||i+1==6||i+1==7||i+1==11||i+1==12||i+1==16||i+1==17||i+1==23||i+1==25) {
           // 	printf("%.16f,",xj);
		//	}
           printf("x_%d^(%d) = %.16f\t", j + 1, i + 1, xj);
        }
        printf("\n");
    }
}

int main() {
    double E[numRows][numCols] = {
        {1,+1.151,1.324801,+4.869},
		{1,+3.352,11.235904,+3.417},
		{1,+6.491,42.133081,+2.802},
		{1,+6.491,42.133081,+2.802},
		{1,+1.151,1.324801,+4.869},
		{1,+3.352,11.235904,+3.417},
		{1,+6.491,42.133081,+2.802},
    };
    double chute[numRows] = {-1.39,-2.3,-0.68};
    int n = 70;

    seidel(E, chute, n);
}
