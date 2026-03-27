import os
import base64
import requests

from urllib.parse import urlparse
from pathlib import Path

arquivo_links = "links_de_imagens.txt"
pasta_saida = "imagens_baixadas"

os.makedirs(pasta_saida, exist_ok=True)

def url_para_nome(url):
    # Codifica a URL para base64 segura para nomes de arquivos
    url_bytes = url.encode("utf-8")
    base64_bytes = base64.urlsafe_b64encode(url_bytes)
    base64_str = base64_bytes.decode("ascii")
    # Pega extensão do arquivo
    ext = os.path.splitext(urlparse(url).path)[-1].lower() or ".jpg"
    return f"{base64_str}{ext}"

with open(arquivo_links, "r", encoding="utf-8") as f:
    for i, url in enumerate(f):
        url = url.strip()
        if not url:
            continue

        nome_arquivo = url_para_nome(url)
        caminho_arquivo = os.path.join(pasta_saida, nome_arquivo)

        if os.path.exists(caminho_arquivo):
            print(f"[{i}] Já existe: {nome_arquivo}")
            continue

        try:
            r = requests.get(url, timeout=None) # None = espera até dar certo else espera or X segundos antes de seguir em frente
            r.raise_for_status()

            with open(caminho_arquivo, "wb") as f_img:
                f_img.write(r.content)

            print(f"[{i}] Salvo: {nome_arquivo}")

        except Exception as e:
            print(f"[{i}] Erro ao baixar {url}: {e}")
