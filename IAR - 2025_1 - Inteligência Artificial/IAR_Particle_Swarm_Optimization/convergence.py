import csv
import matplotlib.pyplot as plt

iters, current_vals, global_vals = [], [], []

with open('convergence.csv', newline='') as csvfile:
    reader = csv.DictReader(csvfile)
    for row in reader:
        iters.append(int(row['iter']))
        current_vals.append(float(row['current_best']))
        global_vals.append(float(row['gbest_value']))

plt.plot(iters, current_vals, label='Melhor da iteração')
plt.plot(iters, global_vals, label='Melhor global acumulado')
plt.xlabel('Iteração')
plt.ylabel('Valor da função')
plt.title('Curva de Convergência Griewank com 10 dimensões')
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.savefig("convergence.png")
plt.show()
