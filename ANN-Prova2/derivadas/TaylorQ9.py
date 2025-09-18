import numpy as np
import math

# x0 = ponto onde a função será derivada
# x = lista de coordenadas na proximidade de x0
# y = cálculo da função em todos os pontos x
# k = ordem da derivada

def coeffs_dif_fin(x0, x, k):
    n = len(x)
    A, B = [[1]* n], [0]
    for i in range(1, n):
        # construção da matriz A
        row_i = [xi ** i for xi in x]
        A.append(row_i)
        # construção da matriz B
        if i < k:
            B.append(0)
        elif i == k:
            B.append(math.factorial(k))
        else:
            numer = math.factorial(i)
            denom = math.factorial(i - k)
            el = (numer / denom) * x0 ** (i - k)
            B.append(el)
    return np.linalg.solve(A, B)
        
def dif_fin(coeffs, y):
    return sum(ci * yi for ci, yi in zip(coeffs, y))
        

if __name__ == '__main__':
    # exemplo 1:
    def f(x):
        return math.log(2 + math.cos(math.exp(-x)))
    def p(xp):
        x0 = 0.7305

        x = [0.5073, 0.5728, 0.6389, 0.6933, 0.7864, 0.8052, 0.9118, 0.9368]


        k = 4  #ordem
        n = 8 # numero de pontos igualmente espaçados
        # queremos pontos no intervalo [x0-e, x0+e]
        # ao diminuir o epsilon (e) os pontos são cada vez mais próximos
        e = 0.000001
        
        y = [f(xi) for xi in x]
        
        coeffs = coeffs_dif_fin(x0, x, 1)
        f_1 = dif_fin(coeffs, y)
        
        coeffs = coeffs_dif_fin(x0, x, 2)
        f_2 = dif_fin(coeffs, y)
        
        coeffs = coeffs_dif_fin(x0, x, 3)
        f_3 = dif_fin(coeffs, y)
        return f(x0) + f_1*(xp - x0) + (f_2/2)*((xp - x0)**2) + (f_3/6)*((xp - x0)**3) 
    
    
    values = [0.5077, 0.537, 0.5794, 0.631]
    px = [p(vi) for vi in values]  #px
    print(f'{px}')

    fx_menos_px = [np.abs(f(vi) - p(vi)) for vi in values]   #fx - px
    print(f'{fx_menos_px}')