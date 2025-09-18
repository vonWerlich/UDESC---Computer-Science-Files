def newton(f, df, x0, n):
    for _ in range(n):
        x0 -= f(x0) / df(x0)
        yield x0

def f(x):
    return  x * (x -1) * (x - 2) + 0.42

def df(x):
    return 3 * x**2 - 6*x +2

x0 = 2.44451776
n=200

resp = list(newton(f,df,x0,n))

iterations = [5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180,185,190,195,200]

for i in iterations:
    print (resp[i-1])