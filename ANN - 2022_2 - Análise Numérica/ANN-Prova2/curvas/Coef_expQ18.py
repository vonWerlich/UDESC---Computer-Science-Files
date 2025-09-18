import numpy as np

def best_poly(x, y, grau = 1):
    k = grau + 1
    A = [[0 for _ in range(k)] for _ in range(k)]
    B = [sum(y)]
    n = len(x)
    cache = {}
    for i in range(k):
        for j in range(k):
            p = i + j
            if (p == 0):
                A[0][0] = n
                continue
            if p not in cache:
                cache[p] = sum([xi ** p for xi in x])
            A[i][j] = cache[p]
        if i > 0:
            B.append(sum([yi * xi ** i for xi, yi in zip(x, y)]))
    return np.linalg.solve(A, B)

def poly(x, a, b):
    return a * x * np.exp(b*x) #funçao

def build_func(a, b):
    def temp(x):
        return poly(x, a, b)
    return temp

if __name__ == '__main__':

    x = [0.9064, 1.3482, 1.8046, 3.1805, 3.459, 4.3441, 5.7162, 6.631, 7.1396, 7.9431, 8.9549, 9.5597]
    y = [2.5542, 3.0494, 3.4672, 3.0812, 2.9068, 2.4153, 1.6719, 1.4074, 1.1099, 0.8468, 0.6085, 0.5045]
    values = [1.4623, 1.4937, 1.5987]

    if min(y) <= 0:
        k1 = abs(min(y)) + 1
    else:
        k1 = 0

    if min(x) <= 0:
        k2 = abs(min(x)) + 1
    else:
        k2 = 0

    yt = [yi + k1 for yi in y]

    y_ = (np.log(y))

    #xt = [xi + k2 for xi in x]

    x_ = np.divide(1,x)
 
    grau = 1

    a0, a1 =  best_poly(x_, y_, grau)

    print(f'{a0 }, {a1},')

    a = a0
    b = np.exp(a1)

    print(f'{a}, {b},')    #coeficientes a e b

    p = build_func(a, b)

    for xi_v in values:
        print(p(xi_v),",")
