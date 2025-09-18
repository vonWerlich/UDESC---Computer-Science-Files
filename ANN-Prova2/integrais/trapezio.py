import math
from numpy import double
import numpy as np

# Usado para aproximar o valor de uma integral
def trapz(f, a, b, n):
    h = (b-a) / n
    soma = 0
    for k in range(1, n):
        soma += f(a + k*h)
    soma *= 2
    soma += (f(a) + f(b))
    return (h/2) * soma


def f(x,y):
    """-x * (x - 21) * (x + 1)"""
    return np.cos(x**2)*np.sin((y**2)*x)*np.exp(-y**2) + 1


a = -1.34,   # Variável inferior
b = 1.085   # Variável superior
a2 = -1.695
b2 = 1.744

# Lista de subintervalos
n = [6]
n2 = [8]

for i in range(len(n)):
    r = trapz(f, a, b, n[i])
    print(r)