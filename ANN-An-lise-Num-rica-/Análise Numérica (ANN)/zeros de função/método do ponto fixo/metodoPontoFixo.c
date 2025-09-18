//algoritmo do m�todo do ponto fixo
/*As fun��es a serem calculadas precisam respeitar os teoremas do Ponto
Fixo de Brouwer e de Banach.

TPF Brouwer: (Exist�ncia)
Se f(x) � cont�nua e se para todo f(x) pertence a [a,b] e x tamb�m 
pertence a [a,b], ent�o existe pelo menos um ponto fixo nesse intervalo
[a,b].
Teorema de Unicidade:
Se uma fun��o � deriv�vel em todos os pontos de seu dom�nio, e o m�dulo
desssa derivada � sempre menor que uma certa constante k estritamente
menor que 1, e se f possui um ponto fixo nesse intervalo, ent�o ele �
�nico.

Al�m disso, essas fun��es s�o do tipo
f(x) + x = x, onde f(x) = 0
*/
#include <stdio.h>
#include <math.h>
#define _USE_MATH_DEFINES
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

void fixed_point (double (*f)(double), double x0, int n) {
	int i;
	for (i=0; i<n; i++) {
		x0 = f(x0);
		printf("x_%d = %.16f\n", i + 1, x0);
		
	}
		
}

int main () {
	
	setlocale(LC_ALL, "Portuguese");
	
	double f (double x) {
		return ((3 * pow(x, 4) + 2 * pow(x, 2) + 3) / (4 * pow(x, 3) + 4 * x - 1)); //fun��o que se quer calcular
	}
	
	double x0 = 1.60004; //chute inicial

	int n = 10; //n�mero de itera��es
	
	fixed_point(f, x0, n);
}
