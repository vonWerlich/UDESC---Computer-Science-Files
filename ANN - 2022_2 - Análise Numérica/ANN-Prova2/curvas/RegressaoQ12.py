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
    return a * np.exp(x*b)
    # funcaomath.pow(x,b)

def build_func(a, b):
    def temp(x):
        return poly(x, a, b)
    return temp

if __name__ == '__main__':
    x = [0.1326, 0.1835, 0.4279, 0.5761, 0.7271, 0.9399, 1.1093, 1.2289, 1.4363, 1.5202, 1.7761, 1.882]
    y = [5.6641, 6.7215, 9.4853, 13.3957, 16.0673, 23.7071, 32.4343, 38.8485, 55.2191, 63.4118, 98.298, 117.892]
    values = [0.5282, 0.7407, 1.8516]
    if min(y) <= 0:
        k1 = abs(min(y)) + 1
    else:
        k1 = 0

    if min(x) <= 0:
        k2 = abs(min(x)) + 1
    else:
        k2 = 0

    y_ = np.log(y)

    x_ = np.log(x)
    grau = 1

    a0, a1 = best_line(x, y_, grau)

    a = np.exp(a0)

    b = a1
    print('Coeficientes da reta')
    print(f'{a0 },{a1 }')

    print('Coeficientes')
    print(f'{a },{b }')

    p = build_func(a, b)

    def q(x):
        return p(x+k2) - k1

    px = [p(vi) for vi in values]
    print(f'{px}')