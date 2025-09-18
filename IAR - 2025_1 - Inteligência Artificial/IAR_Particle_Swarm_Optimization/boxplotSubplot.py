

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# Função para ler valores e dividir em grupos de 30
def ler_e_organizar(caminho_arquivo, grupo_tamanho=30):
    with open(caminho_arquivo, "r") as f:
        valores = [float(linha.strip()) for linha in f if linha.strip()]
    return [valores[i:i + grupo_tamanho] for i in range(0, len(valores), grupo_tamanho)]

# Arquivos e metadados
arquivos = ["boxplot_1.txt", "boxplot_2.txt", "boxplot_3.txt", "boxplot_4.txt"]
funcoes = ["Ackley", "Ackley", "Griewank", "Griewank"]
dimensoes = [5, 10, 5, 10]
variantes = ["STANDARD", "INERTIA", "CONSTRICTION"]

# Lista para armazenar os resultados
tabela = []

# Processamento
for idx, arquivo in enumerate(arquivos):
    grupos = ler_e_organizar(arquivo)
    
    for v_idx, grupo in enumerate(grupos):
        if len(grupo) == 0:
            continue  # Pula se o grupo estiver vazio
        
        media = np.mean(grupo)
        desvio = np.std(grupo, ddof=1)
        
        descricao = f"{funcoes[idx]} | {dimensoes[idx]}D | {variantes[v_idx]}"
        
        tabela.append([
            descricao,
            f"{media:.10f}",
            f"{desvio:.10f}"
        ])

# Criar DataFrame
df = pd.DataFrame(tabela, columns=["Configuração", "Média", "Desvio Padrão"])

# Plotar a tabela
fig, ax = plt.subplots(figsize=(12, len(df) * 0.5 + 1))  # altura dinâmica
ax.axis('off')  # remove os eixos

# Criar tabela no gráfico
tabela_plot = ax.table(
    cellText=df.values,
    colLabels=df.columns,
    loc='center',
    cellLoc='center',
    colColours=['lightgray'] * len(df.columns)
)

# Ajuste de fonte e escala
tabela_plot.auto_set_font_size(False)
tabela_plot.set_fontsize(10)
tabela_plot.scale(1, 1.5)  # largura, altura

# Título opcional
plt.title("Resultados por Configuração", fontsize=14, pad=20)

# Salvar e mostrar
plt.savefig("tabela_configuracoes.png", dpi=300, bbox_inches='tight')
plt.show()
