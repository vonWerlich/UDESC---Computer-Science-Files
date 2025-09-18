import csv
import matplotlib.pyplot as plt

iters, current_vals, global_vals = [], [], []

# Lê os dados
with open('convergence.csv', newline='') as csvfile:
    reader = csv.DictReader(csvfile)
    for row in reader:
        iters.append(int(row['iter']))
        current_vals.append(float(row['current_best']))
        global_vals.append(float(row['gbest_value']))

plt.yscale('log')
plt.ylim(bottom=1e-10)

# Substitui valores ≤ 0 por um epsilon pequeno
eps = 1e-10  # ou outro valor pequeno suficiente
current_vals = [max(v, eps) for v in current_vals]
global_vals = [max(v, eps) for v in global_vals]

# Plota com escala logarítmica
plt.plot(iters, current_vals, label='Melhor da iteração')
plt.plot(iters, global_vals, label='Melhor global acumulado')
plt.xlabel('Iteração')
plt.ylabel('Valor da função')
plt.title('Gráfico de Convergência para 60 dimensões Griewank - Constriction')
plt.grid(True)
plt.yscale('log')
plt.legend()
plt.tight_layout()
plt.savefig("convergence_log.png", dpi=300)
plt.show()
