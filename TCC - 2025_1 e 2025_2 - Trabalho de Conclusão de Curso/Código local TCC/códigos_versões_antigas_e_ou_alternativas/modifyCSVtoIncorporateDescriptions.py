import pandas as pd

# --- Nomes dos arquivos de entrada e saída ---
ARQUIVO_MAPEAMENTO = 'mapeamento_imagens.csv'
ARQUIVO_ANALISE = 'Planilha_Analise.csv'
ARQUIVO_CONVERSAO = 'TabelaConversao.csv'
ARQUIVO_SAIDA = 'mapeamento_final_com_descricoes.csv'

print("Iniciando processo final de união de dados...")
print("Usando vírgula como delimitador para todos os arquivos.")

try:
    # --- Passo 1: Carregar os três arquivos CSV ---
    # Usando o engine='python', que é mais robusto para arquivos CSV com formatação irregular.
    df_mapa = pd.read_csv(ARQUIVO_MAPEAMENTO, engine='python')
    print(f"'{ARQUIVO_MAPEAMENTO}' carregado. Formato: {df_mapa.shape[0]} linhas, {df_mapa.shape[1]} colunas.")

    df_analise = pd.read_csv(ARQUIVO_ANALISE, engine='python')
    print(f"'{ARQUIVO_ANALISE}' carregado. Formato: {df_analise.shape[0]} linhas, {df_analise.shape[1]} colunas.")

    df_conversao = pd.read_csv(ARQUIVO_CONVERSAO, engine='python')
    print(f"'{ARQUIVO_CONVERSAO}' carregado. Formato: {df_conversao.shape[0]} linhas, {df_conversao.shape[1]} colunas.")

    # --- Passo 2: Unir a planilha de análise com a de conversão ---
    # Junção entre 'Identificação Kauan' e 'cognome'
    df_descricoes_completas = pd.merge(
        df_analise,
        df_conversao,
        left_on='Identificação Kauan',
        right_on='cognome',
        how='left'
    )
    print("Planilhas de análise e conversão unidas com sucesso.")
    
    # Manter apenas as colunas-chave para a próxima etapa
    df_descricoes = df_descricoes_completas[['url_original', 'Descrição']].dropna(subset=['url_original'])
    
    # --- Passo 3: Unir o mapeamento principal com as descrições ---
    # A chave é a 'url_original'
    df_final = pd.merge(df_mapa, df_descricoes, on='url_original', how='left')
    print("Descrições adicionadas ao mapeamento principal.")
    
    # --- Passo 4: Limpeza final ---
    df_final.rename(columns={'Descrição': 'descricao'}, inplace=True)
    df_final['descricao'].fillna('', inplace=True)
    df_final = df_final[['id', 'novo_nome', 'url_original', 'descricao']]
    
    # --- Passo 5: Salvar o resultado ---
    df_final.to_csv(ARQUIVO_SAIDA, index=False, encoding='utf-8-sig')
    
    descricoes_encontradas = df_final[df_final['descricao'] != ''].shape[0]
    
    print("\n--- PROCESSO CONCLUÍDO ---")
    print(f"Arquivo final '{ARQUIVO_SAIDA}' foi gerado com sucesso!")
    print(f"Total de linhas no arquivo final: {len(df_final)}")
    print(f"Descrições que foram encontradas e adicionadas: {descricoes_encontradas}")

except FileNotFoundError as e:
    print(f"\n[ERRO] Arquivo não encontrado: {e.filename}")
except KeyError as e:
    print(f"\n[ERRO DE COLUNA] A coluna {e} não foi encontrada.")
    print("Verifique se o nome da coluna no arquivo CSV está escrito exatamente como no script.")
except Exception as e:
    print(f"\n[ERRO] Ocorreu um erro inesperado durante o processamento.")
    print(f"Detalhe do erro: {e}")