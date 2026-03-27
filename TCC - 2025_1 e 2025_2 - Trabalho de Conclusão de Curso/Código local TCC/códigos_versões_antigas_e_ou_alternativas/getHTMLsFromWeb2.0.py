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
os.makedirs("htmls", exist_ok=True)

# Configuração do navegador (pode remover headless para debug)
options = Options()
options.add_argument("--headless")  # remova esta linha para ver o navegador
options.add_argument("--disable-gpu")
options.add_argument("--window-size=1920x1080")
driver = webdriver.Chrome(options=options)

# URL base usada para montar os links
BASE_URL = "https://sistemas.epagri.sc.gov.br/sedimob/consulta.action?subFuncao=consultaDiagnostico&cdEstrutura={}&isEdicao=N&epagriTEC=S"

# Função auxiliar: expande os blocos "...mais"
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

    expandir_colapsados()
    time.sleep(1)

    html = driver.page_source
    with open(f"htmls/{cdEstrutura}.html", "w", encoding="utf-8") as f:
        f.write(html)
    print(f"HTML salvo: htmls/{cdEstrutura}.html")

    try:
        dadosTabela = driver.execute_script("return typeof dadosTabela !== 'undefined' ? dadosTabela : null")
    except Exception as e:
        print(f"Erro ao tentar obter dadosTabela em {cdEstrutura}: {e}")
        dadosTabela = None

    if dadosTabela:
        print(f"{len(dadosTabela)} subitens encontrados em {cdEstrutura}.")
        for item in dadosTabela:
            codigo_html = item.get("codigo", "").strip()
            codigo = ''.join(filter(str.isdigit, codigo_html))
            if codigo:
                visitar(codigo)
    else:
        print(f"Nenhum dadosTabela encontrado em {cdEstrutura}.")

# === Início: coleta os códigos da página principal ===

pagina_inicial = "https://sistemas.epagri.sc.gov.br/sedimob/consulta.action?subFuncao=epagriTec"
driver.get(pagina_inicial)

# Espera os elementos carregarem
WebDriverWait(driver, 10).until(
    EC.presence_of_all_elements_located((By.XPATH, "//a[contains(@href, 'javascript:abreItem(')]"))
)

# Extrai os cdEstrutura dos hrefs "javascript:abreItem(cdEstrutura, cdAwtecest)"
elementos = driver.find_elements(By.XPATH, "//a[contains(@href, 'javascript:abreItem(')]")

ids_iniciais = set()
for el in elementos:
    href = el.get_attribute("href")
    if "abreItem(" in href:
        try:
            parametros = href.split("abreItem(")[-1].split(")")[0]
            cdEstrutura = parametros.split(",")[0].strip()
            if cdEstrutura.isdigit():
                ids_iniciais.add(cdEstrutura)
        except Exception as e:
            print(f"Erro ao extrair de {href}: {e}")

print(f"{len(ids_iniciais)} cdEstrutura(s) iniciais encontrados: {sorted(ids_iniciais)}")

# Inicia recursão a partir de cada id inicial
for cd in ids_iniciais:
    visitar(cd)

# Finaliza o navegador
driver.quit()
print("Finalizado.")
