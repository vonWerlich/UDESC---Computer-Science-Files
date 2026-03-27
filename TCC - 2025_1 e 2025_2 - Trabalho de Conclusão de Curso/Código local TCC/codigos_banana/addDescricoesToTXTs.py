import os
import csv
import re
import sys
import io

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')

# === CONFIGURAÇÕES ===
PASTA_TXTS = "textos"          # pasta com os .txt originais
PASTA_SAIDA = "textos_comdescricao"      # pasta para salvar os .txt modificados
CSV_CONVERSAO = "TabelaConversao.csv"    # CSV com mapeamento URL -> img_X
CSV_DESCRICOES = "Planilha_Analise.csv"  # CSV com mapeamento img_X -> descrição

os.makedirs(PASTA_SAIDA, exist_ok=True)

# === 1. Ler CSV de conversão URL -> img_X ===
url_para_img = {}
with open(CSV_CONVERSAO, newline="", encoding="utf-8") as f:
    reader = csv.DictReader(f)
    for row in reader:
        url_original = row.get("url_original", "").strip()
        img_nome = row.get("cognome", "").strip()
        if url_original and img_nome:
            url_para_img[url_original] = img_nome

# === 2. Ler CSV de descrições img_X -> descrição ===
img_para_desc = {}
with open(CSV_DESCRICOES, newline="", encoding="utf-8") as f:
    reader = csv.reader(f)
    for row in reader:
        if len(row) >= 4:
            img_nome = row[0].strip()
            descricao = row[3].strip()
            if img_nome and descricao:
                img_para_desc[img_nome] = descricao

# === 3. Processar os .txt originais ===
total_arquivos = 0
total_descricoes = 0

for nome_arquivo in os.listdir(PASTA_TXTS):
    if not nome_arquivo.lower().endswith(".txt"):
        continue

    total_arquivos += 1
    caminho_txt = os.path.join(PASTA_TXTS, nome_arquivo)
    with open(caminho_txt, "r", encoding="utf-8") as f:
        conteudo = f.read()

    # URLs encontradas no texto
    urls_encontradas = re.findall(r'https?://\S+', conteudo)
    alterado = False

    for url in urls_encontradas:
        if url in url_para_img:
            img_nome = url_para_img[url]
            if img_nome in img_para_desc:
                descricao = img_para_desc[img_nome]
                conteudo = conteudo.replace(url, f"{url}\n{descricao}")
                print(f"[{nome_arquivo}] Adicionada descrição para {img_nome}: \"{descricao}\"")
                total_descricoes += 1
                alterado = True

    # Salvar apenas se houve mudança
    caminho_saida = os.path.join(PASTA_SAIDA, nome_arquivo)
    with open(caminho_saida, "w", encoding="utf-8") as f_out:
        f_out.write(conteudo)

print(f"\nProcesso concluído!")
print(f"Total de arquivos processados: {total_arquivos}")
print(f"Total de descrições inseridas: {total_descricoes}")
print(f"Textos modificados salvos em: {PASTA_SAIDA}")
