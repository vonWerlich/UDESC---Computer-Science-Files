import numpy as np
import matplotlib.pyplot as plt

def ler_valores(arquivo):
    with open(arquivo, 'r') as f:
        return [float(linha.strip()) for linha in f if linha.strip()]

def calcular_estatisticas(arquivos, nomes_personalizados):
    resultados = []
    for arquivo, nome_custom in zip(arquivos, nomes_personalizados):
        valores = ler_valores(arquivo)
        media = np.mean(valores)
        desvio = np.std(valores)
        resultados.append((nome_custom, f"{media:.2f}", f"{desvio:.2f}"))
    return resultados

def gerar_imagem_tabela(resultados, nome_arquivo_saida='tabela_estatisticas.png'):
    col_labels = ["Nome", "Média", "Desvio Padrão"]
    cell_text = resultados

    fig, ax = plt.subplots(figsize=(6, len(resultados) * 0.6 + 1))
    ax.axis('off')
    tabela = ax.table(cellText=cell_text, colLabels=col_labels, loc='center', cellLoc='center')
    tabela.auto_set_font_size(False)
    tabela.set_fontsize(12)
    tabela.scale(1, 1.5)

    plt.tight_layout()
    plt.savefig(nome_arquivo_saida, dpi=300)
    plt.close()
    print(f"Tabela salva como: {nome_arquivo_saida}")

if __name__ == "__main__":
    arquivos = ["saida_boxplot_1.txt", "saida_boxplot_2.txt"]
    nomes_personalizados = ["51 Cidades", "100 Cidades"]
    resultados = calcular_estatisticas(arquivos, nomes_personalizados)
    gerar_imagem_tabela(resultados)




