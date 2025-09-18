# algoritmo Spline Cúbico
import numpy as np

def spline (x,y):
    """
    Retorna todos os coeficientes de todos os polinômios,
    ou seja, todos os ak, bk, ck dk
    """

    # (1,1), (2,4), (4,2), (5,3)
    x = [1, 2, 4, 5]
    y = [1, 4, 2 ,3]

    n = len(x)
    a = {k: v for k, v in enumerate(y)}
    h = {k: x[k + 1] - x[k] for k in range(len(x) - 1)}

    A = [[1]+[0]*(n-1)]
    for i in range(1, n-1):
        row = [0] * n
        row[i-1] = h[i-1]
        row[i] = 2*(h[i-1] + h[i])
        row[i+1] = h[i]
        A.append(row)
    A.append([0] * (n-1) + [1])

    B = [0]
    for k in range (i, n-1):
        row = 3 * (a[k+1] - a[k]) / h[k] - 3* (a[k] - a[k-1]) / h[k-1]
        B.append(row)
    B.append(0)

    c = dict(zip(range(n), np.linalg.solve(A,B)))
    b = {}
    d = {}
    for k in range (n-1):
        b[k] = (1/h[k]) * (a[k+1] - a[k]) - (h[k]/3) * (2*c[k] + c[k+1])
        d[k] = (c[k+1] - c[k])/(3*h[k])

    s = {}
    for k in range (n-1) :
        s[k] = {'coefs': [a[k], b[k], c[k], d[k]], 'domain': [x[k], x[k+1]]}
