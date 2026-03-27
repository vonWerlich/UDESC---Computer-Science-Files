import json

# Abrir e carregar o conteúdo do arquivo JSON
with open("todos_os_dados.json", "r", encoding="utf-8") as f:
    dados = json.load(f)

# Lista para armazenar os links
links_de_imagens = []

# Percorrer os dados do JSON
for item in dados:
    if "conteudo" in item:
        for elemento in item["conteudo"]:
            if elemento.get("tipo") == "imagem" and "src" in elemento:
                links_de_imagens.append(elemento["src"])

# Salvar os links em um arquivo de saída
with open("links_de_imagens.txt", "w", encoding="utf-8") as f_out:
    for link in links_de_imagens:
        f_out.write(link + "\n")

print(f"{len(links_de_imagens)} links de imagens foram extraídos e salvos em 'links_de_imagens.txt'.")
