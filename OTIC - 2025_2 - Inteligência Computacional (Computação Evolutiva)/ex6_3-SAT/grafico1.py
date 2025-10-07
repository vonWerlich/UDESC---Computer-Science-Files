import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

ARQUIVO_DETALHES = 'detalhes_config114.csv'
RUN_PARA_PLOTAR = 2

df = pd.read_csv(ARQUIVO_DETALHES)
df_run = df[df['Run'] == RUN_PARA_PLOTAR].copy()

# Calcula o melhor histórico (best-so-far)
df_run['BestSoFar'] = df_run['BestFitness'].cummax()

sns.set_theme(style="whitegrid", palette="plasma")
plt.figure(figsize=(12, 7))

# Linhas do gráfico
sns.lineplot(data=df_run, x='Generation', y='BestFitness', label='Melhor da Geração (valor real)', color='orange')
sns.lineplot(data=df_run, x='Generation', y='BestSoFar', label='Melhor Histórico (Best-So-Far)', color='purple')
sns.lineplot(data=df_run, x='Generation', y='AvgFitness', label='Fitness Médio da População', linestyle=':', color='gray')

plt.title(f'Curva de Convergência para 3-SAT (Run {RUN_PARA_PLOTAR})', fontsize=16)
plt.xlabel('Geração', fontsize=12)
plt.ylabel('Cláusulas Satisfeitas (Fitness)', fontsize=12)
plt.legend(loc='lower right')
plt.tight_layout()
plt.show()
