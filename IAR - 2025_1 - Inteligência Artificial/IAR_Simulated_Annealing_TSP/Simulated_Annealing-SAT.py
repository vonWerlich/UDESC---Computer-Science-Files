import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os

print('Gerando o gráfico...')

if not os.path.exists("saida.csv"):
    print("Erro: O arquivo 'saida.csv' não foi encontrado.")
    exit()

# Carregar o CSV
df = pd.read_csv("saida.csv", names=["Iteracao", "Temperatura", "ValorAtual", "MelhorGlobal"])

# Máscara: só onde MelhorGlobal está abaixo de ValorAtual
mask = df["MelhorGlobal"] <= df["ValorAtual"]

# Versão visível de MelhorGlobal: esconde onde não for menor que ValorAtual
melhor_global_visivel = np.where(mask, df["MelhorGlobal"], np.nan)

# Criar gráfico
fig, ax1 = plt.subplots()

# Plot da temperatura (eixo 1)
ax1.set_xlabel("Iteração")
ax1.set_ylabel("Temperatura", color="tab:blue")
ax1.plot(df["Iteracao"], df["Temperatura"], label="Temperatura", color="tab:blue", linestyle="dashed")
ax1.tick_params(axis="y", labelcolor="tab:blue")

# Eixo 2: soluções
ax2 = ax1.twinx()
ax2.set_ylabel("Valor da Solução", color="tab:red")



# MelhorGlobal visível só onde é menor que o valor atual
ax2.plot(df["Iteracao"], melhor_global_visivel, label="Melhor Global", color="tab:green")

# Valor atual sempre visível
ax2.plot(df["Iteracao"], df["ValorAtual"], label="Valor Atual", color="tab:red")

# Construir vetores em degrau para Iteracao e melhor_global_visivel
x_step = []
y_step = []

for i in range(len(df) - 1):
    # Pula intervalos onde algum dos dois pontos do intervalo não atende a condição
    if not (mask.iloc[i] and mask.iloc[i + 1]):
        continue
    x_step.append(df["Iteracao"].iloc[i])
    x_step.append(df["Iteracao"].iloc[i + 1])
    y_step.append(df["MelhorGlobal"].iloc[i])
    y_step.append(df["MelhorGlobal"].iloc[i])

# Preencher apenas se houver algo válido
if x_step:
    ax2.fill_between(x_step, y_step, 0, color="lightgreen", alpha=0.3, label="Área Melhor Global")

ax2.tick_params(axis="y", labelcolor="tab:red")

# Título e legenda
fig.legend(loc="upper right")
plt.title("Gráfico de Convergência da Solução no SA", loc='left')

# Salvar e mostrar
plt.tight_layout()
plt.savefig("evolucao_sa.png", dpi=300, bbox_inches='tight')
plt.show()

print('Concluído!')
