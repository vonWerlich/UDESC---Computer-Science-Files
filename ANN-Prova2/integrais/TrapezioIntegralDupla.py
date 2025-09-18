import numpy as np

def double_trapz(f, a: float, b: float, c: float, d: float, n1: int, n2: int) -> float:
    if n1 <= 0 or n2 <= 0:
        raise ValueError('Ops, isso não pode')
    h1 = (b - a) / n1
    h2 = (d - c) / n2
    soma_interior = 0
    for i in range(1, n1):
        for j in range (1, n2):
            soma_interior += f(a + i * h1, c + j * h2)
    soma_arestas_horizontais = 0
    for i in range(1, n1):
        for j in [0, n2]:
            soma_arestas_horizontais += f(a + i * h1, c + j * h2)
    soma_arestas_verticais = 0
    for j in range(1, n2):
        for i in [0, n1]:
            soma_arestas_verticais += f(a + i * h1, c + j *h2)
    soma_vertices = 0
    for i in [0,n1]:
        for j in [0,n2]:
            soma_vertices += f(a + i * h1, c + j * h2)
    return (h1 * h2 / 4) * (soma_vertices + 4 * soma_interior + 2 * (soma_arestas_horizontais + soma_arestas_verticais))

def f(x,y):
    """np.cos(x**2)*np.sin((y**2)*x)*np.exp(-y**2) + 1"""
    return np.sqrt(np.exp((-x**2)*y**2) + 1)

a1 , b1 = [-1.924, 1.025]
a2 , b2 =  [-1.67, 1.464]
n1 = 256
n2 = 128

r = double_trapz(f, a1, b1, a2, b2, n1, n2)
print(r)
