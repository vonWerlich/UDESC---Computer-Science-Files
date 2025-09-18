import math
import numpy

def f1(x, y):
    return x**2 + y**2 - 5

def f2(x, y) :
    return x**2 + x * y**3 - 3

def f1x(x, y) : # derivada de f1 em relação a x
    return 2 * x

def f1y(x, y) : # derivada de f1 em relação a y
    return 2 * y

def f2x(x, y) : #derivada de f2 em relação a x
    return 2 * x

def f2y(x, y) : # derivada de f2 em relação a y
    return 3 * x * y**2

def NewtonNaoLinear(f1,f2,f1x,f1y,f2x,f2y,x0,y0,n) :

    for _ in range(n):
        a = f1x(x0, y0)
        b = f1y(x0, y0)
        c = f2x(x0, y0)
        d = f2y(x0, y0)
        det = a * d - b * c
        xk = x0 - (f2y(x0, y0) * f1(x0, y0) -f1y(x0, y0) * f2(x0, y0)) / det
        yk = y0 - (-f2x(x0, y0) * f1(x0, y0) + f1x(x0, y0) * f2(x0, y0)) / det
        x0 = xk
        y0 = yk
        # printf("x^(%d) = %.12f\ty^(%d) = %.12f\n", i + 1, x0, i + 1, y0);
        #printf("%.12f,%.12f,", x0, y0);
        yield x0,y0


x0 = -1.9981
y0 = 1.4974
n = 5 # iterações



resp = list(NewtonNaoLinear(f1,f2,f1x,f1y,f2x,f2y,x0,y0,n))

iterations = [1, 2, 3, 4, 5]

for i in iterations:
    print(resp[i - 1])