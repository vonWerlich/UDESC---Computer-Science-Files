import numpy as np
# import scipy as sp

def best_poly (x, y, k):    # k é o grau do polinômio!
    n = len(x)
    if n <= k:
        raise ValueError('O número de pontos deve ser maior que k (o grau do polinônmio)')

    somas = {}
    somas[0] = n
    for n in range(1, 2*k + 1):
        somas[n] = sum(xi ** n for xi in x)
    A = []
    B = []
    for i in range (k + 1):
        row = []
        for j in range(k + 1):
            row.append(somas[i + j])
        A.append(row)
        if i == 0:
            B.append(sum(y))
        else:
            B.append(sum(xi ** i * yi for xi, yi in zip(x,y)))
    #print(A)
    #print(B)
    return np.linalg.solve(A, B)
    
x = [0.4903, 1.1406, 2.4152, 3.2955, 3.8399, 4.4138, 5.7348, 5.9935, 7.32, 7.5755, 8.802, 9.8901]
y = [5.6185, 5.1415, 4.1933, 3.8195, 3.6419, 3.5338, 3.3911, 3.3453, 3.2622, 3.6355, 4.2136, 4.7819]
values = [2.8554, 6.7649, 9.0889]

a0, a1, a2 = best_poly(x, y, 2)   # precisa alterar a quantidade de pontos dependendo do grau do polinômio

def p(a0,a1,a2,x):
    return a0 + a1 * x + a2 * x**2 #fórmula do polinômio

print(f'{a0},{a1},{a2}')

for v in values:
    print(",",p(a0,a1,a2,v))