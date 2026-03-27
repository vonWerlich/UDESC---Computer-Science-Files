import os
import csv
import base64
from pathlib import Path
import re

# ===== CONFIGURAÇÕES =====
PASTA_IMAGENS = "imagens_baixadas"  # pasta com as imagens originais
ARQUIVO_SAIDA = "TabelaConversao.csv"      # arquivo CSV de saída

def natural_sort_key(s):
    """Quebra a string em blocos de texto e números para ordenação natural."""
    return [int(text) if text.isdigit() else text.lower() for text in re.split(r'(\d+)', s)]

# Lista e ordena arquivos com ordenação natural
arquivos = sorted(
    [f for f in os.listdir(PASTA_IMAGENS) if os.path.isfile(os.path.join(PASTA_IMAGENS, f))],
    key=natural_sort_key
)

# Criar CSV
with open(ARQUIVO_SAIDA, "w", encoding="utf-8", newline="") as f:
    writer = csv.writer(f)
    writer.writerow(["cognome", "nome_original", "url_original"])  # cabeçalho

    for i, nome in enumerate(arquivos, start=1):
        cognome = f"img_{i}"
        nome_sem_extensao = Path(nome).stem

        try:
            # Decodifica base64 para URL original
            url_original = base64.urlsafe_b64decode(nome_sem_extensao).decode("utf-8")
        except Exception as e:
            url_original = f"[ERRO ao decodificar: {e}]"

        writer.writerow([cognome, nome, url_original])

print(f"Arquivo de conversão criado: {ARQUIVO_SAIDA}")
print(f"{len(arquivos)} imagens processadas.")
