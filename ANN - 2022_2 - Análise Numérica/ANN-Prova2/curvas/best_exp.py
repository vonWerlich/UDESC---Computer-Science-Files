import math
import matplotlib.pyplot as plt
import numpy as np

def poly_regression(x, y, k =1):
    A = [[0 for _ in range(k+1)] for _ in range(k+1)]
    B = []
    powers_x = {0: len(x)}
    for i in range(1, 2 * k + 1):
        powers_x[i] = sum(xi ** i for xi in x)
    
    for i in range(k+1):
        for j in range(k + 1):
            p = i + j
            A[i][j] = powers_x[p]
        if i == 0:
            B.append(sum(y))
        else:
            B.append(sum(yi * xi ** i for xi, yi in zip(x,y ) ))
    return np.linalg.solve(A, B)
"""
def dummy():
    def func(x):
        erro = -4 + 2 * np.random()
        return 0.2 * x**3 - 3 * x + 4 + erro
    return func

def build_poly(coeffs):
    def func(x):
        soma = coeffs[0]
        for i, ci in enumerate(coeffs[1:], 1):
            soma += ci * x ** i
        return soma
    return func"""

x = [1, 2, 3, 4, 5]
y = [3, 10, 25, 90, 250]
Y = [math.log(yi) for yi in y]

a0, a1 = poly_regression(x, Y, k=1)

a = math.exp(a0)
b = a1

def f(x):
    return a * math.exp(b * x)

t = np.linspace(min(x), max(x), 200)
ft = [f(ti) for ti in t]

plt.scatter(x, y)
plt.plot(f, ft, color='red')

plt.savefig('best_exp.png')
