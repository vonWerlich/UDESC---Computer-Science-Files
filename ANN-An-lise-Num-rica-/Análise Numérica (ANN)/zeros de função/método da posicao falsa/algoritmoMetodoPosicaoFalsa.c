//algoritmo do método da posição falsa

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

void falseposition (double (*f)(double), double a, double b, int n) {
	int i;
	for (i=0; i<n; i++) {
		double fa = f(a);
		double fb = f(b);
		if (fa * fb >= 0) {
			printf("O teorema de Bolzano não sabe dixer se existe raiz para f nesse intervalo");
			break;
		}
		else {
			double x1 = (a * fb - b * fa) / (fb - fa);
			/*if (i==0||i==24||i==49||i==99||i==199||i==399||i==799||i==1599||i==3199||i==4799||i==6399||i==7999||i==9999) {
				
			}*/
			printf("x_%d = %.16f\n", i + 1, x1);
			double fx1 = f(x1);
			if (fa * fx1 < 0) {
				b = x1;
				fb = fx1;
			} else {
				a = x1;
				fa = fx1;
			}
		}
	}
		
}

int main () {
	
	setlocale(LC_ALL, "Portuguese");
	
	double f (double x) {
		
		return M_PI*x*x*(3*5.31-x)/3.0 - 487.68; //função que se quer calcular
	}
	
	double a = 0; //valor chute inicial
	double b = 10.62; //valor chute final
	int n = 20; //número de iterações
	
	falseposition(f, a, b, n);
}
