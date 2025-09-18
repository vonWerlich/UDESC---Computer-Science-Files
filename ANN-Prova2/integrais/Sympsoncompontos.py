import math
import numpy as np

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
    return math.sqrt(1 + math.cos(x)**2)

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

x = [0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90]	
y = [0,106,234,359,508,666,824,970,1093,1212,1321,1465,1630,1819,2048,2308,2602,2897,3198]
if min(y) <= 0:
    k1 = abs(min(y)) + 1
else:
    k1 = 0

if min(x) <= 0:
    k2 = abs(min(x)) + 1
else:
    k2 = 0

yt = [yi + k1 for yi in y]

y_ = np.divide(y,3.6)

intervalo = [0,90]
subintervalos = [64]

'''
n = len(subintervalos)
for i in range(n):
    print(simps(f, intervalo[0], intervalo[1], subintervalos[i]))
'''

simpsPonto(x, y_)