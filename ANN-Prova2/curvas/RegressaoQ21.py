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
    return a * np.log(x) + b
    # return a * (x/(x+b))
    # funcaomath.pow(x,b)

def build_func(a, b):
    def temp(x):
        return poly(x, a, b)
    return temp

if __name__ == '__main__':

    x = [1.3432, 1.8346, 3.0947, 3.5823, 4.4174, 5.0932, 5.7735, 6.3881, 7.3092, 8.3749, 8.635, 9.3255]
    y = [5.0021, 5.4741, 6.521, 6.7544, 7.0942, 7.356, 7.6748, 7.8027, 7.9786, 8.2869, 8.2481, 8.3967]
    values = [6.122, 6.6832, 8.7955]
    if min(x) <= 0:
        k1 = abs(min(x)) + 1
    else:
        k1 = 0

    if min(y) <= 0:
        k2 = abs(min(y)) + 1
    else:
        k2 = 0

    yt = [yi + k1 for yi in y]
    xt = [xi + k2 for xi in x]
    
    y_ = np.divide(1,y)
    x_ = np.log(x)

    grau = 1
    """
    y = a1 * ln(x) + a0
    """

    a0, a1 = best_line(x_, y, grau)

    a = a1

    b = a0

    print('Coeficientes da reta')
    print(f'{a0} e {a1}')

    print('Coeficientes')
    print(f'{a}, {b},')

    p = build_func(a, b)

    def q(x):
        return p(x+k2) - k1

    px = [p(vi) for vi in values]
    print(f'{px}')