from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import os
import time

# Conjunto para evitar visitas duplicadas
visitados = set()

# Pasta onde os arquivos HTML serão salvos
PASTA_SAIDA = "htmls_tomate"
os.makedirs(PASTA_SAIDA, exist_ok=True)

# Configuração do navegador (pode remover headless para debug)
options = Options()
options.add_argument("--headless")  # remova esta linha para ver o navegador
options.add_argument("--disable-gpu")
options.add_argument("--window-size=1920x1080")

# BLOQUEAR IMAGENS, CSS, FONTES PARA MAIOR VELOCIDADE
prefs = {
    "profile.managed_default_content_settings.images": 2,
    "profile.managed_default_content_settings.stylesheets": 2,
    "profile.managed_default_content_settings.fonts": 2,
    }
options.add_experimental_option("prefs", prefs)

driver = webdriver.Chrome(options=options)

# URL base usada para montar os links
BASE_URL = "https://sistemas.epagri.sc.gov.br/sedimob/consulta.action?subFuncao=consultaDiagnostico&cdEstrutura={}&isEdicao=N&epagriTEC=S"

# Função auxiliar: expande os blocos "...mais"
def expandir_colapsados():
    try:
        links = driver.find_elements(By.XPATH, "//a[contains(text(), '...mais')]")
        if links:
            print(f"Expandindo {len(links)} blocos colapsados...")
            for link in links:
                try:
                    driver.execute_script("arguments[0].click();", link)
                    time.sleep(0.1) # Pequena pausa para o JS executar
                except Exception:
                    continue
    except Exception as e:
        print(f"Erro ao expandir colapsados: {e}")

# Função recursiva principal
def visitar(cdEstrutura):
    if cdEstrutura in visitados:
        return

    print(f"Visitando {cdEstrutura}...")
    visitados.add(cdEstrutura)

    url = BASE_URL.format(cdEstrutura)
    driver.get(url)
    
    # Espera o carregamento da página
    WebDriverWait(driver, 10).until(EC.presence_of_element_located((By.TAG_NAME, "body")))

    expandir_colapsados()
    time.sleep(1) # Espera extra para garantir que o conteúdo expandido carregue

    html = driver.page_source
    # Corrigindo o caminho do arquivo salvo para corresponder à pasta
    caminho_arquivo = os.path.join(PASTA_SAIDA, f"{cdEstrutura}.html")
    with open(caminho_arquivo, "w", encoding="utf-8") as f:
        f.write(html)
    print(f"HTML salvo: {caminho_arquivo}")

    try:
        dadosTabela = driver.execute_script("return typeof dadosTabela !== 'undefined' ? dadosTabela : null")
    except Exception as e:
        print(f"Erro ao tentar obter dadosTabela em {cdEstrutura}: {e}")
        dadosTabela = None

    if dadosTabela:
        print(f"{len(dadosTabela)} subitens encontrados em {cdEstrutura}.")
        for item in dadosTabela:
            # A chave parece ser "codigo" e não "código" no JS da página
            codigo_html = item.get("codigo", "").strip() 
            # Extrai apenas os dígitos do código, caso haja algum HTML junto
            codigo = ''.join(filter(str.isdigit, codigo_html))
            if codigo:
                visitar(codigo)
    else:
        print(f"Nenhum dadosTabela encontrado em {cdEstrutura}.")

# === Início: Define o ponto de partida manualmente ===

# ID inicial a partir do qual a varredura começará (Tomate)
id_de_partida = "1" 

print(f"Iniciando a varredura a partir do cdEstrutura: {id_de_partida}")

# Inicia a recursão a partir deste ID específico
visitar(id_de_partida)


# Finaliza o navegador
driver.quit()
print("Finalizado.")