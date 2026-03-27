from bs4 import BeautifulSoup
import os
import json

BASE_URL = "https://sistemas.epagri.sc.gov.br/sedimob/consulta.action?subFuncao=consultaDiagnostico&cdEstrutura={}&isEdicao=N&epagriTEC=S"
entrada_dir = "htmls"
saida_dir = "jsons"

os.makedirs(saida_dir, exist_ok=True)

def extrair_conteudo(filepath):
    with open(filepath, "r", encoding="utf-8") as f:
        soup = BeautifulSoup(f, "html.parser")

    cd = os.path.splitext(os.path.basename(filepath))[0]
    url = BASE_URL.format(cd)

    texto = []
    tabelas = []
    imagens = []

    # Extrai texto visível de parágrafos, títulos e listas
    for tag in soup.find_all(["p", "h1", "h2", "h3", "li"]):
        txt = tag.get_text(strip=True)
        if txt:
            texto.append(txt)

    # Extrai tabelas como texto simples
    for tabela in soup.find_all("table"):
        linhas = []
        for tr in tabela.find_all("tr"):
            colunas = [td.get_text(strip=True) for td in tr.find_all(["td", "th"])]
            if colunas:
                linhas.append(" | ".join(colunas))
        if linhas:
            tabelas.append("\n".join(linhas))

    # Extrai imagens e tenta achar legendas ou contexto
    for img in soup.find_all("img"):
        src = img.get("src", "")
        alt = img.get("alt", "")
        legenda = ""

        # Verifica se há legenda ou texto próximo
        parent_text = img.find_parent().get_text(strip=True) if img.find_parent() else ""
        if parent_text and len(parent_text) < 300:
            legenda = parent_text

        imagens.append({
            "src": src,
            "alt": alt,
            "legenda": legenda
        })

    return {
        "cdEstrutura": cd,
        "url": url,
        "titulo": soup.title.string.strip() if soup.title else "",
        "texto": texto,
        "tabelas": tabelas,
        "imagens": imagens
    }

# Processa todos os HTMLs da pasta
for nome_arquivo in os.listdir(entrada_dir):
    if nome_arquivo.endswith(".html"):
        caminho = os.path.join(entrada_dir, nome_arquivo)
        conteudo = extrair_conteudo(caminho)

        # Salva JSON correspondente
        saida = os.path.join(saida_dir, nome_arquivo.replace(".html", ".json"))
        with open(saida, "w", encoding="utf-8") as fjson:
            json.dump(conteudo, fjson, ensure_ascii=False, indent=2)
        print(f"JSON salvo: {saida}")
