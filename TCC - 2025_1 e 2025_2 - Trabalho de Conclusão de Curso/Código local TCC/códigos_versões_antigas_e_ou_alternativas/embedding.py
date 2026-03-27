import glob
import json
import os
from langchain.schema import Document
from langchain.chains import RetrievalQA

from langchain_community.embeddings import HuggingFaceEmbeddings
from langchain_community.vectorstores import FAISS

import sys
import io
sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')

# === CONFIGURAÇÕES ===
PASTA_JSON = "jsons"       # Pasta com os arquivos .json
FAZER_TESTE_QA = True             # Roda uma pergunta teste ao final?

# === ETAPA 1: CARREGAR JSONs COMO DOCUMENTS ===
documents = []

for path in glob.glob(f"{PASTA_JSON}/*.json"):
    with open(path, encoding="utf-8") as f:
        data = json.load(f)

    # Inicializa o conteúdo principal do documento
    texto = ""

    # 1. Texto principal (parágrafos)
    texto += "\n\n".join(data.get("texto", []))

    # 2. Tabelas (strings simples)
    if data.get("tabelas"):
        texto += "\n\nTABELAS:\n" + "\n".join(data["tabelas"])

    # 3. Imagens (lista de objetos com 'src')
    if data.get("imagens"):
        imagens = [img["src"] for img in data["imagens"] if "src" in img]
        if imagens:
            texto += "\n\nIMAGENS:\n" + "\n".join(imagens)

    # 4. Metadados úteis
    metadata = {
        "cdEstrutura": data.get("cdEstrutura", ""),
        "url": data.get("url", ""),
        "titulo": data.get("titulo", ""),
        "arquivo_origem": os.path.basename(path)
    }

    documents.append(Document(page_content=texto, metadata=metadata))

print(f"[OK] Carregados {len(documents)} documentos.")

# === ETAPA 2: EMBEDDINGS COM HUGGINGFACE (LOCAL, GRATUITO) ===
#embedder = HuggingFaceEmbeddings(model_name="sentence-transformers/all-MiniLM-L6-v2")
embedder = HuggingFaceEmbeddings(model_name="sentence-transformers/all-mpnet-base-v2")

# === ETAPA 3: INDEXAR COM FAISS ===
vectorstore = FAISS.from_documents(documents, embedding=embedder)
vectorstore.save_local("faiss_index_banana")
print("[OK] Indexação completa. Arquivo salvo em 'faiss_index_banana/'.")

# === ETAPA 4 (OPCIONAL): TESTE DE CONSULTA COM EMBEDDINGS LOCAIS ===
if FAZER_TESTE_QA:
    #Como está usando apenas embeddings locais, precisa de um LLM para responder.
    #Sugestão: usar LangChain com LLM local (como Llama, Mistral, GPT4All) ou só o FAISS para busca.

    # Sugestão: apenas teste de busca sem geração
    docs = vectorstore.similarity_search("sigatoka", k=3)
    print("\n Trechos mais relevantes encontrados:")
    for i, d in enumerate(docs, 1):
        print(f"\n--- Documento {i} ---")
        print(f"Título: {d.metadata.get('titulo', '')}")
        print(f"Json: {d.metadata.get('cdEstrutura', '')}")
        print(d.page_content[:500] + ("..." if len(d.page_content) > 500 else ""))
