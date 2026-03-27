import os
import requests
import csv
from urllib.parse import urlparse
from tqdm import tqdm

# --- CONFIGURAÇÕES ---
arquivo_links = "links_de_imagens.txt"  # Recomendo usar a lista filtrada
pasta_saida = "imagens_baixadas"
arquivo_csv = "mapeamento_imagens.csv"

os.makedirs(pasta_saida, exist_ok=True)

# --- LÓGICA PARA CONTINUAR O DOWNLOAD SE O SCRIPT PARAR ---
urls_ja_processadas = set()
ultimo_id = 0
try:
    with open(arquivo_csv, 'r', newline='', encoding='utf-8') as f_csv:
        reader = csv.reader(f_csv)
        header = next(reader)  # Pula o cabeçalho
        for row in reader:
            ultimo_id = int(row[0])
            urls_ja_processadas.add(row[2])
    print(f"Encontrado arquivo de mapeamento. Continuando a partir do ID {ultimo_id + 1}.")
    print(f"{len(urls_ja_processadas)} URLs já foram processadas.")
except FileNotFoundError:
    # Se o arquivo não existe, cria um novo e escreve o cabeçalho
    with open(arquivo_csv, 'w', newline='', encoding='utf-8') as f_csv:
        writer = csv.writer(f_csv)
        writer.writerow(['id', 'novo_nome', 'url_original'])
    print("Arquivo de mapeamento não encontrado. Criando um novo: mapeamento_imagens.csv")


# --- SCRIPT PRINCIPAL ---
s = requests.Session()
contador = ultimo_id

# Abre o arquivo CSV no modo 'append' (para adicionar novas linhas sem apagar as antigas)
with open(arquivo_csv, 'a', newline='', encoding='utf-8') as f_csv, \
     open(arquivo_links, "r", encoding="utf-8") as f_links:
    
    writer = csv.writer(f_csv)
    urls_para_baixar = f_links.readlines()

    for url in tqdm(urls_para_baixar, desc="Baixando Imagens"):
        url = url.strip()
        if not url or url in urls_ja_processadas:
            continue

        try:
            # Extrai a extensão original da URL, com .jpg como padrão
            ext = os.path.splitext(urlparse(url).path)[-1].lower() or ".jpg"
            if not ext.startswith("."):
                 ext = ".jpg" # Garante que a extensão seja válida

            contador += 1
            nome_arquivo = f"{contador}{ext}"
            caminho_arquivo = os.path.join(pasta_saida, nome_arquivo)
            
            # ATENÇÃO: timeout=None pode fazer o script travar indefinidamente
            r = s.get(url, timeout=1)
            r.raise_for_status()

            with open(caminho_arquivo, "wb") as f_img:
                f_img.write(r.content)

            # Escreve a linha no CSV após o sucesso do download
            writer.writerow([contador, nome_arquivo, url])

        except Exception as e:
            print(f"[ERRO] Falha ao baixar {url}: {e}")

print(f"\nProcesso finalizado. O mapeamento está salvo em '{arquivo_csv}'.")