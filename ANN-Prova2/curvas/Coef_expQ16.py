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
    return (a * x) / (x + b) #funçao

def build_func(a, b):
    def temp(x):
        return poly(x, a, b)
    return temp

if __name__ == '__main__':

    x = [1.2805, 1.8187, 2.0796, 2.5307, 3.2032, 3.5372, 4.1256, 4.318, 4.6925, 5.2991, 5.7635, 6.0969, 6.5491, 7.1056, 7.4471, 7.9719, 8.3636, 9.1153, 9.516, 9.9466, 10.2493, 10.5325, 11.2545, 11.4406, 11.8799, 12.6679, 13.0189, 13.5258, 13.9758, 14.2287, 14.8728, 15.1529, 15.5653, 15.9344, 16.6743, 16.952, 17.7262, 18.0542, 18.4289, 18.9368, 19.2105, 19.8337]
    y = [0.6615, 0.7923, 0.8877, 0.9373, 1.0126, 1.1652, 1.2232, 1.2424, 1.2646, 1.3203, 1.4001, 1.433, 1.4327, 1.4727, 1.5058, 1.4815, 1.5185, 1.5537, 1.5528, 1.5856, 1.6003, 1.6222, 1.6098, 1.6265, 1.5516, 1.6577, 1.6918, 1.6988, 1.7261, 1.685, 1.6909, 1.7359, 1.7146, 1.7249, 1.7358, 1.7143, 1.7458, 1.7419, 1.713, 1.7556, 1.7814, 1.7544]
    values = [3.2848, 6.9445, 6.9482, 9.9446, 12.3075]

    if min(y) <= 0:
        k1 = abs(min(y)) + 1
    else:
        k1 = 0

    if min(x) <= 0:
        k2 = abs(min(x)) + 1
    else:
        k2 = 0

    yt = [yi + k1 for yi in y]

    y_ = (np.divide(1,y))

    xt = [xi + k2 for xi in x]

    x_ = np.divide(1,x)
 
    grau = 1

    a0, a1 =  best_poly(x_, y_, grau)

    print(f'{a0 }, {a1},')

    a = 1 / a0
    b = a1 * a 

    print(f'{a}, {b},')    #coeficientes a e b

    p = build_func(a, b)

    for xi_v in values:
        print(p(xi_v),",")
