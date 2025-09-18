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

void secante (double (*f)(double), double x0, double x1, int n) {
	int i;
	for (i=0; i<n; i++) {
		double fx0 = f(x0);
		double fx1 = f(x1);
		if (fx0 == fx1) {
			break;
		}
		else {
			double x2 = (x0 * fx1 - x1 * fx0) / (fx1 - fx0);
			printf("x_%d = %.16f\n", i + 1, x2);
			x0 = x1;
			x1 = x2;
		}
	}
		
}

int main () {
	
	setlocale(LC_ALL, "Portuguese");
	
	double f (double x) {
		return M_PI*x*x*(3*5.31-x)/3.0 - 487.68; //função que se quer calcular
	}
	
	double x0 = 1.73 ; //valor chute inicial
	double x1 = 10.47; //valor chute final
	int n = 10; //número de iterações
	
	secante(f, x0, x1, n);
}
