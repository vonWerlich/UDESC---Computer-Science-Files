from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import os
import time

# Conjunto para evitar visitas duplicadas (reiniciado para cada raiz)
visitados = set()

# Configuração do navegador
options = Options()
options.add_argument("--headless")  # remova para debug
options.add_argument("--disable-gpu")
options.add_argument("--window-size=1920x1080")

# BLOQUEAR IMAGENS, CSS e fontes
prefs = {
    "profile.managed_default_content_settings.images": 2,
    "profile.managed_default_content_settings.stylesheets": 2,
    "profile.managed_default_content_settings.fonts": 2,
}
options.add_experimental_option("prefs", prefs)

driver = webdriver.Chrome(options=options)

# URL base
BASE_URL = "https://sistemas.epagri.sc.gov.br/sedimob/consulta.action?subFuncao=consultaDiagnostico&cdEstrutura={}&isEdicao=N&epagriTEC=S"

# Função auxiliar: expande blocos "...mais"
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
def visitar(cdEstrutura, pasta_saida):
    global visitados
    if cdEstrutura in visitados:
        return

    print(f"Visitando {cdEstrutura}...")
    visitados.add(cdEstrutura)

    url = BASE_URL.format(cdEstrutura)
    driver.get(url)

    # Espera a página carregar
    WebDriverWait(driver, 10).until(EC.presence_of_element_located((By.TAG_NAME, "body")))

    expandir_colapsados()
    time.sleep(1)

    # Salva HTML
    html = driver.page_source
    with open(os.path.join(pasta_saida, f"{cdEstrutura}.html"), "w", encoding="utf-8") as f:
        f.write(html)
    print(f"HTML salvo: {pasta_saida}/{cdEstrutura}.html")

    # Busca subitens via JavaScript
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
                visitar(codigo, pasta_saida)
    else:
        print(f"Nenhum dadosTabela encontrado em {cdEstrutura}.")

# Função para iniciar cada árvore em uma subpasta
def iniciar_visita(cdEstrutura, nome_pasta):
    global visitados
    visitados = set()
    pasta_saida = f"htmls_SITEINTEIRO/{nome_pasta}"
    os.makedirs(pasta_saida, exist_ok=True)
    visitar(cdEstrutura, pasta_saida)

# === Início: coleta cdEstrutura da página principal ===
pagina_inicial = "https://sistemas.epagri.sc.gov.br/sedimob/consulta.action?subFuncao=epagriTec"
driver.get(pagina_inicial)

WebDriverWait(driver, 10).until(
    EC.presence_of_all_elements_located((By.XPATH, "//a[contains(@href, 'javascript:abreItem(')]"))
)

# Extrai cdEstrutura
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

# Inicia visita para cada cdEstrutura inicial
for cd in ids_iniciais:
    iniciar_visita(cd, f"id_{cd}")

# Finaliza
driver.quit()
print("Finalizado.")
