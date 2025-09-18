import math
from numpy import double

# Usado para aproximar o valor de uma integral
def trapz(f, a, b, n):
    h = (b-a) / n
    soma = 0
    for k in range(1, n):
        soma += f(a + k*h)
    soma *= 2
    soma += (f(a) + f(b))
    return (h/2) * soma


def f(x):
    return math.sqrt(math.sin(math.cos(math.log(x**2+1)+2)+3)+4)

# Variável inferior
a = -1.334

# Variável superior
b = 1.502

# Lista de subintervalos
n = [4, 16, 40, 57, 97, 117, 158, 454, 727, 969, 2334, 8526]

for i in range(len(n)):
    r = trapz(f, a, b, n[i])
    print(r,",")