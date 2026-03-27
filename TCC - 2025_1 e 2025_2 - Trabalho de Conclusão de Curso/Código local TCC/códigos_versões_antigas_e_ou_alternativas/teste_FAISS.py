from langchain_community.vectorstores import FAISS
from langchain_community.embeddings import HuggingFaceEmbeddings

# === CONFIGURAÇÕES ===
CAMINHO_INDEX = "faiss_index_sem_chunking-mpnet-base-v2"
# EMBEDDING_MODEL = "sentence-transformers/all-MiniLM-L6-v2"  # Altere para outro modelo se necessário
EMBEDDING_MODEL = "sentence-transformers/all-mpnet-base-v2"

# === CARREGAR INDEX EXISTENTE ===
print(f"[INFO] Carregando índice FAISS de: {CAMINHO_INDEX}")
embedder = HuggingFaceEmbeddings(model_name=EMBEDDING_MODEL)
vectorstore = FAISS.load_local(CAMINHO_INDEX, embeddings=embedder, allow_dangerous_deserialization=True)
print("[OK] Índice carregado com sucesso!")

# === LOOP DE TESTES INTERATIVOS ===

#sigatoka
#moko da bananeira
#cavendish

resultados = vectorstore.similarity_search("doenças banana", k=10)
print("\n Resultados mais relevantes:")
print("Dimensão do vetor:", vectorstore.index.d)

for i, doc in enumerate(resultados, 1):
    print(f"\n--- Documento {i} ---")
    print(f"Título: {doc.metadata.get('titulo', '')}")
    print(f"Arquivo: {doc.metadata.get('arquivo_origem', '')}")
    print(f"Conteúdo:\n{doc.page_content[:500]}{'...' if len(doc.page_content) > 500 else ''}")
