import matplotlib.pyplot as plt

# Função para ler e agrupar os dados
def ler_e_organizar(caminho_arquivo, grupo_tamanho):
    with open(caminho_arquivo, "r") as f:
        valores = [float(linha.strip()) for linha in f.readlines()]
    # Divide os dados em grupos de tamanho "grupo_tamanho"
    return [valores[i:i + grupo_tamanho] for i in range(0, len(valores), grupo_tamanho)]

# Parâmetros
arquivo = "saida_boxplot_2.txt"      # nome do arquivo com todos os dados
grupo_tamanho = 30                   # número de execuções por grupo

# Lê e organiza os dados
dados = ler_e_organizar(arquivo, grupo_tamanho)

def imprimir_valores(valores):
    for valor in valores:
        print(f"{valor:.6f}")  # Imprime com 6 casas decimais

# Cria o boxplot
fig, ax = plt.subplots()
box = ax.boxplot(dados,
                 patch_artist=True,
                 showmeans=False,
                 showcaps=True,
                 showfliers=False,
                 widths=0.6)

# Cores para os grupos (expande se precisar de mais)
cores = ['orange', 'skyblue', 'lightgreen', 'lightcoral', 'gold']
for patch, cor in zip(box['boxes'], cores):
    patch.set_facecolor(cor)

# Personalização
ax.set_xticklabels([f"Alg. {i}" for i in range(len(dados))])
ax.set_ylabel("Resultado Final do Algoritmo")
ax.set_title("Esquemas de Resfriamento - 100 cidades")

plt.tight_layout()
plt.savefig("comparacao_boxplot.png", dpi=300, bbox_inches='tight')
#a = dados[9]
#imprimir_valores(a)
plt.show()
