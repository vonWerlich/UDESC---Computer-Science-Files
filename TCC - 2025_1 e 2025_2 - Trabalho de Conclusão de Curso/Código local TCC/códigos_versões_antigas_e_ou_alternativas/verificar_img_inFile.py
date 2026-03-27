import base64
from pathlib import Path

# Caminho para o arquivo
nome_arquivo = "aHR0cDovL2ludHJhbmV0ZG9jLmVwYWdyaS5zYy5nb3YuYnIvc2VkaW1vYi9pbWdfZWxlbWVudG8vJTVCMTgzODclNUQlN0I0OTAlN0Ricm9jYS5qcGc=.png"  # nome do arquivo salvo

# Remover a extensão
nome_sem_extensao = Path(nome_arquivo).stem

# Decodificar de volta para a URL original
url_original = base64.urlsafe_b64decode(nome_sem_extensao).decode("utf-8")

print("URL original:", url_original)
