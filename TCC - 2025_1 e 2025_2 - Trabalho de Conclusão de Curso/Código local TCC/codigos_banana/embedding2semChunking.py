import glob
import json
import os
from langchain.schema import Document
from langchain.chains import RetrievalQA

from langchain_community.embeddings import HuggingFaceEmbeddings
from langchain_community.vectorstores import FAISS

from tqdm import tqdm  # para mostrar barra de progresso


import sys
import io
sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')


PASTA_TXT = "textos_comdescricao"  # Pasta com os arquivos

documents = []

for path in glob.glob(f"{PASTA_TXT}/*.txt"):
    with open(path, "r", encoding="utf-8") as f:
        texto = f.read()

    # Inicializa valores padrão
    titulo = ""
    url = ""

    # Tenta extrair 'Título' e 'URL' das duas primeiras linhas
    linhas = texto.splitlines()
    for linha in linhas[:5]:  # pega as 5 primeiras por segurança
        if linha.startswith("Título:"):
            titulo = linha.replace("Título:", "").strip()
        elif linha.startswith("URL:"):
            url = linha.replace("URL:", "").strip()
    
    nome_arquivo = os.path.basename(path)
    cd_estrutura = os.path.splitext(nome_arquivo)[0]  # tira o ".txt"

    metadata = {
        "titulo": titulo,
        "url": url,
        "cdEstrutura": cd_estrutura,
        "arquivo_origem": nome_arquivo
    }

    documents.append(Document(page_content=texto, metadata=metadata))

print(f"[OK] Carregados {len(documents)} arquivos .txt.")


# === ETAPA 2: EMBEDDINGS COM HUGGINGFACE (LOCAL, GRATUITO) ===
#embedder = HuggingFaceEmbeddings(model_name="sentence-transformers/all-MiniLM-L6-v2")
#intfloat/multilingual-e5-base #1024
#intfloat/multilingual-e5-large #1024
#sentence-transformers/paraphrase-multilingual-mpnet-base-v2 #multilingue, 768
#sentence-transformers/all-mpnet-base-v2

embedder = HuggingFaceEmbeddings(model_name="sentence-transformers/all-mpnet-base-v2")


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

print("[INFO] Salvando o índice no disco...")
vectorstore.save_local("faiss_index")
print("[OK] Indexação completa. Arquivo salvo em 'faiss_index/'.")

# === ETAPA 4 (OPCIONAL): TESTE DE CONSULTA COM EMBEDDINGS LOCAIS ===

#Como está usando apenas embeddings locais, precisa de um LLM para responder.
#Sugestão: usar LangChain com LLM local (como Llama, Mistral, GPT4All) ou só o FAISS para busca.

# Sugestão: apenas teste de busca sem geração
docs = vectorstore.similarity_search("moko da bananeira", k=10)
print("\n Trechos mais relevantes encontrados:") 
for i, d in enumerate(docs, 1):
    print(f"\n--- Documento {i} ---")
    print(f"Título: {d.metadata.get('titulo', '')}")
    print(f"Json: {d.metadata.get('cdEstrutura', '')}")
    print(d.page_content[:500] + ("..." if len(d.page_content) > 500 else ""))
