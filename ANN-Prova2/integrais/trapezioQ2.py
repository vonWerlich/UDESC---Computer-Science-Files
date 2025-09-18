import numpy as np

def trapz(f, a, b, n):
    h = (b - a) / n
    soma = 0
    for k in range(1, n):
        soma += f(a + k * h)
    soma *= 2
    soma += f(a)
    soma += f(b)
    soma *= (h/2.0)
    print(f'Area aproximadamente: {soma}')

def f(x):
    """return math.sqrt(math.sin(math.cos(math.log(x**2 + 1) + 2) + 3) + 4)"""
    return np.sqrt(9.81*74.12/0.38)*np.tanh(9.81*0.38*x/74.12)

def trapzPonto(x, y):
    tam = len(x) - 1
    somas = 0
    for i in range(tam):
        h = x[i+1] - x[i]
        somas += (h/2) * (y[i] + y[i+1])
    print(f'Area = {somas}')
"""x = [0.0,5.0,10.0,15.0,20.0,25.0,30.0,35.0,40.0,45.0,50.0,55.0,60.0]
y = [197.79,272.64,153.78,166.75,294.85,121.77,220.84,232.44,138.13,180.91,250.52,109.71,265.79]"""
"""x = [0.0,0.75,1.5,2.25,3.0,3.75,4.5,5.25,6.0,6.75,7.5,8.25,9.0,9.75,10.5,11.25,12.0]
y = [9.65,9.55,9.12,8.4,8.12,7.75,7.25,6.91,6.62,6.19,5.72,5.3,4.8,4.52,3.96,3.46,3.25]"""

	
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
    trapz(f, intervalo[0], intervalo[1], subintervalos[i])
'''

trapzPonto(x, y_)