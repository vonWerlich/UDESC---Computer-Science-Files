import math
import numpy as np

def richardson(col_1):
    n = len(col_1) - 1
    for i in range(n - 1):
        for j in range(n - 1 - i):
            numer = 2 ** (i + 1) * col_1[j + 1] - col_1[j]
            denom = 2 ** (i + 1) - 1
            value = numer / denom
            col_1[j] = value
    return col_1[0]

if __name__ == '__main__':
    x0 = 1.65978
    approximations = [-0.5136360707125105, -0.5242555133974722, -0.5282564698489587, -0.529932617163972, -0.5306901183634665, -0.5310487986867543]
    
    new_value = richardson(approximations.copy())
    aprox = richardson(approximations + [new_value])
    print(aprox)