from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import os
import time

# Conjunto para evitar visitas duplicadas
visitados = set()

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
def visitar(cdEstrutura, pasta_saida):
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
    # Salva na subpasta correta
    with open(os.path.join(pasta_saida, f"{cdEstrutura}.html"), "w", encoding="utf-8") as f:
        f.write(html)
    print(f"HTML salvo: {pasta_saida}/{cdEstrutura}.html")

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
                # Passa a mesma pasta_saida para a chamada recursiva
                visitar(codigo, pasta_saida)
    else:
        print(f"Nenhum dadosTabela encontrado em {cdEstrutura}.")

def iniciar_visita(cdEstrutura, nome_pasta):
    """
    Função para iniciar o processo de visita para um item específico,
    criando uma pasta dedicada para ele.
    """
    # Define a pasta de saída para a chamada específica
    pasta_saida = f"htmls_SITEINTEIRO/{nome_pasta}"
    os.makedirs(pasta_saida, exist_ok=True)
    # Limpa o conjunto de visitados para cada nova chamada
    global visitados
    visitados = set()
    visitar(cdEstrutura, pasta_saida)

# --- CHAMADAS PRINCIPAIS ---
# já foi iniciar_visita(7983, "banana")
# iniciar_visita(9147, "mangarito")
# ja foi iniciar_visita(13031, "arroz_irrigado")
# ja foi iniciar_visita(1, "tomate")
# iniciar_visita(8233, "cebola")
# ja foi iniciar_visita(670, "adubacao_verde")
# iniciar_visita(14962, "pancs")
# iniciar_visita(18468, "compostagem")
# iniciar_visita(2181, "calda_bordalesa")
# ja foi iniciar_visita(21434, "termoterapia")
# iniciar_visita(18792, "biofertilizante_EEI")
# iniciar_visita(9860, "piscicultura")
iniciar_visita(20968, "formigas")
# ja foi iniciar_visita(9346, "legislacoes")

# Finaliza o navegador
driver.quit()
print("Finalizado.")