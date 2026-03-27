import os
from collections import Counter

PASTA = "imagens_baixadas"  # pasta a verificar

extensoes = Counter()

for nome in os.listdir(PASTA):
    if os.path.isfile(os.path.join(PASTA, nome)):
        ext = os.path.splitext(nome)[1].lower()  # pega extensão em minúsculo
        extensoes[ext] += 1

print("Contagem por extensão:")
for ext, qtd in sorted(extensoes.items()):
    print(f"{ext or '[sem extensão]'}: {qtd}")

print(f"\nTotal de arquivos: {sum(extensoes.values())}")
