from bs4 import BeautifulSoup
import os
import json

entrada_dir = "htmls"
saida_dir = "jsons_limpos"
os.makedirs(saida_dir, exist_ok=True)

BASE_URL = "https://sistemas.epagri.sc.gov.br/sedimob/consulta.action?subFuncao=consultaDiagnostico&cdEstrutura={}&isEdicao=N&epagriTEC=S"

def extrair_titulo(soup):
    trilha = []

    # Encontra todos os <a> que têm um cdEstrutura na URL
    for a in soup.find_all("a", href=True):
        if "cdEstrutura=" in a['href']:
            texto = a.get_text(strip=True)
            if texto and texto != "◀":
                trilha.append(texto)

    # Remove duplicatas mantendo a ordem (caso ocorram)
    trilha_unica = []
    for item in trilha:
        if item not in trilha_unica:
            trilha_unica.append(item)

    return " ▶ ".join(trilha_unica)

def remover_imagens_irrelevantes(soup):
    for img in soup.find_all("img"):
        src = img.get("src", "")
        if (
            src.startswith("/sedimob/img/icone") or
            src == "/sedimob/img/sedimob_icone_banana_color.png"
        ):
            img.decompose()

def extrair_conteudo(filepath):
    with open(filepath, "r", encoding="utf-8") as f:
        soup = BeautifulSoup(f, "html.parser")

    cd = os.path.splitext(os.path.basename(filepath))[0]
    url = BASE_URL.format(cd)

    remover_imagens_irrelevantes(soup)
    titulo = extrair_titulo(soup)
    texto = []
    tabelas = []
    imagens = []

    # Extrair textos
    for tag in soup.find_all(["p", "h1", "h2", "h3", "li"]):
        txt = tag.get_text(strip=True)
        if txt:
            texto.append(txt)

    # Extrair tabelas
    for tabela in soup.find_all("table"):
        linhas = []
        for tr in tabela.find_all("tr"):
            colunas = [td.get_text(strip=True) for td in tr.find_all(["td", "th"])]
            if colunas:
                linhas.append(" | ".join(colunas))
        if linhas:
            tabelas.append("\n".join(linhas))

    # Extrair imagens restantes
    for img in soup.find_all("img"):
        src = img.get("src", "")
        alt = img.get("alt", "")
        legenda = ""
        parent = img.find_parent()
        if parent:
            parent_text = parent.get_text(strip=True)
            if 0 < len(parent_text) < 300:
                legenda = parent_text
        imagens.append({
            "src": src,
            "alt": alt,
            "legenda": legenda
        })

    return {
        "cdEstrutura": cd,
        "url": url,
        "titulo": titulo,
        "texto": texto,
        "tabelas": tabelas,
        "imagens": imagens
    }

# Processar todos os arquivos da pasta
for nome in os.listdir(entrada_dir):
    if nome.endswith(".html"):
        caminho = os.path.join(entrada_dir, nome)
        dados = extrair_conteudo(caminho)

        saida = os.path.join(saida_dir, nome.replace(".html", ".json"))
        with open(saida, "w", encoding="utf-8") as f:
            json.dump(dados, f, ensure_ascii=False, indent=2)
        print(f"Salvo: {saida}")
