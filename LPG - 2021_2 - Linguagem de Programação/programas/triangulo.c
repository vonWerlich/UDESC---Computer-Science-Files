#include <stdio.h>

int main ()
{
double a,b,c,perimetro,area;	
	
scanf("%lf", &a);
scanf("%lf", &b);
scanf("%lf", &c);
	
perimetro= a + b + c;
area= (a+b)*c/2.0;	
	
if ((a+b>c)&&(a+c>b)&&(b+c>a))
{printf("Perimetro = %.1lf\n",perimetro);}	
else
{printf("Area = %.1lf\n",area);}
	
	
	return 0;
}
