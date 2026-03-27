from bs4 import BeautifulSoup
from urllib.parse import urlparse, urlunparse, quote
import os
import re

BASE_URL = "https://sistemas.epagri.sc.gov.br/sedimob/consulta.action?subFuncao=consultaDiagnostico&cdEstrutura={}&isEdicao=N&epagriTEC=S"
entrada_dir = "htmls"
saida_dir = "textos"

os.makedirs(saida_dir, exist_ok=True)

def limpar_texto(t):
    t = re.sub(r"\s+", " ", t)
    t = t.replace("▶", "").replace("●", "").replace("•", "•")
    t = re.sub(r"[▶●♦■→◀]+", "", t).strip()
    t = t.replace("fechar /\\", "")  # <- REMOVE o fechar /\
    return t.strip()

def extrair_titulo(soup):
    headers = soup.find_all("div", attrs={"data-role": "header"})
    if not headers:
        return ""
    titulo_div = headers[-1]
    links = titulo_div.find_all("a")
    niveis = [link.get_text(strip=True) for link in links]
    return limpar_texto(" - ".join(niveis))

def extrair_conteudo(filepath):
    with open(filepath, "r", encoding="utf-8") as f:
        soup = BeautifulSoup(f, "html.parser")

    # FILTRO: ignora documentos que são apenas menus (sem conteúdo técnico)
    if not soup.find("form", id="frmManutencaoElemento"):
        print(f"[IGNORADO] {filepath} parece ser apenas um menu.")
        return None
    
    cd = os.path.splitext(os.path.basename(filepath))[0]
    url = BASE_URL.format(cd)
    titulo = extrair_titulo(soup)

    conteudo = []
    conteudo.append(f"Título: {titulo}")
    conteudo.append(f"URL: {url}")
    conteudo.append("")

    corpo = soup.body or soup
    for elem in corpo.descendants:
        if elem.name in ["script", "style"]:
            continue

        if elem.name in ["h1", "h2", "h3"]:
            texto = limpar_texto(elem.get_text(separator=" ", strip=True))
            if texto:
                conteudo.append(f"\n=== {texto.upper()} ===")

        elif elem.name in ["p", "li"]:
            texto = limpar_texto(elem.get_text(separator=" ", strip=True))
            if texto:
                conteudo.append(texto)

        elif elem.name == "b":
            texto = limpar_texto(elem.get_text(separator=" ", strip=True))
            if texto and texto != "Enviar Feedback":
                next_elem = elem.find_next_sibling()
                next_block = next_elem.find_next_sibling() if next_elem else None

                is_legitimo = (
                    next_elem and next_elem.name == "br" and
                    next_block and next_block.name in ["p", "div"]
                )

                # NOVO: verificar se o <b> está após um <hr>
                prev_elem = elem.find_previous_sibling()
                is_apos_hr = prev_elem and prev_elem.name == "hr"

                if is_legitimo or is_apos_hr:
                    conteudo.append(f"\n-- {texto} --")


        elif elem.name == "img":
            IMAGENS_EXCLUIR = [
                "http://intranetdoc.epagri.sc.gov.br/sedimob/img/sedimob_icone_banana_color.png",
                "./img/iconeDocumento.png",
                "/sedimob/img/iconeBarraHomeBranco.png",
                "/sedimob/img/iconeEpagriTecMobSemBorda.png",
                "/sedimob/img/iconeVoltarBranco.png"
            ]
            src = elem.get("src", "")
            alt = elem.get("alt", "")
            legenda = ""

            if src:
                parsed = urlparse(src)
                path_encoded = quote(parsed.path)
                src = urlunparse((parsed.scheme, parsed.netloc, path_encoded, parsed.params, parsed.query, parsed.fragment))

            if elem.find_parent():
                parent_text = limpar_texto(elem.find_parent().get_text(separator=" ", strip=True))
                if parent_text and len(parent_text) < 300:
                    legenda = parent_text

            if src not in IMAGENS_EXCLUIR:
                conteudo.append(f"[IMAGEM] {src}")
                if legenda:
                    conteudo.append(f"Legenda: {legenda}")
                    
        elif elem.name == "font":
            texto = limpar_texto(elem.get_text(separator=" ", strip=True))
            if texto and "enviar feedback" not in texto.lower():
                # Evita repetir rodapés como "Criado em" etc.
                if not re.search(r"(Criado em|Última atualização)", texto, re.IGNORECASE):
                    conteudo.append(texto)

    

    return "\n".join(conteudo)

# === Processa todos os HTMLs da pasta ===

#for nome_arquivo in os.listdir(entrada_dir):  # se fizer desse jeito não aparece ordenado no console
for nome_arquivo in sorted(os.listdir(entrada_dir), key=lambda x: int(os.path.splitext(x)[0])):
    if nome_arquivo.endswith(".html"):
        caminho = os.path.join(entrada_dir, nome_arquivo)
        texto_extraido = extrair_conteudo(caminho)
        if texto_extraido is None:
            continue  # pula arquivos inúteis

        saida = os.path.join(saida_dir, nome_arquivo.replace(".html", ".txt"))
        with open(saida, "w", encoding="utf-8") as ftxt:
            ftxt.write(texto_extraido)

        print(f"[OK] Texto salvo: {saida}")