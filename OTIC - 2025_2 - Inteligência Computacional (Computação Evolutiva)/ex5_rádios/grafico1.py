import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# --- CONFIGURAÇÕES ---
# Coloque aqui o nome do seu arquivo CSV com os detalhes das gerações
# Esta é a linha que foi corrigida:
ARQUIVO_DETALHES = 'detalhes_config1.csv'

# Escolha qual execução (run) você quer visualizar no gráfico
RUN_PARA_PLOTAR = 1

# --- LEITURA E PREPARAÇÃO DOS DADOS ---
try:
    # Lê o arquivo CSV para um DataFrame do pandas
    df_details = pd.read_csv(ARQUIVO_DETALHES)
except FileNotFoundError:
    print(f"Erro: Arquivo '{ARQUIVO_DETALHES}' não encontrado. Verifique o nome e o caminho do arquivo.")
    exit()

# Filtra os dados para mostrar apenas a execução escolhida
df_run = df_details[df_details['Run'] == RUN_PARA_PLOTAR]

if df_run.empty:
    print(f"Erro: A execução (Run) {RUN_PARA_PLOTAR} não foi encontrada no arquivo CSV.")
    exit()

# --- PLOTAGEM DO GRÁFICO ---
# Define um tema mais agradável para os gráficos
sns.set_theme(style="whitegrid")

# Cria a figura e o eixo principal
fig, ax1 = plt.subplots(figsize=(12, 7))

# Título do Gráfico
ax1.set_title(f'Curva de Convergência e Evolução do Lucro', fontsize=16)

# Plota Melhor Fitness e Fitness Médio no eixo Y principal (ax1)
sns.lineplot(data=df_run, x='Generation', y='BestFitness', label='Melhor Fitness da Geração', ax=ax1, color='b')
sns.lineplot(data=df_run, x='Generation', y='AvgFitness', label='Fitness Médio da População', ax=ax1, color='c', linestyle=':')
ax1.set_xlabel('Geração', fontsize=12)
ax1.set_ylabel('Fitness (Normalizado)', fontsize=12, color='b')
ax1.tick_params(axis='y', labelcolor='b')
ax1.legend(loc='upper left')

# Cria um segundo eixo Y que compartilha o mesmo eixo X
ax2 = ax1.twinx()

# Plota o Lucro Real no eixo Y secundário (ax2)
sns.lineplot(data=df_run, x='Generation', y='Best_Profit', label='Lucro Real (R$)', ax=ax2, color='g', linestyle='--')
ax2.set_ylabel('Lucro (R$)', fontsize=12, color='g')
ax2.tick_params(axis='y', labelcolor='g')
ax2.legend(loc='lower right')

# Otimiza o layout para evitar sobreposição de elementos
fig.tight_layout()

# Salva o gráfico em um arquivo de imagem
nome_arquivo_saida = f'convergencia_run_{RUN_PARA_PLOTAR}.png'
plt.savefig(nome_arquivo_saida, dpi=300)
print(f"Gráfico salvo como '{nome_arquivo_saida}'")

# Mostra o gráfico na tela
plt.show()