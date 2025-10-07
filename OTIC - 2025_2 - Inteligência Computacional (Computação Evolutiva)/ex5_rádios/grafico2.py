import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os

# --- Configurações ---
# Nome do arquivo de entrada com os resultados consolidados por execução
INPUT_CSV_FILE = 'resultados_config1.csv'

# Nome do arquivo de imagem que será salvo
OUTPUT_IMAGE_FILE = 'boxplot_geral_runs.png'

# --- Lógica do Script ---

# Verifica se o arquivo de entrada existe no mesmo diretório do script
if not os.path.exists(INPUT_CSV_FILE):
    print(f"ERRO: Arquivo '{INPUT_CSV_FILE}' não encontrado!")
    print("Certifique-se de que o script está na mesma pasta que o arquivo CSV.")
else:
    print(f"Lendo o arquivo de dados: '{INPUT_CSV_FILE}'...")
    
    # Carrega os dados usando pandas
    df = pd.read_csv(INPUT_CSV_FILE)

    # Define o estilo do gráfico (opcional, mas deixa mais bonito)
    sns.set_theme(style="whitegrid", palette="viridis")

    # Cria a figura que conterá o gráfico
    plt.figure(figsize=(8, 7))

    # --- Criação do Boxplot ---
    # Cria um boxplot para a coluna 'BestFitness'.
    # Como não estamos separando por categorias no eixo X, todos os
    # valores de 'BestFitness' serão usados para criar um único boxplot,
    # que é exatamente o que queremos para ver a distribuição geral.
    sns.boxplot(y=df['BestFitness'])

    # Adiciona um título e rótulos aos eixos para maior clareza
    #plt.title('Distribuição do Melhor Fitness Entre 20 Execuções', fontsize=16, pad=20)
    plt.ylabel('Melhor Fitness', fontsize=12)
    plt.xlabel('Conjunto de Todas as Execuções (Runs)', fontsize=12)

    # Salva o gráfico em um arquivo de imagem
    plt.savefig(OUTPUT_IMAGE_FILE, dpi=300, bbox_inches='tight')

    print(f"\nGráfico salvo com sucesso como '{OUTPUT_IMAGE_FILE}'")

    # Mostra o gráfico em uma janela pop-up ao executar o script
    plt.show()