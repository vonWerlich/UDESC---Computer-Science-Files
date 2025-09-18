import math

def romberg(col1):
    col1 = [item for item in col1]
    n = len(col1)
    for j in range(n -1):
        temp_col = [0] * (n - 1 - j)
        for i in range(n - 1 - j):
            power = j + 1
            temp_col[i] = (4 ** power * col1[i+1] - col1[i]) / (4 ** power - 1)
        col1[:n -1 - j] = temp_col
        #print(f'F_{j+2}',temp_col)
    return col1[0]
    
def trapz(f, a, b, h):
    n = int((b - a) / h)
    soma = 0
    for k in range(1, n):
        soma += f(a + k * h)
    return (h/2) * (f(a) + 2 * soma + f(b))

def f(x):
    return -x * (x - 21) * (x + 1)

func = [f]
a = [0]
b = [12]
order = [8]


h = [1.2]

m = len(func)
for xi in range(m):
    #print(xi)
    hs = [h[xi] / 2 ** i for i in range(order[xi])]
    col1 = [trapz(func[xi],a[xi],b[xi],hi) for hi in hs]
    #print('F_1',col1)
    r = romberg(col1)
    print(f'{r}',",")