import os
import re
import csv
import time
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from collections import defaultdict

# --- CONFIGURAÇÕES GERAIS ---

# 1. Configurações para a Navegação (apenas para mapeamento)
URL_INICIAL = "https://sistemas.epagri.sc.gov.br/sedimob/consulta.action?subFuncao=epagriTec"
BASE_URL_ESTRUTURA = "https://sistemas.epagri.sc.gov.br/sedimob/consulta.action?subFuncao=consultaDiagnostico&cdEstrutura={}&isEdicao=N&epagriTEC=S"

# 2. Configurações para arquivos locais
PASTA_TXT = "textos"
PASTA_SAIDA_CSV = "relatorios_csv" # Pasta onde os CSVs serão salvos

# --- ETAPA 1: MAPEAMENTO DA ESTRUTURA VIA NAVEGAÇÃO ONLINE ---
# Nenhuma alteração necessária nesta seção.

def configurar_driver():
    """Configura e retorna uma instância do driver do Selenium."""
    print("Configurando o navegador (Selenium) para o mapeamento...")
    options = Options()
    options.add_argument("--headless")
    options.add_argument("--disable-gpu")
    options.add_argument("--window-size=1920x1080")
    prefs = {
        "profile.managed_default_content_settings.images": 2,
        "profile.managed_default_content_settings.stylesheets": 2,
        "profile.managed_default_content_settings.fonts": 2,
    }
    options.add_experimental_option("prefs", prefs)
    return webdriver.Chrome(options=options)

def _explorar_recursivamente_online(driver, cd_estrutura, mapa_documentos, id_inicial_atual, visitados):
    """Função recursiva que navega para descobrir a hierarquia de sub-itens."""
    if cd_estrutura in visitados:
        return
    visitados.add(cd_estrutura)

    url = BASE_URL_ESTRUTURA.format(cd_estrutura)
    driver.get(url)
    
    try:
        WebDriverWait(driver, 10).until(EC.presence_of_element_located((By.TAG_NAME, "body")))
    except Exception as e:
        print(f"  [Aviso] Timeout ao carregar a página para o ID {cd_estrutura}. Pulando. Erro: {e}")
        return

    try:
        dados_tabela = driver.execute_script("return typeof dadosTabela !== 'undefined' ? dadosTabela : null")
    except Exception as e:
        print(f"  - Erro ao obter dadosTabela para o ID {cd_estrutura}: {e}")
        dados_tabela = None

    if dados_tabela:
        for item in dados_tabela:
            codigo_html = item.get("codigo", "").strip()
            if not codigo_html:
                continue
            
            nome_documento = re.sub(r'<.*?>', '', codigo_html).strip()
            id_documento = ''.join(filter(str.isdigit, codigo_html))

            if id_documento and nome_documento:
                documento_info = {"id": id_documento, "nome": nome_documento}
                mapa_documentos[id_inicial_atual]['documentos'].append(documento_info)
                _explorar_recursivamente_online(driver, id_documento, mapa_documentos, id_inicial_atual, visitados)

def mapear_estrutura_online():
    print("--- INICIANDO ETAPA 1: Mapeamento da estrutura do site (Online) ---")
    driver = configurar_driver()
    
    print(f"Acessando página inicial: {URL_INICIAL}")
    driver.get(URL_INICIAL)
    WebDriverWait(driver, 10).until(EC.presence_of_all_elements_located((By.XPATH, "//a[contains(@href, 'javascript:abreItem(')]")))
    elementos = driver.find_elements(By.XPATH, "//a[contains(@href, 'javascript:abreItem(')]")
    
    ids_iniciais = {}
    for el in elementos:
        href = el.get_attribute("href")
        if "abreItem(" in href:
            try:
                parametros = href.split("abreItem(")[-1].split(")")[0]
                cd_estrutura = parametros.split(",")[0].strip()
                if cd_estrutura.isdigit():
                    nome_ponto_partida = el.text.strip()
                    ids_iniciais[cd_estrutura] = nome_ponto_partida
            except Exception as e:
                print(f"Erro ao extrair ID inicial de {href}: {e}")

    print(f"\n{len(ids_iniciais)} pontos de partida encontrados:")
    for id_inicial, nome in ids_iniciais.items():
        print(f"- ID: {id_inicial}, Nome: {nome}")

    visitados = set()
    mapa_final = {}
    
    for id_inicial, nome_inicial in ids_iniciais.items():
        print(f"\nMapeando sub-itens de: '{nome_inicial}' (ID: {id_inicial})...")
        mapa_final[id_inicial] = {
            "nome_inicial": nome_inicial,
            "documentos": []
        }
        _explorar_recursivamente_online(driver, id_inicial, mapa_final, id_inicial, visitados)

    driver.quit()
    print("\n[SUCESSO] Mapeamento online concluído.")
    return mapa_final

# --- ETAPA 2: EXTRAÇÃO DE LINKS E TÍTULOS DOS ARQUIVOS .TXT LOCAIS (LÓGICA ALTERADA) ---

