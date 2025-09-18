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
    return a * 2 ** (b * x) #funçao

def build_func(a, b):
    def temp(x):
        return poly(x, a, b)
    return temp

if __name__ == '__main__':
    x = [0.026, 0.057, 0.1632, 0.2045, 0.2633, 0.3176, 0.3738, 0.4076, 0.496, 0.5088, 0.5865, 0.6143, 0.6736, 0.7587, 0.7986, 0.8711, 0.905, 0.969, 1.0336, 1.1051, 1.1147, 1.2152, 1.2355, 1.3178, 1.3424, 1.3926, 1.468, 1.5546, 1.5995, 1.6647, 1.7222, 1.7715, 1.804, 1.8381, 1.9374, 1.9521]
    y = [3.597, 4.5326, 4.832, 5.954, 5.9935, 7.8651, 6.6878, 7.3944, 7.715, 8.1786, 8.4312, 8.5587, 9.6556, 11.7251, 10.9014, 10.267, 12.9912, 13.1654, 14.6324, 13.0798, 15.7667, 16.3125, 18.2501, 18.7475, 21.258, 18.8821, 25.0174, 23.0616, 27.444, 30.7127, 31.0742, 32.5444, 34.7983, 35.4936, 38.6363, 41.0375]
    values = [0.6764, 0.8735, 0.8905, 1.0873, 1.8114]
    y_ = np.log(y)
 
    grau = 1

    a0, a1 =  best_poly(x, y_, grau)

    print(f'{a0 }, {a1},')

    a = np.exp(a0)
    b = a1/np.log(2)

    print(f'{a}, {b},')    #coeficientes a e b

    p = build_func(a, b)

    for xi_v in values:
        print(p(xi_v),",")
