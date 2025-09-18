import math

def simps(f, a, b, n):
    if n % 2 != 0 or n < 1:
        raise ValueError("n deve ser par e maior q 1")
    h = (b - a) / n
    soma_odd, soma_even = 0, 0
    for k in range(1,n,2):
        soma_odd += f(a+k*h)
    for k in range(2,n,2):
        soma_even += f(a + k * h)
    return (h/3) * (f(a) + 4 * soma_odd + 2 * soma_even + f(b))

def f(x):
    return math.sqrt(math.sin(math.cos(math.log(x**2 + 1) + 2) + 3) + 4)
def simp(x0,x1,x3,y0,y1,y2):
    return ((x1-x0)/3)*(y0+4*y1+y2)

def simpsPonto(x, y):
    tam = (len(x) - 1) // 2
    somas = 0
    k = 0
    for i in range(tam):
        somas += simp(x[k],x[k+1],x[k+2],y[k],y[k+1],y[k+2])
        k += 2
    print(f'{somas}')


x = [0.258, 0.276, 0.294, 0.5015, 0.709, 0.7625, 0.816, 0.854, 0.892, 0.9215, 0.951, 1.0375, 1.124, 1.1265, 1.129, 1.142, 1.155, 1.3105, 1.466, 1.6775, 1.889, 1.8915, 1.894, 2.058, 2.222, 2.2765, 2.331, 2.38, 2.429, 2.6855, 2.942, 2.9755, 3.009, 3.167, 3.325, 3.426, 3.527, 4.0275, 4.528, 4.5565, 4.585, 4.6055, 4.626, 4.7585, 4.891]
y = [2.107, 2.169, 2.229, 2.781, 2.995, 2.999, 2.986, 2.967, 2.942, 2.918, 2.891, 2.799, 2.694, 2.691, 2.688, 2.671, 2.655, 2.458, 2.281, 2.104, 2.012, 2.012, 2.011, 2.003, 2.049, 2.076, 2.109, 2.144, 2.183, 2.453, 2.775, 2.814, 2.851, 2.978, 2.983, 2.895, 2.724, 1.176, 2.107, 2.25, 2.389, 2.484, 2.575, 2.97, 2.876]


intervalo = [-1.403, 1.03]
subintervalos = [6, 16, 48, 54, 76, 102, 138, 164, 178, 234, 372]

n = len(subintervalos)
for i in range(n):
    print(simps(f, intervalo[0], intervalo[1], subintervalos[i]),",")

#simpsPonto(x, y)