def extrair_dados_dos_txts():
    """
    Varre a pasta de textos, extrai o título da primeira linha e os links de
    imagem do restante do conteúdo.
    Retorna um dicionário mapeando ID para título e lista de links.
    """
    print("\n--- INICIANDO ETAPA 2: Extração de títulos e links dos arquivos .txt (Local) ---")
    if not os.path.isdir(PASTA_TXT):
        print(f"[ERRO] A pasta de textos '{PASTA_TXT}' não foi encontrada.")
        return None
        
    regex_img = re.compile(r'https?://[^\s"\'<>`]+\.(?:png|jpg|jpeg|jfif|gif|webp|bmp|tiff?|avif|heic|heif)', re.IGNORECASE)
    padroes_permitidos = ["/img_elemento/", "/img_estrutura/", "/arq_anexos/"]
    
    # Dicionário para armazenar dados mais completos
    dados_por_id = {}
    
    arquivos_txt = [f for f in os.listdir(PASTA_TXT) if f.lower().endswith(".txt")]
    if not arquivos_txt:
        print(f"[AVISO] Nenhum arquivo .txt encontrado na pasta '{PASTA_TXT}'.")
        return dados_por_id

    print(f"Analisando {len(arquivos_txt)} arquivos .txt...")
    for arquivo in arquivos_txt:
        id_documento = os.path.splitext(arquivo)[0]
        caminho = os.path.join(PASTA_TXT, arquivo)
        
        with open(caminho, "r", encoding="utf-8") as f:
            try:
                # Extrai o título da primeira linha
                primeira_linha = f.readline()
                if primeira_linha.lower().startswith("título:"):
                    titulo = primeira_linha.split(":", 1)[1].strip()
                else:
                    titulo = "Título não encontrado"
                
                # Lê o resto do conteúdo para extrair imagens
                conteudo_restante = f.read()
                links_encontrados = regex_img.findall(conteudo_restante)
                
                links_filtrados = []
                for link in links_encontrados:
                    if any(padrao in link for padrao in padroes_permitidos):
                        links_filtrados.append(link)

                # Armazena a estrutura completa
                if links_filtrados:
                    dados_por_id[id_documento] = {
                        "titulo": titulo,
                        "links": links_filtrados
                    }

            except Exception as e:
                print(f"  - Erro ao processar o arquivo {arquivo}: {e}")

    print("[SUCESSO] Extração de títulos e links dos arquivos locais concluída.")
    return dados_por_id

# --- ETAPA 3: GERAÇÃO DOS RELATÓRIOS CSV (LÓGICA ALTERADA) ---

def gerar_csvs_por_estrutura(mapa_estrutura, mapa_dados_documentos):
    """
    Consolida os dados e gera um CSV para cada ponto de partida,
    contendo o LINK DA IMAGEM e o TÍTULO DO DOCUMENTO de origem.
    """
    print("\n--- INICIANDO ETAPA 3: Geração de relatórios CSV com links e títulos ---")
    os.makedirs(PASTA_SAIDA_CSV, exist_ok=True)
    
    for id_inicial, dados_categoria in mapa_estrutura.items():
        nome_inicial = dados_categoria["nome_inicial"]
        nome_arquivo_seguro = re.sub(r'[\\/*?:"<>|]', "", nome_inicial)
        nome_arquivo_csv = f"{nome_arquivo_seguro}_cd{id_inicial}.csv"
        caminho_csv = os.path.join(PASTA_SAIDA_CSV, nome_arquivo_csv)
        
        # Lista para armazenar as linhas do CSV (link, titulo)
        linhas_para_csv = []
        
        # Inclui o próprio documento inicial na lista de documentos a serem verificados
        documentos_do_grupo = [{"id": id_inicial}] + dados_categoria["documentos"]
        
        # Itera sobre todos os documentos da categoria
        for doc in documentos_do_grupo:
            doc_id = doc["id"]
            
            # Verifica se temos dados (título e links) para este ID
            if doc_id in mapa_dados_documentos:
                titulo_doc = mapa_dados_documentos[doc_id]["titulo"]
                links_doc = mapa_dados_documentos[doc_id]["links"]
                
                # Adiciona uma linha para cada link encontrado
                for link in links_doc:
                    linhas_para_csv.append([link, titulo_doc])
        
        if linhas_para_csv:
            print(f"Gerando arquivo: {caminho_csv} ({len(linhas_para_csv)} registros)")
            
            with open(caminho_csv, "w", newline="", encoding="utf-8") as f:
                writer = csv.writer(f)
                # Escreve o novo cabeçalho com duas colunas
                writer.writerow(["link_imagem", "titulo_documento"])
                # Escreve todas as linhas coletadas
                writer.writerows(linhas_para_csv)
        else:
            print(f"  - Aviso: Nenhum documento com imagens encontrado para '{nome_inicial}'. O arquivo CSV não será gerado.")
            
    print(f"\n[SUCESSO] Relatórios CSV foram gerados na pasta '{PASTA_SAIDA_CSV}'.")

# --- EXECUÇÃO PRINCIPAL (LÓGICA ALTERADA) ---
if __name__ == "__main__":
    mapa_da_estrutura = mapear_estrutura_online()

    if mapa_da_estrutura:
        # Chama a nova função de extração
        dados_dos_documentos = extrair_dados_dos_txts()

        if dados_dos_documentos is not None:
            # Passa a nova estrutura de dados para a função de geração de CSV
            gerar_csvs_por_estrutura(mapa_da_estrutura, dados_dos_documentos)
            print("\nProcesso finalizado com sucesso.")
        else:
            print("\nProcesso interrompido devido a erro na extração de dados dos arquivos.")
    else:
        print("\nProcesso interrompido devido a erro no mapeamento online.")