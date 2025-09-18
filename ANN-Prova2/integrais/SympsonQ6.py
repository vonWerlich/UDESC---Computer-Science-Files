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

x = [0.028, 0.1705, 0.313, 0.4845, 0.656, 0.7355, 0.815, 0.986, 1.157, 1.1725, 1.188, 1.251, 1.314, 1.421, 1.528, 1.5345, 1.541, 1.625, 1.709, 1.7935, 1.878, 1.923, 1.968, 1.9945, 2.021, 2.065, 2.109, 2.2605, 2.412, 2.524, 2.636, 2.7725, 2.909, 3.1145, 3.32, 3.417, 3.514, 3.531, 3.548, 3.661, 3.774, 4.0205, 4.267, 4.46, 4.653]
y = [1.32, 1.796, 2.291, 2.748, 2.972, 3.0, 2.986, 2.856, 2.652, 2.632, 2.613, 2.532, 2.453, 2.329, 2.221, 2.215, 2.209, 2.14, 2.085, 2.043, 2.015, 2.006, 2.001, 2.0, 2.0, 2.004, 2.012, 2.068, 2.169, 2.271, 2.394, 2.562, 2.735, 2.946, 2.985, 2.906, 2.751, 2.716, 2.678, 2.373, 1.995, 1.192, 1.09, 1.77, 2.685]

intervalo = [0.028,4.653]
subintervalos = [4, 18, 32, 60, 98, 108, 132, 152, 194, 212, 278]

'''
n = len(subintervalos)
for i in range(n):
    print(simps(f, intervalo[0], intervalo[1], subintervalos[i]))
'''

simpsPonto(x, y)