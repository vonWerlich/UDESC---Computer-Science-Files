import pandas as pd

# --- Nomes dos arquivos ---
# Arquivo gerado pelo seu script original
ARQUIVO_BASE = 'mapeamento_final_com_descricoes.csv'

# Arquivo que você precisa criar com as descrições da galeria
ARQUIVO_GALERIA = 'descricoes_galeria.csv'

# Arquivo final que será gerado
ARQUIVO_SAIDA = 'mapeamento_final_com_descricoes+galerias.csv'

print("Iniciando a adição da coluna de descrição da galeria...")

try:
    # --- Passo 1: Carregar os arquivos CSV ---
    # Carrega o seu CSV principal, que já contém a coluna 'descricao'
    df_base = pd.read_csv(ARQUIVO_BASE)
    print(f"'{ARQUIVO_BASE}' carregado com sucesso. ({len(df_base)} linhas)")

    # Carrega o novo arquivo com as descrições da galeria
    df_galeria = pd.read_csv(ARQUIVO_GALERIA)
    print(f"'{ARQUIVO_GALERIA}' carregado com sucesso. ({len(df_galeria)} linhas)")

    # Verificar se as colunas necessárias existem
    if 'url_original' not in df_base.columns:
        raise ValueError(f"A coluna 'url_original' não foi encontrada em '{ARQUIVO_BASE}'.")
    if 'url_original' not in df_galeria.columns or 'descricao_galeria' not in df_galeria.columns:
        raise ValueError(f"O arquivo '{ARQUIVO_GALERIA}' deve conter as colunas 'url_original' e 'descricao_galeria'.")

    # --- Passo 2: Adicionar a nova coluna ---
    # Usamos 'merge' para unir os dois dataframes com base na 'url_original'.
    # 'how='left'' garante que todas as linhas do arquivo original sejam mantidas.
    df_final = pd.merge(df_base, df_galeria, on='url_original', how='left')

    # Preencher com texto vazio os links que não tiverem uma descrição de galeria correspondente
    df_final['descricao_galeria'].fillna('', inplace=True)
    
    # --- Passo 3: Salvar o resultado ---
    df_final.to_csv(ARQUIVO_SAIDA, index=False, encoding='utf-8-sig')

    descricoes_adicionadas = df_final[df_final['descricao_galeria'] != ''].shape[0]

    print("\n--- PROCESSO CONCLUÍDO ---")
    print(f"Arquivo final '{ARQUIVO_SAIDA}' foi gerado com sucesso!")
    print(f"Total de linhas no arquivo: {len(df_final)}")
    print(f"Descrições de galeria encontradas e adicionadas: {descricoes_adicionadas}")


except FileNotFoundError as e:
    print(f"\nERRO: Arquivo não encontrado!")
    print(f"Verifique se o arquivo '{e.filename}' está na mesma pasta que o script.")

except ValueError as e:
    print(f"\nERRO: Problema com as colunas do arquivo CSV.")
    print(e)

except Exception as e:
    print(f"\nOcorreu um erro inesperado: {e}")