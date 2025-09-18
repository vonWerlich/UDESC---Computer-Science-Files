import numpy as np
import math

def best_line(x, y, grau=1):
    n = len(x)
    # soma das coordenadas x
    sum_x = sum(x)
    # soma das coordenadas x**2
    sum_x2 = sum(xi ** 2 for xi in x)
    # soma das coordenadas y
    sum_y = sum(y)
    #soma das coordenadas x*y
    sum_xy = sum(xi * yi for xi, yi in zip(x, y))

    # Matriz dos coeficientes
    A = [[n, sum_x], [sum_x, sum_x2]]
    # Matriz dos termos independentes
    B = [sum_y, sum_xy]

    return np.linalg.solve(A, B)

def poly(x, a, b):
    return (a * x **2)/(b + x**2)
    # return a * (x/(x+b))
    # funcaomath.pow(x,b)

def build_func(a, b):
    def temp(x):
        return poly(x, a, b)
    return temp

if __name__ == '__main__':

    c = [1.8078, 2.2975, 3.1909, 4.0569, 5.1373, 6.0349, 7.184, 7.7315, 8.7599, 9.634, 10.827, 11.4702]
    k = [1.0947, 1.4532, 1.8285, 2.2545, 2.5181, 2.6028, 2.8765, 2.9138, 2.8542, 2.8322, 2.9475, 2.9454]
    values = [2.2609, 7.5161, 11.1588]
    if min(k) <= 0:
        k1 = abs(min(k)) + 1
    else:
        k1 = 0

    if min(c) <= 0:
        k2 = abs(min(c)) + 1
    else:
        k2 = 0

    yt = [yi + k1 for yi in k]
    xt = [xi + k2 for xi in c]
    
    x2 = np.multiply(c,c)
    y_ = np.divide(1,k)
    x_ = np.divide(1,x2)

    grau = 1
    """
    1/y = 1/a + b/(a*x**2)
    """

    a0, a1 = best_line(x_, y_, grau)

    a = 1/a0

    b = a1/a0

    print('Coeficientes da reta')
    print(f'{a0} e {a1}')

    print('Coeficientes')
    print(f'{a}, {b},')

    p = build_func(a, b)

    def q(x):
        return p(x+k2) - k1

    px = [p(vi) for vi in values]
    print(f'{px}')