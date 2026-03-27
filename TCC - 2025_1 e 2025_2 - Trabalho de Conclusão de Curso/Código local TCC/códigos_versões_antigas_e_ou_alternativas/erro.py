import pandas as pd

# Lista dos arquivos CSV que você quer analisar
arquivos_csv = [
    'mapeamento_imagens.csv',
    'Planilha_Analise.csv',
    'TabelaConversao.csv'
]

print("--- Verificador de Linhas com Células Vazias ('nan') ---")

for nome_arquivo in arquivos_csv:
    print(f"\n--- Analisando arquivo: {nome_arquivo} ---")
    
    try:
        # Tenta ler com o delimitador padrão (vírgula)
        df = pd.read_csv(nome_arquivo, engine='python')
        
        # Se encontrou poucas colunas (sinal de delimitador errado), tenta com ponto e vírgula
        if df.shape[1] < 2 and ';' in open(nome_arquivo, 'r', encoding='utf-8').readline():
            print("  Delimitador parece não ser vírgula, tentando com ponto e vírgula...")
            df = pd.read_csv(nome_arquivo, delimiter=';', engine='python')

        # Encontra todas as linhas que contêm QUALQUER valor nulo/vazio (NaN)
        linhas_com_nan = df[df.isnull().any(axis=1)]

        if not linhas_com_nan.empty:
            print(f"  Encontradas {len(linhas_com_nan)} linhas com pelo menos uma coluna vazia:")
            # Itera sobre as linhas encontradas para mostrar o número da linha e seu conteúdo
            for index, row in linhas_com_nan.iterrows():
                # O índice do pandas é 0-based, e temos 1 linha de cabeçalho, então somamos 2.
                print(f"\n  - Linha nº: {index + 2}")
                print(f"    Conteúdo: {row.to_dict()}")
        else:
            print("  Nenhuma linha com valores vazios foi encontrada.")

    except FileNotFoundError:
        print(f"  [ERRO] Arquivo não encontrado. Verifique se o nome está correto.")
    except Exception as e:
        print(f"  [ERRO] Não foi possível processar o arquivo. Detalhe: {e}")