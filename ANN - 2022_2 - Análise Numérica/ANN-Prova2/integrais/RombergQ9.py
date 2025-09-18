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

def f_1(x):
    return math.sqrt(1+x**2) 

def f_2(x):
    return math.exp(-x**2)

def f_3(x):
    return math.cos((-x**2)/3)

def f_4(x):
    return (x+(1/x))**2

def f_5(x):
    return math.exp(x)*math.sin(x)/(1+x**2)

func = [f_1, f_2, f_3, f_4, f_5]
a = [0.98, 0.83, 0.35, -0.97, 0.43]
b = [1.98, 1.83, 1.35, 0.03, 1.43]
order = [6, 4, 6, 10, 6]


h = [0.2, 0.125, 0.125, 0.1, 0.2]

m = len(func)
for xi in range(m):
    #print(xi)
    hs = [h[xi] / 2 ** i for i in range(order[xi])]
    col1 = [trapz(func[xi],a[xi],b[xi],hi) for hi in hs]
    #print('F_1',col1)
    r = romberg(col1)
    print(f'{r}',",")