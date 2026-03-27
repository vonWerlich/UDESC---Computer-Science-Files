import os
import csv

# --- CONFIGURAÇÃO ---
# Especifique a pasta onde os arquivos CSV gerados estão localizados.
PASTA_DOS_CSVS = "relatorios_csv"

def remover_linhas_duplicadas():
    """
    Percorre todos os arquivos .csv em uma pasta e remove as linhas duplicadas
    de cada um, salvando o resultado no próprio arquivo.
    """
    if not os.path.isdir(PASTA_DOS_CSVS):
        print(f"[ERRO] O diretório '{PASTA_DOS_CSVS}' não foi encontrado.")
        print("Por favor, execute o script principal primeiro para gerar os relatórios.")
        return

    print(f"Iniciando a verificação de linhas duplicadas na pasta '{PASTA_DOS_CSVS}'...")
    total_arquivos_processados = 0

    # Lista todos os arquivos na pasta especificada
    for nome_arquivo in os.listdir(PASTA_DOS_CSVS):
        if nome_arquivo.lower().endswith('.csv'):
            caminho_completo = os.path.join(PASTA_DOS_CSVS, nome_arquivo)
            total_arquivos_processados += 1
            
            try:
                # Lê todas as linhas do arquivo
                with open(caminho_completo, 'r', newline='', encoding='utf-8') as f:
                    leitor = csv.reader(f)
                    cabecalho = next(leitor)  # Salva o cabeçalho
                    linhas_originais = list(leitor)

                # Usa um set para identificar as linhas únicas de forma eficiente
                # (tuplas são usadas porque listas não podem ser adicionadas a sets)
                linhas_vistas = set()
                linhas_unicas = []
                for linha in linhas_originais:
                    tupla_linha = tuple(linha)
                    if tupla_linha not in linhas_vistas:
                        linhas_vistas.add(tupla_linha)
                        linhas_unicas.append(linha)
                
                # Compara o número de linhas antes e depois da limpeza
                if len(linhas_originais) == len(linhas_unicas):
                    print(f"- '{nome_arquivo}': Nenhuma linha duplicada encontrada.")
                else:
                    # Se houver duplicatas, reescreve o arquivo com os dados limpos
                    with open(caminho_completo, 'w', newline='', encoding='utf-8') as f:
                        escritor = csv.writer(f)
                        escritor.writerow(cabecalho)
                        escritor.writerows(linhas_unicas)
                    
                    linhas_removidas = len(linhas_originais) - len(linhas_unicas)
                    print(f"- '{nome_arquivo}': {linhas_removidas} linha(s) duplicada(s) foram removidas.")

            except Exception as e:
                print(f"[ERRO] Falha ao processar o arquivo '{nome_arquivo}': {e}")

    if total_arquivos_processados == 0:
        print("Nenhum arquivo .csv foi encontrado para processar.")

    print("\nProcesso de limpeza concluído.")


# --- Execução do Script ---
if __name__ == "__main__":
    remover_linhas_duplicadas()