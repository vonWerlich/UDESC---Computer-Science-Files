#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#include <locale.h>

void bisection (double (*f) (double), double a, double b, int n, double tol) {
	double fa = f(a);
	double fb = f(b);
	if (fa * fb >= 0) {
		printf("Voc� n�o pode usar esse intervalo.");
		return;
	} else {
		int i;
		for (i=0; i<n; i++) {
			double m = 0.5 * (a + b);
			double fm = f(m);
			if (fm == 0) {
				printf("Voc� encontrou uma raiz r=%.16f", m);
				return;
			}
			printf("x_%d = %.16f\n", i + 1, m);
			if (fabs(fm) < tol) {
				printf("atingiu a toler�ncia => x_%d = %.16f\n", i + 1, m);
				return;
			}
			if (fa * fm < 0) {
				b = m;
			} else {
				a = m;
				fa = fm;
			}
		}
	}
}

int main () {
	
	setlocale(LC_ALL, "Portuguese");
	
	double f(double x) {
	
		return (4.0/3.0*M_PI*x*x*X - (M_PI*x*x*(3*5.1-x)/3.0 - 487.68))*;//fun��o a ser encontrado o zero
	}
	double a = 0;//intervalo inicial
	double b = 10.62;//intervalo final
	int n = 15;//n�mero de itera��es
	double tol = 0.000000000000001;//toler�ncia

	
	bisection (f, a, b, n, tol);
}
