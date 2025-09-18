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

x = [-4.776, -4.4834, -4.3603, -4.0436, -3.692, -3.3066, -3.2468, -2.8761, -2.4186, -2.2179, -1.8716, -1.8086, -1.336, -1.0682, -0.8365, -0.4215, -0.2003, 0.0286, 0.4067, 0.5906, 1.0709, 1.0843, 1.5424, 1.6706, 2.1214, 2.5232, 2.6864, 2.9742, 3.151, 3.4411, 3.8754, 4.0516, 4.3001, 4.6197, 4.8953, 5.181, 5.4923, 5.938]
y = [-7.9218, -3.7307, -4.0645, -0.2215, 1.6622, 2.6261, 2.0126, 2.3836, 2.4586, 2.0115, 1.6345, 1.1989, 0.6095, 0.011, -0.4713, -0.5504, -0.6747, -0.6567, -0.5059, -0.6185, -0.3513, 0.3813, 1.1553, 1.4742, 2.4786, 3.8498, 3.8433, 4.42, 6.2809, 5.8273, 5.2049, 4.9259, 2.4144, 2.5579, 1.2483, -1.8739, -6.394, -13.0826]
values = [-4.6295, 1.1748, 2.2018, 2.5777, 5.503]


a0, a1, a2, a3, a4 = best_poly(x, y, 4)   # precisa alterar a quantidade de pontos dependendo do grau do polinômio

def p(a0,a1,a2,a3,a4,x):
    return a0 + a1 * x + a2 * x**2 + a3 * x**3 + a4 * x**4 #fórmula do polinômio

print(f'{a0},{a1},{a2},{a3},{a4}')

for v in values:
    print(",",p(a0,a1,a2,a3,a4,v))