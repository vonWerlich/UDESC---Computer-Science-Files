#include "methods.h"

#define r 1.13
#define ps 304.38
#define pw 1000

double f(double h) {
	return pw*((pow(r,3) * 4 /3) - (pow(h,2))*r + (pow(h,3))/3) - ps*(4*(pow(r,3))/3);
}

double df(double h) {
	return pw*(-2*h*r + pow(h,2));
}

int main(void) {
	int iterationsBissection[] = {2, 4, 8, 12};
	int iterationsNewton[] = {1, 3, 5};
	int iterationsSecant[] = {1, 2, 5};
	int iterationsFalsePosition[] = {2, 4, 7, 9};

	// Método da Bisseção
	for(int i = 0; i < sizeof(iterationsBissection) / sizeof(iterationsBissection[0]); i++) {
		bisection(f, 0, 2.26, iterationsBissection[i]);
	}
	printf("\n");

	// Método de Newton
	for(int i = 0; i < sizeof(iterationsNewton) / sizeof(iterationsNewton[0]); i++) {
		newton(f, df, 0.76, iterationsNewton[i]);
	}
	printf("\n");

	// Método da Secante
	for(int i = 0; i < sizeof(iterationsSecant) / sizeof(iterationsSecant[0]); i++) {
		secant(f, 0.16, 1.9, iterationsSecant[i]);
	}
	printf("\n");

	// Método da Posição Falsa
	for(int i = 0; i < sizeof(iterationsFalsePosition) / sizeof(iterationsFalsePosition[0]); i++) {
		falsePosition(f, 0, 2.26, iterationsFalsePosition[i]);
	}
	printf("\n");

	return 0;
}
