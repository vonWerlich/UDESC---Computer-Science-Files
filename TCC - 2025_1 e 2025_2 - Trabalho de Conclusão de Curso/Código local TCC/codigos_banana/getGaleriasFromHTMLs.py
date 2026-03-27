import os
import re
import time
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.common.by import By
from selenium.webdriver.support import expected_conditions as EC

PASTA_HTML = "htmls_banana"                # HTMLs principais (pais)
PASTA_GALERIA = "htmls_galeria"     # Pasta onde vamos salvar os HTMLs renderizados das galerias
os.makedirs(PASTA_GALERIA, exist_ok=True)

# Configura o Chrome em modo headless
chrome_options = Options()
chrome_options.add_argument("--headless=new")  # headless moderno
chrome_options.add_argument("--disable-gpu")
chrome_options.add_argument("--no-sandbox")
chrome_options.add_argument("--window-size=1920x1080")

driver = webdriver.Chrome(options=chrome_options)

BASE_URL_GALERIA = (
    "https://sistemas.epagri.sc.gov.br/sedimob/consulta.action"
    "?subFuncao=consultaDiagnosticoGaleria"
    "&cdEstrutura={}&cdElemento={}&nrAnexo={}&isEdicao=N&cdAnexo={}&epagriTEC=S"
)

def baixar_galeria(cd_anexo, cd_estrutura, cd_elemento, nr_anexo):
    """
    Abre a galeria no navegador headless, espera carregar imagens e legendas,
    e salva o HTML renderizado completo.
    """
    url = BASE_URL_GALERIA.format(cd_estrutura, cd_elemento, nr_anexo, cd_anexo)
    print("Acessando:", url)
    driver.get(url)

    try:
        # Espera até que pelo menos 1 imagem apareça no DOM
        WebDriverWait(driver, 10).until(
            EC.presence_of_element_located((By.TAG_NAME, "img"))
        )
    except Exception:
        print("[AVISO] Nenhuma imagem carregada em", url)

    # Espera um pouco extra para as legendas aparecerem
    time.sleep(2)

    # Pega o HTML já renderizado
    html = driver.page_source

    # Nome do arquivo salvo
    nome_arquivo = f"{cd_estrutura}_{cd_elemento}_{cd_anexo}_{nr_anexo}.html"
    caminho = os.path.join(PASTA_GALERIA, nome_arquivo)

    with open(caminho, "w", encoding="utf-8") as f:
        f.write(html)

    print("[OK] Salvo em:", caminho)


# Regex para capturar parâmetros de abrirGaleria(...)
# Ordem capturada: cdAnexo, cdEstrutura, cdElemento, nrAnexo
REGEX_GALERIA = re.compile(
    r"abrirGaleria\([^)]*?(?:&quot;[A-Za-z]&quot;|['\"][A-Za-z]['\"])?,?\s*"
    r"(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*\)"
)

# Varrer os HTMLs principais
for nome in os.listdir(PASTA_HTML):
    if not nome.endswith(".html"):
        continue

    caminho = os.path.join(PASTA_HTML, nome)
    with open(caminho, "r", encoding="utf-8") as f:
        conteudo = f.read()

    matches = REGEX_GALERIA.findall(conteudo)
    if matches:
        print("\n[+] Encontrados", len(matches), "abrirGaleria em", nome)

    for (cd_anexo, cd_estrutura, cd_elemento, nr_anexo) in matches:
        saida_nome = f"{cd_estrutura}_{cd_elemento}_{cd_anexo}_{nr_anexo}.html"
        saida_caminho = os.path.join(PASTA_GALERIA, saida_nome)
        if os.path.exists(saida_caminho):
            print("Já existe, pulando:", saida_nome)
            continue
        try:
            baixar_galeria(cd_anexo, cd_estrutura, cd_elemento, nr_anexo)
        except Exception as e:
            print("[ERRO] Falha ao baixar", saida_nome, ":", str(e))

driver.quit()
print("\nFinalizado.")
