#versão para pegar legendas em html_galeria

from bs4 import BeautifulSoup
from urllib.parse import urlparse, urlunparse, quote
import os
import re

# === CONFIGURAÇÕES GERAIS ===
BASE_URL = "https://sistemas.epagri.sc.gov.br/sedimob/consulta.action?subFuncao=consultaDiagnostico&cdEstrutura={}&isEdicao=N&epagriTEC=S"
entrada_dir = "htmls_banana"            # Pasta com os HTMLs principais
saida_dir = "textos"             # Pasta para salvar os textos finais
galeria_dir = "htmls_galeria"    # Pasta onde estão os HTMLs de galeria renderizados

os.makedirs(saida_dir, exist_ok=True)

# === Função de limpeza de texto ===
def limpar_texto(t):
    # Remove excesso de espaços, símbolos estranhos e lixo visual
    t = re.sub(r"\s+", " ", t)
    t = t.replace("▶", "").replace("●", "").replace("•", "•")
    t = re.sub(r"[▶●♦■→◀]+", "", t).strip()
    t = t.replace("fechar /\\", "")
    return t.strip()

# === Função para extrair largura de uma imagem (<img>) ===
def extrair_width(img):
    """Extrai largura de um <img> tanto de width= quanto de style='width:XXXpx'."""
    try:
        w = int(img.get("width", 0))
        if w > 0:
            return w
    except ValueError:
        pass

    style = img.get("style", "")
    m = re.search(r"width\s*:\s*(\d+)px", style)
    if m:
        try:
            return int(m.group(1))
        except ValueError:
            return 0
    return 0

# === Função que identifica se um HTML é apenas um menu ===
def eh_menu(soup):
    """
    Identifica se a página é apenas um menu de navegação e não um conteúdo final.
    Agora evita falsos positivos considerando imagens grandes mesmo quando o tamanho está no style.
    """
    tabela = soup.find(id="consultaEstruturaTable")
    if not tabela:
        return False

    linhas = tabela.find_all("tr")
    if not linhas:
        return True

    textos = []
    linhas_com_imagem_grande = 0
    linhas_uteis = 0

    for tr in linhas:
        txt = limpar_texto(tr.get_text(" ", strip=True))
        if not txt:
            continue
        linhas_uteis += 1
        textos.append(txt)

        # Se tiver uma imagem grande, considera como conteúdo real
        imgs = tr.find_all("img")
        for img in imgs:
            w = extrair_width(img)
            if w >= 200:
                linhas_com_imagem_grande += 1
                break

    if linhas_uteis > 0 and (linhas_com_imagem_grande / linhas_uteis) >= 0.5:
        return False

    if linhas_uteis > 8:
        for t in textos:
            if len(t) > 80 and any(v in t.lower() for v in [" é ", " são ", " contém ", " apresenta "]):
                return False
        return True

    titulos_curto = 0
    for t in textos:
        if len(t) <= 80 and not any(v in t.lower() for v in [" é ", " são ", " contém ", " apresenta "]):
            titulos_curto += 1
    return titulos_curto / len(textos) > 0.8

# === Função para extrair título do documento ===
def extrair_titulo(soup):
    headers = soup.find_all("div", attrs={"data-role": "header"})
    if not headers:
        return ""
    titulo_div = headers[-1]
    links = titulo_div.find_all("a")
    niveis = [link.get_text(strip=True) for link in links]
    return limpar_texto(" - ".join(niveis))

# === NOVA FUNÇÃO: pegar legenda de uma galeria, se existir ===
def buscar_legenda_galeria(cd_estrutura, cd_elemento, cd_anexo, nr_anexo):
    """
    Procura o arquivo HTML correspondente na pasta de galerias
    e extrai a descrição da legenda, se existir.
    """
    nome_arquivo = f"{cd_estrutura}_{cd_elemento}_{cd_anexo}_{nr_anexo}.html"
    caminho = os.path.join(galeria_dir, nome_arquivo)
    if not os.path.exists(caminho):
        return None

    with open(caminho, "r", encoding="utf-8") as f:
        soup = BeautifulSoup(f, "html.parser")

    desc = soup.find("div", class_="galleria-info-description")
    if desc:
        return limpar_texto(desc.get_text())

    return None

# === Função principal para extrair conteúdo ===
def extrair_conteudo(filepath):
    with open(filepath, "r", encoding="utf-8") as f:
        soup = BeautifulSoup(f, "html.parser")

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
                prev_elem = elem.find_previous_sibling()
                is_apos_hr = prev_elem and prev_elem.name == "hr"

                if is_legitimo or is_apos_hr:
                    conteudo.append(f"\n-- {texto} --")

        elif elem.name == "img":
            # Lista de imagens irrelevantes para descartar
            IMAGENS_EXCLUIR = [
                "http://intranetdoc.epagri.sc.gov.br/sedimob/img/sedimob_icone_banana_color.png",
                "http://intranetdoc.epagri.sc.gov.br/sedimob/img/sedimob_icone_culturas_color.png",
                "./img/iconeDocumento.png",
                "/sedimob/img/iconeBarraHomeBranco.png",
                "/sedimob/img/iconeEpagriTecMobSemBorda.png",
                "/sedimob/img/iconeVoltarBranco.png"
            ]
            src = elem.get("src", "")
            legenda = ""

            if src:
                parsed = urlparse(src)
                path_encoded = quote(parsed.path)
                src = urlunparse((parsed.scheme, parsed.netloc, path_encoded, parsed.params, parsed.query, parsed.fragment))

            if src not in IMAGENS_EXCLUIR:
                conteudo.append(f"[IMAGEM] {src}")

                # === NOVO: verificar se essa imagem tem galeria associada ===
                a_tag = elem.find_parent("a", href=True)
                if a_tag and "abrirGaleria" in a_tag["href"]:
                    m = re.search(r"abrirGaleria\([^)]*?(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)", a_tag["href"])
                    if m:
                        cd_anexo, cd_estrutura, cd_elemento, nr_anexo = m.groups()
                        legenda_galeria = buscar_legenda_galeria(cd_estrutura, cd_elemento, cd_anexo, nr_anexo)
                        if legenda_galeria:
                            conteudo.append(f"Legenda: {legenda_galeria}")

    return "\n".join(conteudo)

# === Loop principal: processa todos os HTMLs da pasta ===
for nome_arquivo in sorted(os.listdir(entrada_dir), key=lambda x: int(os.path.splitext(x)[0])):
    if nome_arquivo.endswith(".html"):
        caminho = os.path.join(entrada_dir, nome_arquivo)
        texto_extraido = extrair_conteudo(caminho)
        if texto_extraido is None:
            continue

        saida = os.path.join(saida_dir, nome_arquivo.replace(".html", ".txt"))
        with open(saida, "w", encoding="utf-8") as ftxt:
            ftxt.write(texto_extraido)

        print(f"[OK] Texto salvo: {saida}")
