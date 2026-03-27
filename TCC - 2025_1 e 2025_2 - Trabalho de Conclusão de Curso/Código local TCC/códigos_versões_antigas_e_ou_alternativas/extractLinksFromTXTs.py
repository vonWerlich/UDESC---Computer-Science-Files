import os
import re

PASTA_TXT = "textos"  # pasta onde estão os .txt
links_de_imagens = set()  # usar set para evitar duplicados

# Expressão regular para capturar URLs de imagens
regex_img = re.compile(
    r'https?://[^\s"\']+\.(?:png|jpg|jpeg|jfif|gif|webp|bmp|tiff?|avif|heic|heif)', 
    re.IGNORECASE
)


# Percorrer todos os arquivos .txt da pasta
for arquivo in os.listdir(PASTA_TXT):
    if arquivo.lower().endswith(".txt"):
        caminho = os.path.join(PASTA_TXT, arquivo)
        with open(caminho, "r", encoding="utf-8") as f:
            conteudo = f.read()
            # Procurar todas as ocorrências
            encontrados = regex_img.findall(conteudo)
            links_de_imagens.update(encontrados)

# Salvar os links encontrados em um arquivo
with open("links_de_imagens.txt", "w", encoding="utf-8") as f_out:
    for link in sorted(links_de_imagens):
        f_out.write(link + "\n")

print(f"{len(links_de_imagens)} links de imagens foram extraídos e salvos em 'links_de_imagens.txt'.")
