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
    return (a/ (b * np.sqrt(x)) + 1/b)**2
    # return a * (x/(x+b))
    # funcaomath.pow(x,b)

def build_func(a, b): #a dependente, b independente
    def temp(x):
        return poly(x, a, b)
    return temp

if __name__ == '__main__':

    x = [1.0392, 1.5225, 2.4338, 2.9347, 4.369, 5.1732, 5.8309, 6.2558, 7.2268, 7.987, 8.6215, 9.3589]
    y = [5.0052, 3.8125, 2.7097, 2.3467, 1.7874, 1.6197, 1.5711, 1.6174, 1.2715, 1.2872, 1.2395, 1.0859]
    values = [2.6571, 8.8546, 9.1906]
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
    
    y_ = np.sqrt(y)
    x_ = np.sqrt(x)
    x__ = np.divide(1,x_)

    grau = 1
    """
    y^2 = a/(b*sqrt(x)) + 1/b
    """

    a0, a1 = best_line(x__, y_, grau)
    
    a = a1/a0
    b = 1/a0
   

    

    print('Coeficientes da reta')
    print(f'{a0} e {a1}')

    print('Coeficientes')
    print(f'{a}, {b},')

    p = build_func(a, b)

    def q(x):
        return p(x+k2) - k1

    px = [p(vi) for vi in values]
    print(f'{px}')