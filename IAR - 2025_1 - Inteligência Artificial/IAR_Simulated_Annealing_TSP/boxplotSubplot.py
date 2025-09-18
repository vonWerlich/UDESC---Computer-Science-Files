import matplotlib.pyplot as plt

# Função auxiliar para ler valores de um .txt
def ler_valores(caminho_arquivo):
    with open(caminho_arquivo, "r") as f:
        return [float(linha.strip()) for linha in f.readlines()]

# Lê os dados de cada configuração
valores1 = ler_valores("saida_boxplot_1.txt")
valores2 = ler_valores("saida_boxplot_2.txt")

# Cria subplots lado a lado
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(10, 5))

# Boxplot para 51 cidades
box1 = ax1.boxplot([valores1],
                   patch_artist=True,
                   showmeans=False,
                   showcaps=True,
                   showfliers=False,
                   widths=0.6)
box1['boxes'][0].set_facecolor('orange')
ax1.set_title("51 cidades, i=51000")
ax1.set_ylabel("Resultado Final do Algoritmo")
ax1.set_ylim(min(valores1) - 10, max(valores1) + 10)
ax1.set_xticklabels([])  # Remove os números no eixo X

# Boxplot para 100 cidades
box2 = ax2.boxplot([valores2],
                   patch_artist=True,
                   showmeans=False,
                   showcaps=True,
                   showfliers=False,
                   widths=0.6)
box2['boxes'][0].set_facecolor('skyblue')
ax2.set_title("100 cidades, i=100000")
ax2.set_ylim(min(valores2) - 500, max(valores2) + 500)
ax2.set_xticklabels([])  # Remove os números no eixo X

# Ajustes finais
plt.suptitle("Resultado após Configuração Inicial", fontsize=14)
plt.tight_layout(rect=[0, 0.03, 1, 0.95])
plt.savefig("comparacao_boxplot_subplot.png", dpi=300, bbox_inches='tight')
plt.show()
