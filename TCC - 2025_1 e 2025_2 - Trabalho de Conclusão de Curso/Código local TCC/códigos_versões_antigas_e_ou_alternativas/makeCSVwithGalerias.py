import os
import re
import pandas as pd
from bs4 import BeautifulSoup
from urllib.parse import urlparse, urlunparse, quote

# --- CONFIGURAÇÕES ---
# Pastas de onde os dados serão lidos (devem existir)
entrada_dir = "htmls_Site_Inteiro"
galeria_dir = "htmls_galeria"

# Nome do arquivo CSV que será gerado
ARQUIVO_SAIDA = 'descricoes_galeria.csv'

print(f"Iniciando extração de descrições de galeria...")
print(f"Pasta de HTMLs principais: '{entrada_dir}'")
print(f"Pasta de HTMLs de galeria: '{galeria_dir}'")

# Lista para armazenar os resultados encontrados
dados_galeria = []

# === FUNÇÕES ADAPTADAS DO SEU SCRIPT 'scriptHTMLtoTXT4.0.py' ===

def limpar_texto(t):
    """Função para limpar o texto da descrição."""
    t = re.sub(r"\s+", " ", t)
    t = t.replace("▶", "").replace("●", "").replace("•", "•")
    t = re.sub(r"[▶●♦■→◀]+", "", t).strip()
    t = t.replace("fechar /\\", "")
    return t.strip()

def buscar_legenda_galeria(cd_estrutura, cd_elemento, cd_anexo, nr_anexo):
    """
    Procura o arquivo HTML da galeria e extrai a descrição da legenda.
    """
    nome_arquivo = f"{cd_estrutura}_{cd_elemento}_{cd_anexo}_{nr_anexo}.html"
    caminho = os.path.join(galeria_dir, nome_arquivo)
    
    if not os.path.exists(caminho):
        return None

    try:
        with open(caminho, "r", encoding="utf-8") as f:
            soup = BeautifulSoup(f, "html.parser")
        
        desc_div = soup.find("div", class_="galleria-info-description")
        if desc_div:
            return limpar_texto(desc_div.get_text())
    except Exception as e:
        print(f"  [AVISO] Erro ao ler o arquivo de galeria '{caminho}': {e}")
        return None
        
    return None

# === LÓGICA PRINCIPAL DE EXTRAÇÃO ===

# Verifica se as pastas de entrada existem
if not os.path.isdir(entrada_dir):
    print(f"\nERRO: A pasta de entrada '{entrada_dir}' não foi encontrada.")
elif not os.path.isdir(galeria_dir):
    print(f"\nERRO: A pasta de galerias '{galeria_dir}' não foi encontrada.")
else:
    # Loop principal: processa todos os HTMLs da pasta de entrada
    for nome_arquivo in sorted(os.listdir(entrada_dir)):
        if nome_arquivo.endswith(".html"):
            caminho_html = os.path.join(entrada_dir, nome_arquivo)
            print(f"Processando arquivo: {nome_arquivo}...")

            with open(caminho_html, "r", encoding="utf-8") as f:
                soup = BeautifulSoup(f, "html.parser")

            # Encontra todas as imagens que estão dentro de um link
            imagens_em_links = soup.find_all("img")

            for img in imagens_em_links:
                src = img.get("src", "")
                if not src:
                    continue

                # Normaliza a URL da imagem (mesma lógica do seu script)
                parsed = urlparse(src)
                path_encoded = quote(parsed.path)
                url_normalizada = urlunparse((parsed.scheme, parsed.netloc, path_encoded, parsed.params, parsed.query, parsed.fragment))

                # Procura o link pai (tag <a>) que abre a galeria
                a_tag = img.find_parent("a", href=True)
                if a_tag and "abrirGaleria" in a_tag["href"]:
                    # Extrai os IDs da função 'abrirGaleria' usando regex
                    match = re.search(r"abrirGaleria\([^)]*?(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)", a_tag["href"])
                    if match:
                        cd_anexo, cd_estrutura, cd_elemento, nr_anexo = match.groups()
                        
                        # Busca a legenda no arquivo HTML da galeria correspondente
                        legenda = buscar_legenda_galeria(cd_estrutura, cd_elemento, cd_anexo, nr_anexo)
                        
                        if legenda:
                            # Adiciona os dados encontrados à nossa lista
                            dados_galeria.append({
                                'url_original': url_normalizada,
                                'descricao_galeria': legenda
                            })
                            print(f"  -> Legenda encontrada para: {os.path.basename(url_normalizada)}")

    # --- FINALIZAÇÃO E GERAÇÃO DO CSV ---
    if dados_galeria:
        # Cria um DataFrame do Pandas com os dados
        df = pd.DataFrame(dados_galeria)
        
        # Remove duplicatas, caso a mesma imagem/legenda apareça em várias páginas
        df.drop_duplicates(inplace=True)
        
        # Salva o DataFrame em um arquivo CSV
        df.to_csv(ARQUIVO_SAIDA, index=False, encoding='utf-8-sig')
        
        print("\n--- PROCESSO CONCLUÍDO ---")
        print(f"Arquivo '{ARQUIVO_SAIDA}' foi gerado com sucesso!")
        print(f"Total de descrições únicas de galeria extraídas: {len(df)}")
    else:
        print("\n--- PROCESSO CONCLUÍDO ---")
        print("Nenhuma descrição de galeria foi encontrada nos arquivos processados.")