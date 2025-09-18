import math

def falseposition(f, a, b,  n):
    for i in range(n):
        fa = f(a)
        fb = f(b)
        if (fa * fb >= 0):
            print("O teorema de Bolzano não sabe dixer se existe raiz para f nesse intervalo")
            break

        else:
            x1 = (a * fb - b * fa) / (fb - fa)

            print(x1)

            fx1 = f(x1)
            if (fa * fx1 < 0):
                b = x1
                fb = fx1
            else:
                a = x1
                fa = fx1

def f(x):
    return (9.81 * x / 20.44) * (1 - math.exp(-(20.44 / x) * 8.42)) - 30.48

a = 36.05
b = 193.19
n = 20

falseposition(f, a, b, n);
