import glob
import json
import os
from langchain.schema import Document
from langchain.chains import RetrievalQA
from langchain_community.embeddings import HuggingFaceEmbeddings
from langchain_community.vectorstores import FAISS
import sys
import io
from tqdm import tqdm  # para mostrar barra de progresso
import tiktoken

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')

# === CONFIGURAÇÕES ===
PASTA_TXT = "textos_comdescricao"  # Pasta com os arquivos
TAMANHO_CHUNK = 1000  # caracteres por chunk
SOBREPOSICAO = 100    # caracteres que repetem entre chunks
LIMITE_PARA_DIVIDIR = 2000  # até 2 KB não divide

# === FUNÇÃO DE CHUNKING ===

import tiktoken

def dividir_texto(texto, max_tokens=500, sobreposicao_tokens=80, modelo="cl100k_base"):
    """
    Divide o texto em chunks de até `max_tokens`, com `sobreposicao_tokens`.
    Mantém frases e contexto, evitando cortes no meio de palavras.
    """
    enc = tiktoken.get_encoding(modelo)
    tokens = enc.encode(texto)
    chunks = []
    start = 0
    while start < len(tokens):
        end = min(start + max_tokens, len(tokens))
        chunk = enc.decode(tokens[start:end])
        chunks.append(chunk)
        start += max_tokens - sobreposicao_tokens
    return chunks



# === ETAPA 1: LEITURA E CHUNKING ===
documents = []
arquivos_txt = glob.glob(f"{PASTA_TXT}/*.txt")
print(f"[INFO] Encontrados {len(arquivos_txt)} arquivos para processar.\n")

for idx, path in enumerate(arquivos_txt, start=1):
    with open(path, "r", encoding="utf-8") as f:
        texto = f.read()

    # Inicializa valores padrão
    titulo = ""
    url = ""

    # Extrai título e URL das primeiras linhas (se existirem)
    linhas = texto.splitlines()
    for linha in linhas[:5]:
        if linha.startswith("Título:"):
            titulo = linha.replace("Título:", "").strip()
        elif linha.startswith("URL:"):
            url = linha.replace("URL:", "").strip()

    nome_arquivo = os.path.basename(path)
    cd_estrutura = os.path.splitext(nome_arquivo)[0]

    if len(texto) <= LIMITE_PARA_DIVIDIR:
        # Arquivo pequeno → vai inteiro
        documents.append(Document(
            page_content=texto,
            metadata={
                "titulo": titulo,
                "url": url,
                "cdEstrutura": cd_estrutura,
                "arquivo_origem": nome_arquivo,
                "parte": 1
            }
        ))
        print(f"[{idx}/{len(arquivos_txt)}] '{nome_arquivo}' (1 chunk único)")
    else:
        # Arquivo grande → divide em pedaços
        partes = chunks = dividir_texto(texto, max_tokens=500, sobreposicao_tokens=80)
        for i, chunk in enumerate(partes, start=1):
            documents.append(Document(
                page_content=chunk,
                metadata={
                    "titulo": titulo,
                    "url": url,
                    "cdEstrutura": cd_estrutura,
                    "arquivo_origem": nome_arquivo,
                    "parte": i
                }
            ))
        print(f"[{idx}/{len(arquivos_txt)}] '{nome_arquivo}' dividido em {len(partes)} chunks")

print(f"\n[OK] Total de {len(documents)} chunks prontos para embedding.\n")

# === ETAPA 2: EMBEDDINGS COM HUGGINGFACE ===
print("[INFO] Carregando modelo de embeddings...")

# === ETAPA 2: EMBEDDINGS COM HUGGINGFACE (LOCAL, GRATUITO) ===
#embedder = HuggingFaceEmbeddings(model_name="sentence-transformers/all-MiniLM-L6-v2")
#intfloat/multilingual-e5-base #1024
#intfloat/multilingual-e5-large #1024
#sentence-transformers/paraphrase-multilingual-mpnet-base-v2 #multilingue, 768
#sentence-transformers/all-mpnet-base-v2 #funcionou, 768, dizem que é melhor em ingles
embedder = HuggingFaceEmbeddings(model_name="intfloat/multilingual-e5-large")

# ===  feedback ===
embeddings_list = []
documents_list = []

for doc in tqdm(documents, desc="Gerando embeddings"):
    emb = embedder.embed_documents([doc.page_content])[0]  # gera embedding
    embeddings_list.append(emb)
    documents_list.append(doc)


# === ETAPA 3: INDEXAR COM FAISS ===
print("[INFO] Construindo o índice FAISS a partir dos embeddings...")
# Extrai os textos e metadados separadamente
texts = [doc.page_content for doc in documents_list]
metadatas = [doc.metadata for doc in documents_list]

# Cria o índice FAISS usando os embeddings já calculados
vectorstore = FAISS.from_embeddings(
    zip(texts, embeddings_list),  # lista de tuplas (texto, vetor)
    embedding=embedder,
    metadatas=metadatas
)

#vectorstore = FAISS.from_documents(documents, embedding=embedder) #os embeddings não foram gerados antes
print("[INFO] Salvando o índice no disco...")
vectorstore.save_local("faiss_index")
print("[OK] Indexação completa. Arquivo salvo em 'faiss_index_banana/'.")

# === ETAPA 4: TESTE DE CONSULTA ===
print("\n[INFO] Teste de busca com a palavra 'sigatoka'...")
docs = vectorstore.similarity_search("moko da bananeira", k=5)
for i, d in enumerate(docs, 1):
    print(f"\n--- Resultado {i} ---")
    print(f"Título: {d.metadata.get('titulo', '')}")
    print(f"URL: {d.metadata.get('url', '')}")
    print(f"Arquivo: {d.metadata.get('arquivo_origem', '')} | Parte: {d.metadata.get('parte', '')}")
    print(d.page_content[:300] + ("..." if len(d.page_content) > 300 else ""))
