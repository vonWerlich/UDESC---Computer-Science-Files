import os

# Caminho da subpasta onde estão os .txt (dentro da pasta onde o script está)
SUBPASTA = "textos"  # substitua pelo nome da sua subpasta

# String que será buscada
BUSCA = "cavendish"

# Caminho absoluto da subpasta
caminho_absoluto = os.path.join(os.getcwd(), SUBPASTA)

# Verifica se a pasta existe
if not os.path.isdir(caminho_absoluto):
    print(f"Subpasta '{SUBPASTA}' não encontrada.")
    exit()

# Percorre todos os arquivos da subpasta
for nome_arquivo in os.listdir(caminho_absoluto):
    if nome_arquivo.endswith(".txt"):
        caminho_arquivo = os.path.join(caminho_absoluto, nome_arquivo)

        # Abre o arquivo e verifica a presença da string
        with open(caminho_arquivo, "r", encoding="utf-8") as f:
            conteudo = f.read()
            if BUSCA.lower() in conteudo.lower():
                print(f"Encontrado em: {nome_arquivo}")
            #else:
                #print(f"[ ] Não encontrado em: {nome_arquivo}")
