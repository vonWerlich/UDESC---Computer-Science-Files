import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os
import glob # Biblioteca para encontrar arquivos por padrão de nome

# --- CONFIGURAÇÕES ---
# Padrão de nome para os arquivos de entrada. O '*' é um coringa.
INPUT_FILE_PATTERN = 'resultados_*.csv'

# Nome do arquivo de imagem que será salvo
OUTPUT_IMAGE_FILE = 'boxplot_consolidado_SAT.png'
# --------------------

# --- LÓGICA DO SCRIPT ---

# Encontra todos os arquivos que correspondem ao padrão
file_list = glob.glob(INPUT_FILE_PATTERN)

if not file_list:
    print(f"ERRO: Nenhum arquivo correspondente ao padrão '{INPUT_FILE_PATTERN}' foi encontrado!")
    exit()

print(f"Arquivos encontrados: {file_list}")

# Lê e combina todos os arquivos CSV encontrados em um único DataFrame
all_data = []
for file in file_list:
    df_temp = pd.read_csv(file)
    # Adiciona uma coluna para identificar a origem dos dados
    df_temp['SourceFile'] = os.path.basename(file)
    all_data.append(df_temp)

df = pd.concat(all_data, ignore_index=True)

# --- PLOTAGEM DO GRÁFICO ---
sns.set_theme(style="whitegrid", palette="viridis")
plt.figure(figsize=(10, 8))

# Cria um boxplot para a coluna 'ClausesMet'
# O eixo X agora pode ser usado para separar por arquivo de configuração
sns.boxplot(x='SourceFile', y='ClausesMet', data=df)

# Pega o número total de cláusulas (solução ótima) do primeiro dado que encontrar
total_clauses = df['TotalClauses'].iloc[0]

# Adiciona uma linha horizontal vermelha para indicar a solução ótima
plt.axhline(y=total_clauses, color='r', linestyle='--', label=f'Solução Ótima ({total_clauses} cláusulas)')

# Títulos e Rótulos
plt.title('Distribuição dos Melhores Resultados por Configuração', fontsize=16, pad=20)
plt.ylabel('Cláusulas Satisfeitas ao Final da Execução', fontsize=12)
plt.xlabel('Arquivo de Configuração', fontsize=12)
plt.xticks(rotation=45, ha='right') # Rotaciona os nomes dos arquivos para não sobrepor
plt.legend()
plt.grid(True, which='both', linestyle='--', linewidth=0.5)

# Otimiza o layout
plt.tight_layout()

# Salva o gráfico
plt.savefig(OUTPUT_IMAGE_FILE, dpi=300)
print(f"\nGráfico salvo com sucesso como '{OUTPUT_IMAGE_FILE}'")

# Mostra o gráfico
plt.show()