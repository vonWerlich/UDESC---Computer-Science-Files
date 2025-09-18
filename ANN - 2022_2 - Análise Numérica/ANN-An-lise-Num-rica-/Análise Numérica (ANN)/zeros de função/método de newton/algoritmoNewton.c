#include <stdio.h>
#include <math.h>
#define _USE_MATH_DEFINES //use M_PI para usar o valor de pi
#include <locale.h>

/* Definitions of useful mathematical constants
 * M_E        - e
 * M_LOG2E    - log2(e)
 * M_LOG10E   - log10(e)
 * M_LN2      - ln(2)
 * M_LN10     - ln(10)
 * M_PI       - pi
 * M_PI_2     - pi/2
 * M_PI_4     - pi/4
 * M_1_PI     - 1/pi
 * M_2_PI     - 2/pi
 * M_2_SQRTPI - 2/sqrt(pi)
 * M_SQRT2    - sqrt(2)
 * M_SQRT1_2  - 1/sqrt(2)
 */

void newton (double (*f)(double), double (*df)(double), double x0, int n) {
	int i;
	for (i=0; i < n; i++) {
		double dfx0 = df(x0);
		if (dfx0 == 0) {
			break;
		}
		double xi = x0 - f(x0) / df(x0);
		printf("x_%d = %.16f\n", i + 1, xi);
		x0 = xi;
	}
}

int main () {
	
	setlocale(LC_ALL, "Portuguese");
	
	double f(double x) {
		return M_PI*x*x*(3*5.31-x)/3.0 - 487.68; //função a ser calculada a raiz
	}
	
	double df (double x) {
		
		return 1.04719755119659774615421446*(-3*x*x +31.86*x); //derivada da função que se quer calcular a raiz
	}
	
	double x0 = 4.27 ; //chute inicial
	int n = 20; //número de iterações
	
	newton (f,df,x0,n);
}
