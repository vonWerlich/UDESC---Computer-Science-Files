from bs4 import BeautifulSoup
import os
import json
import re

BASE_URL = "https://sistemas.epagri.sc.gov.br/sedimob/consulta.action?subFuncao=consultaDiagnostico&cdEstrutura={}&isEdicao=N&epagriTEC=S"
entrada_dir = "htmls"
saida_dir = "jsons"

os.makedirs(saida_dir, exist_ok=True)

def limpar_texto(t):
    return re.sub(r"[▶●♦■→◀]+", "", t).strip()

def extrair_titulo(soup):
    headers = soup.find_all("div", attrs={"data-role": "header"})
    if not headers:
        return ""

    # Assume que o último <div data-role="header"> tem o título real
    titulo_div = headers[-1]

    # Pega os <a> dentro do título
    links = titulo_div.find_all("a")

    # Extrai os dois pedaços do título (categoria + subtítulo)
    categoria = links[0].get_text(strip=True) if len(links) >= 1 else ""
    subtitulo = links[1].get_text(strip=True) if len(links) >= 2 else ""

    titulo = f"{categoria} - {subtitulo}" if subtitulo else categoria
    return limpar_texto(titulo)

def extrair_conteudo(filepath):
    with open(filepath, "r", encoding="utf-8") as f:
        soup = BeautifulSoup(f, "html.parser")

    cd = os.path.splitext(os.path.basename(filepath))[0]
    url = BASE_URL.format(cd)
    titulo = extrair_titulo(soup)

    conteudo = []

    corpo = soup.body or soup
    for elem in corpo.descendants:
        if elem.name in ["script", "style"]:
            continue

        if elem.name in ["h1", "h2", "h3"]:
            texto = limpar_texto(elem.get_text(strip=True))
            if texto:
                conteudo.append({"tipo": "titulo", "valor": texto})

        elif elem.name in ["p", "li"]:
            texto = limpar_texto(elem.get_text(strip=True))
            if texto:
                conteudo.append({"tipo": "texto", "valor": texto})

        elif elem.name == "table":
            linhas = []
            for tr in elem.find_all("tr"):
                cols = [td.get_text(strip=True) for td in tr.find_all(["td", "th"])]
                if cols:
                    linhas.append(" | ".join(cols))
            if linhas:
                conteudo.append({"tipo": "tabela", "valor": "\n".join(linhas)})

        elif elem.name == "img":
            src = elem.get("src", "")
            alt = elem.get("alt", "")
            legenda = ""

            if elem.find_parent():
                parent_text = limpar_texto(elem.find_parent().get_text(strip=True))
                if parent_text and len(parent_text) < 300:
                    legenda = parent_text

            conteudo.append({
                "tipo": "imagem",
                "src": src,
                "alt": alt
            })

            if legenda:
                conteudo.append({
                    "tipo": "texto",
                    "valor": legenda
                })

    return {
        "cdEstrutura": cd,
        "url": url,
        "titulo": titulo,
        "conteudo": conteudo
    }



# === Processa todos os HTMLs da pasta ===
for nome_arquivo in os.listdir(entrada_dir):
    if nome_arquivo.endswith(".html"):
        caminho = os.path.join(entrada_dir, nome_arquivo)
        dados = extrair_conteudo(caminho)

        saida = os.path.join(saida_dir, nome_arquivo.replace(".html", ".json"))
        with open(saida, "w", encoding="utf-8") as fjson:
            json.dump(dados, fjson, ensure_ascii=False, indent=2)

        print(f"[OK] JSON salvo: {saida}")
