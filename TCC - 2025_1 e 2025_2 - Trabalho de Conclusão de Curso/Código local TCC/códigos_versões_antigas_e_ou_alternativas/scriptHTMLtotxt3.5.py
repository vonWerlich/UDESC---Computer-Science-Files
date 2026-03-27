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
    t = t.replace("fechar /\\", "")
    return t.strip()

def extrair_width(img):
    """Extrai largura de um <img> tanto de width= quanto de style='width:XXXpx'."""
    # Tenta atributo width
    try:
        w = int(img.get("width", 0))
        if w > 0:
            return w
    except ValueError:
        pass

    # Tenta pegar do style
    style = img.get("style", "")
    m = re.search(r"width\s*:\s*(\d+)px", style)
    if m:
        try:
            return int(m.group(1))
        except ValueError:
            return 0
    return 0

def eh_menu(soup):
    """
    Identifica se a página é apenas um menu de navegação e não um conteúdo final.
    Agora evita falsos positivos considerando imagens grandes mesmo quando o tamanho está no style.
    """
    tabela = soup.find(id="consultaEstruturaTable")
    if not tabela:
        return False  # não tem tabela -> não é menu

    linhas = tabela.find_all("tr")
    if not linhas:
        return True

    textos = []
    linhas_com_imagem_grande = 0
    linhas_uteis = 0

    for tr in linhas:
        txt = limpar_texto(tr.get_text(" ", strip=True))
        if not txt:
            continue  # ignora linhas vazias
        linhas_uteis += 1
        textos.append(txt)

        # Verifica se a linha tem pelo menos uma imagem grande
        imgs = tr.find_all("img")
        for img in imgs:
            w = extrair_width(img)
            if w >= 200:
                linhas_com_imagem_grande += 1
                break  # basta 1 imagem grande para contar a linha

    # Se metade ou mais das linhas úteis têm imagem grande -> não é menu
    if linhas_uteis > 0 and (linhas_com_imagem_grande / linhas_uteis) >= 0.5:
        return False

    # Regra para tabelas grandes
    if linhas_uteis > 8:
        for t in textos:
            if len(t) > 80 and any(v in t.lower() for v in [" é ", " são ", " contém ", " apresenta "]):
                return False
        return True

    # Caso com poucas linhas: verifica títulos curtos e sem verbos
    titulos_curto = 0
    for t in textos:
        if len(t) <= 80 and not any(v in t.lower() for v in [" é ", " são ", " contém ", " apresenta "]):
            titulos_curto += 1
    return titulos_curto / len(textos) > 0.8


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

    # NOVO CRITÉRIO: ignora documentos que são apenas menus
    if eh_menu(soup):
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

                # verificar se o <b> está após um <hr>
                prev_elem = elem.find_previous_sibling()
                is_apos_hr = prev_elem and prev_elem.name == "hr"

                if is_legitimo or is_apos_hr:
                    conteudo.append(f"\n-- {texto} --")

        elif elem.name == "img":
            IMAGENS_EXCLUIR = [
                "http://intranetdoc.epagri.sc.gov.br/sedimob/img/sedimob_icone_banana_color.png",
                "http://intranetdoc.epagri.sc.gov.br/sedimob/img/sedimob_icone_culturas_color.png",
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
                if not re.search(r"(Criado em|Última atualização)", texto, re.IGNORECASE):
                    conteudo.append(texto)

    return "\n".join(conteudo)

# === Processa todos os HTMLs da pasta ===
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
