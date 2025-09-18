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
    return a*x * np.exp(b*x)
    # return a * (x/(x+b))
    # funcaomath.pow(x,b)

def build_func(a, b):
    def temp(x):
        return poly(x, a, b)
    return temp

if __name__ == '__main__':

    x = [0.3033, 0.4726, 0.747, 0.9104, 1.2564, 1.4302, 1.6021, 1.9809, 2.1345, 2.441, 2.6961, 2.9181, 3.1564, 3.3192, 3.6184, 3.6951, 3.8875, 4.1536, 4.3624, 4.701, 4.9915, 5.105, 5.4566, 5.6719, 5.958, 6.083, 6.3206, 6.5542, 6.9153, 6.9785, 7.3205, 7.5605, 7.8562, 8.1131, 8.2556, 8.5666, 8.6399, 8.8336, 9.1384, 9.485, 9.5414, 9.7987]
    y = [1.2063, 1.8611, 2.556, 3.002, 3.6487, 3.8903, 4.1248, 4.5266, 4.5921, 4.8186, 4.8871, 4.8351, 4.8608, 4.8511, 4.7903, 4.7568, 4.6742, 4.6224, 4.5248, 4.3478, 4.1939, 4.1309, 3.9299, 3.7755, 3.6075, 3.5605, 3.4053, 3.2676, 3.0639, 3.1077, 2.8298, 2.7601, 2.544, 2.4481, 2.3686, 2.2075, 2.1887, 2.0853, 1.963, 1.8283, 1.8003, 1.7291]
    values = [2.038, 2.5876, 3.0382, 3.0846, 4.3866]
    if min(y) <= 0:
        k1 = abs(min(y)) + 1
    else:
        k1 = 0

    if min(x) <= 0:
        k2 = abs(min(x)) + 1
    else:
        k2 = 0

    yt = [yi + k1 for yi in y]

    y_ = np.log(np.divide(y,x))

    xt = [xi + k2 for xi in x]

    x_ = x
    grau = 1

    a0, a1 = best_line(x_, y_, grau)

    a = np.exp(a0)

    b = a1

    print('Coeficientes da reta')
    print(f'{a0} e {a1}')

    print('Coeficientes')
    print(f'{a}, {b},')

    p = build_func(a, b)

    def q(x):
        return p(x+k2) - k1

    px = [p(vi) for vi in values]
    print(f'{px}')

"""     # visualização
    import matplotlib.pyplot as plt
    plt.scatter(x, y)
    t = np.linspace(min(x), max(x), 200)
    qt = [q(ti) for ti in t]
    plt.plot(t, qt)
    plt.savefig('best_poly_regressao_potencia.png') """