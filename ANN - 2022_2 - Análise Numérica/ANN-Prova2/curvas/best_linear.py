import numpy as np

def best_line(x, y):
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

# exemplo:
x = [0.087, 0.5752, 0.7871, 1.0833, 1.324, 1.728, 2.0261, 2.2336, 2.7357, 2.975, 3.4071, 3.4764, 3.9499, 4.3469, 4.5818, 4.8382, 5.045, 5.5674, 5.7577, 6.0457, 6.5492, 6.7789, 7.0723, 7.4166, 7.5884, 8.0454, 8.2089, 8.5481, 8.8089, 9.1771, 9.5944, 9.7615]
y = [5.1538, 5.7789, 6.1988, 6.2869, 6.4683, 7.1195, 7.491, 7.9423, 8.1022, 8.4249, 8.9625, 8.9701, 9.6287, 10.0631, 10.3667, 10.8078, 10.9105, 11.641, 11.822, 12.32, 12.6488, 13.0626, 13.5551, 13.7856, 13.975, 15.0389, 14.6071, 14.9874, 15.2336, 15.8738, 16.3116, 16.5435]

a0, a1 = best_line(x, y)

def p(a0,a1,x):
    return a0 + a1 * x

print(f'{a0} e {a1}')

values = [3.1495, 3.2117, 4.8575, 9.258, 9.2601]

for v in values:
    print(p(a0,a1,v))