from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.by import By
import os
import time

# Conjunto para evitar visitas duplicadas
visitados = set()

# Pasta onde os arquivos HTML serão salvos
os.makedirs("htmlsteste", exist_ok=True)

# Configuração do navegador headless
options = Options()
options.add_argument("--headless")
options.add_argument("--disable-gpu")
options.add_argument("--window-size=1920x1080")
driver = webdriver.Chrome(options=options)

# URL base usada para montar os links
BASE_URL = "https://sistemas.epagri.sc.gov.br/sedimob/consulta.action?subFuncao=consultaDiagnostico&cdEstrutura={}&isEdicao=N&epagriTEC=S"

# Função auxiliar: expande todos os links "...mais /"
def expandir_colapsados():
    try:
        links = driver.find_elements(By.XPATH, "//a[contains(text(), '...mais')]")
        print(f"Expandindo {len(links)} blocos colapsados...")
        for link in links:
            try:
                driver.execute_script("arguments[0].click();", link)
                time.sleep(0.1)
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
    time.sleep(2)

    # Expande os blocos de texto colapsados
    expandir_colapsados()
    time.sleep(1)  # garante que o texto foi carregado

    # Salva o HTML da página expandida
    html = driver.page_source
    with open(f"htmls/{cdEstrutura}.html", "w", encoding="utf-8") as f:
        f.write(html)
    print(f"HTML salvo: htmls/{cdEstrutura}.html")

    # Tenta extrair a variável dadosTabela do JavaScript
    try:
        dadosTabela = driver.execute_script("return typeof dadosTabela !== 'undefined' ? dadosTabela : null")
    except Exception as e:
        print(f"Erro ao tentar obter dadosTabela em {cdEstrutura}: {e}")
        dadosTabela = None

    # Se houver subitens, visitar cada um recursivamente
    if dadosTabela:
        print(f"{len(dadosTabela)} subitens encontrados em {cdEstrutura}.")
        for item in dadosTabela:
            codigo_html = item.get("codigo", "").strip()
            codigo = ''.join(filter(str.isdigit, codigo_html))
            if codigo:
                visitar(codigo)
    else:
        print(f"Nenhum dadosTabela encontrado em {cdEstrutura}.")

# Inicia pela raiz
visitar("7983")

# Finaliza o navegador
driver.quit()
print("Finalizado.")
