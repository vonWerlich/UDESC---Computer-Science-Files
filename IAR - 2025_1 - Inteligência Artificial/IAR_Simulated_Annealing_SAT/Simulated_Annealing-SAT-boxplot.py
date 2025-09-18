import matplotlib.pyplot as plt

# Função auxiliar para ler valores de um .txt
def ler_valores(caminho_arquivo):
    with open(caminho_arquivo, "r") as f:
        return [float(linha.strip()) for linha in f.readlines()]

# Lê os dados de cada configuração
valores_config1 = ler_valores("saida_boxplot.txt")
#valores_config2 = ler_valores("valores_config2.txt")

# Junta as listas em uma lista de listas
dados = [valores_config1]

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
ax.set_xticklabels(["Configuração 1"])
ax.set_ylabel("Valor Final da Função Objetivo")
ax.set_title("Comparação de configurações do Simulated Annealing")

plt.tight_layout()
plt.savefig("comparacao_boxplot.png", dpi=300, bbox_inches='tight')
plt.show()
