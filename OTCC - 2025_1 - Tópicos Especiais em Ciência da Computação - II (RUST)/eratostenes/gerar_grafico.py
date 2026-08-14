import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os

print("Diretório atual de execução:", os.getcwd())

# Lê o CSV
df = pd.read_csv("stats.csv")

# Filtra apenas entradas válidas
df = df[(df["n"] > 0) & (df["ms"] > 0)]

# Cria coluna combinada para legenda
df["modo_threads"] = df.apply(lambda row: f"{row['modo']}_{row['threads']}", axis=1)

# Define estilos e marcadores personalizados
sns.set(style="whitegrid")
markers = {
    "seq_1": "o",      # bolinha
    "par_2": "^",      # triângulo
    "par_4": "s",      # quadrado
    "par_8": "*",      # estrela
    "par_16": "X",     # cruz
}

palette = {
    "seq_1": "#1f77b4",   # azul
    "par_2": "#ff7f0e",   # laranja
    "par_4": "#2ca02c",   # verde
    "par_8": "#d62728",   # vermelho
    "par_16": "#9467bd",  # roxo
}

# --- GRÁFICO 1: Tempo ---
plt.figure(figsize=(10, 6))
for modo_thread, group in df.groupby("modo_threads"):
    sns.lineplot(
        data=group,
        x="n",
        y="ms",
        label=modo_thread,
        marker=markers.get(modo_thread, "o"),
        color=palette.get(modo_thread),
    )
plt.xscale("log")
plt.title("Tempo de Execução (ms) vs Tamanho n")
plt.xlabel("n (limite superior)")
plt.ylabel("Tempo (ms)")
plt.legend(title="Modo_Threads")
plt.tight_layout()
plt.savefig("tempo_vs_n_log.png")
plt.show()

# --- GRÁFICO 2: Primos por segundo ---
plt.figure(figsize=(10, 6))
for modo_thread, group in df.groupby("modo_threads"):
    sns.lineplot(
        data=group,
        x="n",
        y="primos_por_seg",
        label=modo_thread,
        marker=markers.get(modo_thread, "o"),
        color=palette.get(modo_thread),
    )
plt.xscale("log")
plt.title("Eficiência: Primos por Segundo vs n")
plt.xlabel("n (limite superior)")
plt.ylabel("Primos por Segundo")
plt.legend(title="Modo_Threads")
plt.tight_layout()
plt.savefig("eficiencia_vs_n_log.png")
plt.show()

# --- GRÁFICO 3: Speedup ---
seq_df = df[df["modo"] == "seq"][["n", "ms"]].rename(columns={"ms": "ms_seq"})
par_df = df[df["modo"] == "par"][["n", "threads", "ms"]].rename(columns={"ms": "ms_par"})

speedup_df = par_df.merge(seq_df, on="n")
speedup_df["speedup"] = speedup_df["ms_seq"] / speedup_df["ms_par"]

plt.figure(figsize=(10, 6))
for t, group in speedup_df.groupby("threads"):
    sns.lineplot(
        data=group,
        x="n",
        y="speedup",
        label=f"{t} threads",
        marker=markers.get(f"par_{t}", "o"),
        color=palette.get(f"par_{t}"),
    )
plt.xscale("log")
plt.title("Speedup vs n para diferentes threads")
plt.xlabel("n")
plt.ylabel("Speedup (tempo sequencial / tempo paralelo)")
plt.legend(title="Threads")
plt.tight_layout()
plt.savefig("speedup_vs_n_threads_log.png")
plt.show()
