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
    return a * x ** (b) #funçao

def build_func(a, b):
    def temp(x):
        return poly(x, a, b)
    return temp

if __name__ == '__main__':

    x = [0.5197, 0.56, 0.6622, 0.7031, 0.7513, 0.8565, 0.8775, 0.9173, 1.0255, 1.0931, 1.1363, 1.1725, 1.2628, 1.3227, 1.3742, 1.4335, 1.4708, 1.5534, 1.6142, 1.675, 1.739, 1.7957, 1.8201, 1.8724, 1.953, 1.9985, 2.1054, 2.123, 2.1689, 2.2729, 2.3317, 2.4018, 2.4392, 2.5193, 2.5397, 2.6368, 2.692, 2.727, 2.7909, 2.8554, 2.8912, 2.9884]
    y = [1.0289, 1.3928, 0.6368, 0.6115, 1.2069, 1.8006, 3.051, 1.094, 1.8707, 2.9427, 3.2661, 3.7248, 4.2833, 4.9607, 5.7108, 5.9294, 7.066, 7.9105, 9.6473, 10.8383, 11.2657, 13.6167, 13.8517, 15.1595, 17.078, 18.5396, 20.7125, 21.4927, 23.3684, 27.3873, 29.1725, 31.8897, 33.9482, 37.3734, 38.3463, 42.7113, 46.4127, 48.2871, 51.8999, 55.4744, 57.2243, 64.516]
    values = [1.4577, 1.918, 1.9244, 1.9339, 2.5592]

    x_ = np.log(x)
    y_ = np.log(y)
 
    grau = 1

    a0, a1 =  best_poly(x_, y_, grau)

    print(f'{a0 }, {a1},')

    a = np.exp(a0)
    b = a1

    print(f'{a}, {b},')    #coeficientes a e b

    p = build_func(a, b)

    for xi_v in values:
        print(p(xi_v),",")
