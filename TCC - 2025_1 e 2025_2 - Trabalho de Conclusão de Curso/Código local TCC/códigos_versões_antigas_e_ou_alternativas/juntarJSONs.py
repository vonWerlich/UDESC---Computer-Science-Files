import os
import json

pasta_jsons = "jsons"
saida_arquivo = "todos_os_dados.json"

todos = []

# Percorre todos os arquivos .json da pasta
for nome_arquivo in sorted(os.listdir(pasta_jsons)):
    if nome_arquivo.endswith(".json"):
        caminho = os.path.join(pasta_jsons, nome_arquivo)
        with open(caminho, "r", encoding="utf-8") as f:
            dados = json.load(f)
            todos.append(dados)

# Salva tudo num único arquivo
with open(saida_arquivo, "w", encoding="utf-8") as fout:
    json.dump(todos, fout, ensure_ascii=False, indent=2)

print(f"Arquivo combinado salvo como {saida_arquivo}")
