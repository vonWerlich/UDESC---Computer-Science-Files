import os
import re

PASTA_TXT = "textos"
links_de_imagens = set()

# Expressão regular para capturar URLs de imagens (continua a mesma)
regex_img = re.compile(
    r'https?://[^\s"\']+\.(?:png|jpg|jpeg|jfif|gif|webp|bmp|tiff?|avif|heic|heif)', #retirei .svg
    re.IGNORECASE
)

# --- NOVO: Lista de padrões de URL que queremos manter ---
PADROES_PERMITIDOS = [
    "/img_elemento/",
    "/img_estrutura/",
    "/arq_anexos/"
]

# Percorrer todos os arquivos .txt da pasta
for arquivo in os.listdir(PASTA_TXT):
    if arquivo.lower().endswith(".txt"):
        caminho = os.path.join(PASTA_TXT, arquivo)
        with open(caminho, "r", encoding="utf-8") as f:
            conteudo = f.read()
            encontrados = regex_img.findall(conteudo)
            
            # --- LÓGICA DE FILTRAGEM ADICIONADA AQUI ---
            for link in encontrados:
                # Verifica se algum dos padrões permitidos está no link
                if any(padrao in link for padrao in PADROES_PERMITIDOS):
                    links_de_imagens.add(link)

# Salvar os links filtrados em um arquivo
with open("links_de_imagens.txt", "w", encoding="utf-8") as f_out:
    for link in sorted(links_de_imagens):
        f_out.write(link + "\n")

print(f"{len(links_de_imagens)} links de imagens FILTRADOS foram extraídos e salvos em 'links_de_imagens.txt'.")