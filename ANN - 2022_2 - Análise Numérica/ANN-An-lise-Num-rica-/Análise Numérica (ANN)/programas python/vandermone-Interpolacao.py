import math
from cmath import cos
from math import log

import numpy as np

def vandermonde(x,y):
    """
    x = lista das coordenadas x
    y = lista das coordenadas y
    Retorna os coeficientes do polinômio inetrpolador da lista
    de pontos x,y
    """
    A = []
    B = y
    n = len(x)
    for xi in x:
        row = [1] + [xi ** k for k in range(1, n)]
        A.append(row)
    return np.linalg.solve(A,B)

def build_poly(coeffs):
    def func(x):
        soma = coeffs[0]
        for i, ci in enumerate(coeffs[1:], 1):
            soma += ci * x ** i
        return soma
    return func

if __name__ == '__main__':

    """
    import matplotlib.pyplot as plt
    
        # exemplo 1
        x = [1, 3]
        y = [2, -1]
    
        coeffs = vandermonde (x, y)
    
        print(coeffs)
    
        p = build_poly(coeffs)
    
        print(f'{p(1) = } e {p(3) = }')
    
        #apenas para visualização
        import matplotlib.pyplot as plt
    
        t = np.linspace(-1,4, 100)
    
        pt = [p(ti) for ti in t]
    
        plt.plot(t, pt, color="red")
        plt.scatter(x,y, color="blue")
    
        plt.savefig('interp.png')
    """

    import matplotlib.pyplot as plt

    np.set_printoptions(suppress=True)
    np.set_printoptions(precision=14)
    # exemplo 1
    x = [1.491, 1.802, 2.326, 2.459, 2.773, 3.078, 3.527, 3.724, 4.257, 4.429, 4.905]

    def f(x):
        return math.cos(x + math.sqrt(log(x**2,math.e)))
    y = [f(xi) for xi in x]

    #y = [1.962621901897,]

    coeffs = vandermonde(x, y)

    print(coeffs)

    p = build_poly(coeffs)

    #print(f'{p(0) = },{p(1) = },{p(2) = },{p(3) = },{p(4) = },{p(5) = },{p(6) = }')

    # apenas para visualização
    import matplotlib.pyplot as plt

    t = np.linspace(-1, 7, 100)

    pt = [p(ti) for ti in t]

    plt.plot(t, pt, color="red")
    plt.scatter(x, y, color="blue")

    plt.savefig('interp.png')