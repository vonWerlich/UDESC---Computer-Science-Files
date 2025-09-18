import os
import numpy as np
import pandas as pd

# Lista de arquivos com os valores finais
arquivos = [
    "valores_config1.txt",
    "valores_config2.txt",
    "valores_config3.txt"
    # Adicione mais aqui se tiver
]

# Lista para armazenar os resultados
resultados = []

# Para cada arquivo, calcular média e desvio padrão
for idx, arq in enumerate(arquivos, start=1):
    with open(arq, "r") as f:
        valores = [float(l.strip()) for l in f.readlines()]
        media = np.mean(valores)
        desvio = np.std(valores, ddof=1)  # amostral
        resultados.append({
            "Configuração": f"Config {idx}",
            "Média": media,
            "Desvio Padrão": desvio
        })

# Criar um DataFrame para exibir como tabela
df_resultados = pd.DataFrame(resultados)

# Exibir a tabela
print(df_resultados)

# Salvar como CSV ou LaTeX se quiser
df_resultados.to_csv("tabela_resultados.csv", index=False)
# df_resultados.to_latex("tabela_resultados.tex", index=False)  # se quiser usar no LaTeX
