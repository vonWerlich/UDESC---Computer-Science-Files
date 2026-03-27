import os

# Caminho da pasta 'textos' no mesmo diretório do script
pasta = os.path.join(os.path.dirname(__file__), 'textos')

# Inicializa contadores
total_caracteres = 0
quantidade_arquivos = 0

# Verifica se a pasta existe
if not os.path.isdir(pasta):
    print(f"Pasta 'textos' não encontrada no mesmo diretório do script.")
else:
    print("Arquivos .txt encontrados em 'textos':\n")
    
    # Varre todos os arquivos da pasta
    for nome_arquivo in os.listdir(pasta):
        if nome_arquivo.endswith('.txt'):
            caminho_arquivo = os.path.join(pasta, nome_arquivo)
            try:
                with open(caminho_arquivo, 'r', encoding='utf-8') as f:
                    conteudo = f.read()
                    num_caracteres = len(conteudo)
                    print(f"{nome_arquivo}: {num_caracteres} caracteres")
                    total_caracteres += num_caracteres
                    quantidade_arquivos += 1
            except Exception as e:
                print(f"Erro ao ler {nome_arquivo}: {e}")

    # Estatísticas
    if quantidade_arquivos > 0:
        media = total_caracteres / quantidade_arquivos
        print(f"\nTotal de arquivos: {quantidade_arquivos}")
        print(f"Total de caracteres: {total_caracteres}")
        print(f"Média de caracteres por arquivo: {media:.2f}")
    else:
        print("Nenhum arquivo .txt encontrado dentro da pasta 'textos'.")
