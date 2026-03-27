import os
import pandas as pd
import matplotlib.pyplot as plt

def coletar_tamanhos_pasta(diretorio):
    """
    Recebe o caminho de um diretório e retorna um DataFrame com nome de arquivo e tamanho em bytes.
    """
    dados = []
    if not os.path.isdir(diretorio):
        raise FileNotFoundError(f"Diretório não encontrado: {diretorio}")
    for nome in os.listdir(diretorio):
        caminho = os.path.join(diretorio, nome)
        if os.path.isfile(caminho):
            tamanho = os.path.getsize(caminho)
            dados.append({'arquivo': nome, 'tamanho_bytes': tamanho})
    return pd.DataFrame(dados)

# Ajuste este caminho para a pasta onde estão seus arquivos
directory = r"D:\Kauan\UDESC\2025_01 - 9º Semestre\Trabalho de Conclusão de Curso - I (TCC - I)\exp1\textos"

try:
    df = coletar_tamanhos_pasta(directory)
    df['tamanho_kb'] = df['tamanho_bytes'] / 1024
    df['tamanho_mb'] = df['tamanho_bytes'] / (1024 * 1024)

    # Mostra as primeiras linhas
    print(df.head())

    # Estatísticas descritivas
    estat = df['tamanho_kb'].describe().rename({
        'count': 'n_arquivos',
        'mean': 'media_kb',
        'std': 'desvio_padrao_kb',
        'min': 'min_kb',
        '25%': 'q1_kb',
        '50%': 'mediana_kb',
        '75%': 'q3_kb',
        'max': 'max_kb'
    })
    print("\nEstatísticas descritivas dos tamanhos em KB:")
    print(estat)

    # Histograma
    plt.figure(figsize=(8, 5))
    plt.hist(df['tamanho_kb'], bins=20, edgecolor='black')
    plt.title("Distribuição de tamanhos de arquivos (KB)")
    plt.xlabel("Tamanho (KB)")
    plt.ylabel("Número de arquivos")
    plt.grid(True, linestyle='--', alpha=0.5)
    plt.tight_layout()
    plt.show()

    # Boxplot
    plt.figure(figsize=(6, 3))
    plt.boxplot(df['tamanho_kb'], vert=False)
    plt.title("Boxplot dos tamanhos de arquivos (KB)")
    plt.xlabel("Tamanho (KB)")
    plt.tight_layout()
    plt.show()

except FileNotFoundError as e:
    print(e)
    print("Verifique se o caminho está correto e se a pasta realmente existe.")
