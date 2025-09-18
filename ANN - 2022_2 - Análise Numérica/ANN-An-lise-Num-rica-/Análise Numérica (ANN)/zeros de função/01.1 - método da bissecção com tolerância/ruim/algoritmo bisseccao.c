#include <stdio.h>
#include <math.h>

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
			if (fa * fb < 0) {
				b = m;
			} else {
				a = m;
				fa = fm;
			}
		}
	}
}

int main () {
	double f(double x) {
		return x * x - 3;//fun��o a ser encontrado o zero
	}
	double a = 1;//intervalo inicial
	double b = 2;//intervalo final
	int n = 100;//n�mero de itera��es
	double tol = 0.0001;//toler�ncia
	
	bisection (f, a, b, n, tol);
}


