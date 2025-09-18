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
    return np.linalg.solve(A, B)

x = [-4.4368, -4.1835, -3.8742, -3.6419, -3.5681, -3.383, -3.1033, -2.8926, -2.5317, -2.5046, -2.1669, -2.069, -1.6978, -1.5023, -1.2673, -1.0314, -0.8531, -0.7641, -0.4878, -0.321, -0.0633, 0.1145, 0.3572, 0.716, 0.8767, 1.0809, 1.2731, 1.6026, 1.6916, 2.0503, 2.095, 2.3253, 2.563, 2.7716, 3.1329, 3.391, 3.6125, 3.7934, 3.9033, 4.1828, 4.4853]
y = [-5.4332, -1.9433, 0.4307, 2.0152, 2.0752, 2.6087, 2.1392, 1.869, 2.6518, 1.1227, 0.2568, 0.1286, -0.3463, -0.7021, -0.9307, -1.0805, -0.6505, -0.9126, -0.8176, -0.6477, -0.2027, 0.4046, -0.03, 1.1656, -1.0311, 1.0007, 0.823, 0.7093, 0.3251, 0.1419, -0.3818, -0.9739, -1.4907, -1.9074, -3.7632, -2.4683, -2.1626, -1.132, -0.9562, 1.9929, 5.7357]
values = [-3.2629, -2.5187, -1.7326, 0.12, 2.9294]

a0, a1, a2, a3, a4, a5 = best_poly(x, y, 5)   # precisa alterar a quantidade de pontos dependendo do grau do polinômio

def p(a0,a1,a2,a3,a4,a5,x):
    return a0 + a1 * x + a2 * x**2 + a3 * x**3 + a4 * x**4 + a5 * x**5 #fórmula do polinômio

print(f'{a0},{a1},{a2},{a3},{a4},{a5}')

for v in values:
    print(",",p(a0,a1,a2,a3,a4,a5,v))