import os
from langchain_community.vectorstores import FAISS
from langchain_huggingface import HuggingFaceEmbeddings # <-- Importação moderna

# --- CONFIGURAÇÕES ---
# 1. Defina o nome da subpasta onde seu índice FAISS está localizado.
#    O script espera que esta subpasta esteja no mesmo diretório que ele.
CAMINHO_INDEX = "faiss_index_com_chunking_intfloatmultilingual-e5-large" # Substitua se o nome da sua pasta for diferente

# 2. Defina o modelo de embedding que foi usado para CRIAR o índice.
#    Use o modelo correto para o seu índice.
EMBEDDING_MODEL = "intfloat/multilingual-e5-large"
# ou o outro que você mencionou:
# EMBEDDING_MODEL = "sentence-transformers/all-mpnet-base-v2"

# --- INÍCIO DO SCRIPT ---

# Verifica se o caminho para o índice existe
if not os.path.exists(CAMINHO_INDEX):
    print(f"ERRO: O diretório do índice '{CAMINHO_INDEX}' não foi encontrado.")
else:
    try:
        # 1. Carrega o modelo de embedding usando a integração do LangChain
        print(f"[INFO] Carregando o modelo de embedding: '{EMBEDDING_MODEL}'...")
        embedder = HuggingFaceEmbeddings(
            model_name=EMBEDDING_MODEL,
            model_kwargs={'device': 'cpu'} # Mude para 'cuda' se tiver GPU
        )
        print("[OK] Modelo carregado.")

        # 2. Carrega o índice FAISS local usando o modelo
        print(f"[INFO] Carregando o índice FAISS de: '{CAMINHO_INDEX}'...")
        vectorstore = FAISS.load_local(
            CAMINHO_INDEX,
            embeddings=embedder,
            allow_dangerous_deserialization=True
        )
        print("[OK] Índice carregado com sucesso!")
        print(f"Dimensão dos vetores no índice: {vectorstore.index.d}")

        # 3. Realiza a busca por similaridade
        pergunta = "Como identificar a deficiência de cálcio no tomateiro?"
        print(f"\nBuscando por: '{pergunta}'...")
        resultados = vectorstore.similarity_search(pergunta, k=5) # Buscando 5 resultados

        # 4. Exibe os resultados
        print("\n--- Resultados Mais Relevantes ---")
        for i, doc in enumerate(resultados, 1):
            print(f"\n--- Documento {i} ---")
            # .get() é uma forma segura de acessar o dicionário, não dá erro se a chave não existir
            print(f"Arquivo de Origem: {doc.metadata.get('arquivo_origem', 'N/A')}")
            print(f"Título: {doc.metadata.get('titulo', 'N/A')}")
            print(f"Parte: {doc.metadata.get('parte', 'N/A')}")
            print(f"Conteúdo:\n{doc.page_content[:400]}{'...' if len(doc.page_content) > 400 else ''}")

    except Exception as e:
        print(f"\n❌ Ocorreu um erro: {e}")