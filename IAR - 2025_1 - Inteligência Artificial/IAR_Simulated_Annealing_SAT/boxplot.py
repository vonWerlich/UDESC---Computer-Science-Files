import matplotlib.pyplot as plt

# Função auxiliar para ler valores de um .txt
def ler_valores(caminho_arquivo):
    with open(caminho_arquivo, "r") as f:
        return [float(linha.strip()) for linha in f.readlines()]

# Lê os dados de cada configuração
valores1 = ler_valores("saida_boxplot_1.txt")
valores2 = ler_valores("saida_boxplot_2.txt")
valores3 = ler_valores("saida_boxplot_3.txt")

# Junta as listas em uma lista de listas
dados = [valores1, valores2, valores3]

# Cria o boxplot comparando as configurações
fig, ax = plt.subplots()
box = ax.boxplot(dados,
                 patch_artist=True,
                 showmeans=False,
                 showcaps=True,
                 showfliers=False,
                 widths=0.6)

# Cores para distinguir
cores = ['orange', 'skyblue']
for patch, cor in zip(box['boxes'], cores):
    patch.set_facecolor(cor)

# Personalização dos eixos
ax.set_xticklabels(["20 cláusulas, i=160", "100 cláusulas, i=800", "250 cláusulas, i=2000"])
ax.set_ylabel("Resultado Final do Algoritmo")
ax.set_title("Valor Final após i iterações")

plt.tight_layout()
plt.savefig("comparacao_boxplot.png", dpi=300, bbox_inches='tight')
plt.show()
