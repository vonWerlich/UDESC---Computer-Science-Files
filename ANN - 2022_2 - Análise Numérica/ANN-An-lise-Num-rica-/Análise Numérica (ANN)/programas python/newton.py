import math
import numpy

def newton(f, df, x0, n):
    for _ in range(n):
        x0 -= f(x0) / df(x0)
        yield x0

def f(x):
    return  math.sqrt(2*9.81*x)*numpy.tanh((math.sqrt(2*9.81*x)*9.28)/(2*9.62)) - 10.67

def df(x):
    return 2,21472345903501*numpy.tanh(2,136448409547286*math.sqrt(x))/math.sqrt(x) + 4,731642411642411*(numpy.sech(2,136448409547286*math.sqrt(x)))**2

x0 = 1.6
n=20

resp = list(newton(f,df,x0,n))

iterations = [1,3,5]

for i in iterations:
    print (resp[i-1])