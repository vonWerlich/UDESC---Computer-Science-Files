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
PASTA_SAIDA = "htmls"
os.makedirs(PASTA_SAIDA, exist_ok=True)

# Configuração do navegador (pode remover headless para debug)
options = Options()
options.add_argument("--headless")  # remova esta linha para ver o navegador
options.add_argument("--disable-gpu")
options.add_argument("--window-size=1920x1080")

# BLOQUEAR IMAGENS
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
    
    # Espera o carregamento da página
    WebDriverWait(driver, 10).until(EC.presence_of_element_located((By.TAG_NAME, "body")))

    expandir_colapsados()
    time.sleep(1)

    html = driver.page_source
    with open(f"{PASTA_SAIDA}/{cdEstrutura}.html", "w", encoding="utf-8") as f:
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


visitar(7983) # banana
# visitar(9147) # mangarito
visitar(13031) # arroz irrigado
# visitar(1) # tomate
# visitar(8233) # cebola
# visitar(670) # plantas para adubação verde
# visitar(14962) # PANCs
# visitar(18468) # compostagem
# visitar(2181) # calda bordalesa
# visitar(21434) # termoterapia para substratos
# visitar(18792) # biofertilizante EEI
# visitar(9860) # piscicultura em viveiros escavados
# visitar(20968) # formigas em pinus e eucaliptus
# visitar(9346) # legislações

# Finaliza o navegador
driver.quit()
print("Finalizado.")
