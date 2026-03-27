import os
import glob
from langchain.schema import Document

# Pasta com arquivos de texto
PASTA_TXT = "textos"

# Configuração de chunking
TAMANHO_CHUNK = 1000   # caracteres
SOBREPOSICAO = 100     # caracteres
LIMITE_PARA_DIVIDIR = 2000  # se arquivo <= 2 KB, não divide

def dividir_texto(texto, tamanho_chunk, sobreposicao):
    """
    Divide o texto em pedaços com sobreposição.
    Retorna lista de strings.
    """
    chunks = []
    inicio = 0
    while inicio < len(texto):
        fim = inicio + tamanho_chunk
        chunks.append(texto[inicio:fim])
        inicio += tamanho_chunk - sobreposicao
    return chunks

documents = []

for path in glob.glob(f"{PASTA_TXT}/*.txt"):
    with open(path, "r", encoding="utf-8") as f:
        texto = f.read()

    nome_arquivo = os.path.basename(path)
    cd_estrutura = os.path.splitext(nome_arquivo)[0]

    # Decide se divide ou não
    if len(texto) <= LIMITE_PARA_DIVIDIR:
        documents.append(Document(
            page_content=texto,
            metadata={
                "arquivo_origem": nome_arquivo,
                "cdEstrutura": cd_estrutura,
                "parte": 1
            }
        ))
    else:
        partes = dividir_texto(texto, TAMANHO_CHUNK, SOBREPOSICAO)
        for i, chunk in enumerate(partes, start=1):
            documents.append(Document(
                page_content=chunk,
                metadata={
                    "arquivo_origem": nome_arquivo,
                    "cdEstrutura": cd_estrutura,
                    "parte": i
                }
            ))

print(f"[OK] Gerados {len(documents)} chunks a partir de {len(glob.glob(f'{PASTA_TXT}/*.txt'))} arquivos.")
