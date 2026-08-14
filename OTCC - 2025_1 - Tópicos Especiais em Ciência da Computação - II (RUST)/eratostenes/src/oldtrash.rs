/*
Aluno: Kauan Henrique Werlich
 Programa: Crivo de Eratóstenes sequencial e paralelo.
 Objetivo: Determinar todos os números primos no intervalo [2, n].
 Métodos implementados:
   1. Versão sequencial.
   2. Versão paralela com divisão por blocos utilizando threads independentes.
 
 Estratégia geral:
   - O limite superior n é lido da linha de comando.
   - A raiz quadrada de n define o conjunto de primos básicos necessários para
     crivar o intervalo completo (Teorema: se p é divisor de k, então p ≤ √k).
   - Os primos básicos são obtidos de forma sequencial, pois a faixa é pequena
     quando comparada ao intervalo total.
   - Na versão paralela, o intervalo (√n + 1 ..= n) é dividido em blocos
     de tamanhos iguais; cada bloco é associado a uma thread que marca
     múltiplos dos primos básicos dentro do próprio bloco. Como as threads
     trabalham em fatias disjuntas do vetor, não há necessidade de
     sincronização.
   - Um vetor de u8 é usado como mapa de bits (1 = potencialmente primo,
     0 = composto). A indexação corresponde diretamente ao número natural
     (ex.: índice 17 armazena o estado do número 17).
   - Medições de tempo de execução (em milissegundos) são gravadas no arquivo
     "stats.txt" no formato CSV:
       modo,n,threads,duracao_ms
   - O arquivo pode ser importado posteriormente em Python para análise e
     geração de gráficos.
 
 Limitações práticas:
   - O valor máximo possível para n em um u128 (≈ 3,4×10^38) é inviável
     em termos de memória. O algoritmo aceita esse tipo por completude, mas
     na prática n deve caber em usize, pois a alocação de vetor utiliza o
     índice da plataforma (64 bits em sistemas modernos).
   - Para n maiores que algumas centenas de milhões, recomenda‑se a versão
     segmentada em disco ou algoritmos especializados, fora do escopo deste
     exemplo educacional.
 
 Uso:
   cargo run --release -- <n> <seq|par> [threads]
 Exemplos:
   cargo run --release -- 1000000 seq
   cargo run --release -- 1000000 par 4
 Dependências (Cargo.toml):
   [dependencies]
   crossbeam-utils = "0.8"

   # NÃO salvar (padrão)
cargo run --release -- 1000000 seq

# Salvar em texto
cargo run --release -- 1000000 par 8 --save txt

# Salvar em binário compacto
cargo run --release -- 1000000 par 8 --save bin
 */
#[allow(dead_code)]
use std::env;
use std::fs::OpenOptions;
use std::io::{Write, BufWriter};
use std::time::Instant;

use crossbeam_utils::thread; // fornece threads com escopo seguro

enum SaveFmt { None, Txt, Bin }

/// Gera a lista de primos ≤ limite usando o sieve clássico sequencial.
fn base_primes(limite: usize) -> Vec<usize> {
    let mut marca = vec![true; limite + 1];
    marca[0] = false;
    if limite >= 1 {
        marca[1] = false;
    }
    let raiz = (limite as f64).sqrt() as usize;
    for p in 2..=raiz {
        if marca[p] {
            let mut mult = p * p;
            while mult <= limite {
                marca[mult] = false;
                mult += p;
            }
        }
    }
    marca
        .iter()
        .enumerate()
        .filter_map(|(i, &is_prime)| if is_prime { Some(i) } else { None })
        .collect()
}

/// Versão sequencial completa.
fn sieve_seq(n: usize) -> Vec<u8> {
    let mut marca = vec![1_u8; n + 1];
    if n >= 0 {
        marca[0] = 0;
    }
    if n >= 1 {
        marca[1] = 0;
    }
    let raiz = (n as f64).sqrt() as usize;
    for p in 2..=raiz {
        if marca[p] == 1 {
            let mut mult = p * p;
            while mult <= n {
                marca[mult] = 0;
                mult += p;
            }
        }
    }
    marca
}

/// Versão paralela usando divisão em blocos e threads independentes.
fn sieve_par(n: usize, threads: usize) -> Vec<u8> {
    let raiz = (n as f64).sqrt() as usize;
    let base = base_primes(raiz);

    // Vetor de marcações compartilhado; cada thread manipula uma seção exclusiva.
    let mut marca = vec![1_u8; n + 1];
    marca[0] = 0;
    if n >= 1 {
        marca[1] = 0;
    }

    // Primeira etapa: remover múltiplos até √n (já poderia ser coberta por base).
    for &p in &base {
        let mut mult = p * p;
        while mult <= raiz {
            marca[mult] = 0;
            mult += p;
        }
    }

// Tamanho aproximado de cada fatia que ficará com uma thread
    let intervalo  = n - raiz;
    let chunk_size = (intervalo + threads - 1) / threads; // arredonda pra cima

    crossbeam_utils::thread::scope(|s| {
        // Divide o vetor `[raiz+1 ..= n]` em fatias mutáveis não sobrepostas
        for (i, chunk) in marca[(raiz + 1)..].chunks_mut(chunk_size).enumerate() {
            let ini = raiz + 1 + i * chunk_size;       // primeiro número da fatia
            let fim = ini + chunk.len() - 1;           // último número da fatia
            let base_local = base.clone();             // cópia local da lista de primos

            s.spawn(move |_| {
                for &p in &base_local {
                    // menor múltiplo de `p` dentro da faixa [ini, fim]
                    let mut mult = ((ini + p - 1) / p) * p;
                    if mult < p * p { mult = p * p; }
                    while mult <= fim {
                        chunk[mult - ini] = 0;         // marca como composto
                        mult += p;
                    }
                }
            });
        }
    }).unwrap();

    marca
}

fn gravar_stats(modo: &str, n: usize, threads: usize,
                dur_ms: u128, qtd_primos: usize)
{
    let novo = !std::path::Path::new("stats.txt").exists();   // true se arquivo não existia

    let mut arq = std::fs::OpenOptions::new()
        .create(true)
        .append(true)
        .open("stats.txt")
        .expect("não foi possível abrir stats.txt");

    if novo {
        writeln!(arq, "modo,n,threads,duracao_ms,qtd_primos").unwrap();
    }
    writeln!(arq, "{},{},{},{},{}",
             modo, n, threads, dur_ms, qtd_primos).unwrap();
}


fn save_primes(bits: &[u8], n: usize, modo: &str, th: usize, fmt: &SaveFmt)
    -> std::io::Result<()> {

    if let SaveFmt::None = fmt { return Ok(()); }   // nada a salvar

    let fname = format!("primes_{n}_{modo}_{th}.{}",
                        match fmt { SaveFmt::Txt => "txt", SaveFmt::Bin => "bin", _ => unreachable!() });

    let file = std::fs::File::create(&fname)?;
    let mut buf = BufWriter::new(file);

    match fmt {
        SaveFmt::Txt => {                 // um primo por linha
            for (i, &b) in bits.iter().enumerate().skip(2) {
                if b == 1 { writeln!(buf, "{i}")?; }
            }
        }
        SaveFmt::Bin => buf.write_all(bits)?, // bitset completo
        SaveFmt::None => {}
    }
    Ok(())
}

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() < 3 {
        eprintln!(
            "Uso: {} <n> <seq|par> [threads]\nEx.: {} 1000000 par 4",
            args[0], args[0]
        );
        std::process::exit(1);
    }

    let n: usize = args[1]
        .parse()
        .expect("n deve ser um inteiro não negativo e <= usize::MAX");

    let modo = &args[2];

    let threads: usize = if modo == "par" {
        if args.len() >= 4 {
            args[3].parse().expect("threads deve ser inteiro positivo")
        } else {
            // Se não fornecido, utiliza o número de CPUs lógicas disponíveis.
            std::thread::available_parallelism()
                .map(|n| n.get())
                .unwrap_or(1)
        }
    } else {
        1
    };

    let inicio = Instant::now();

    let resultado = if modo == "seq" {
        sieve_seq(n)
    } else {
        sieve_par(n, threads)
    };
    let qtd_primos = resultado.iter().filter(|&&b| b == 1).count();

    let duracao = inicio.elapsed();
    gravar_stats(modo, n, threads, duracao.as_millis(), qtd_primos);

    println!(
        "Concluído: modo={}, n={}, threads={}, tempo={} ms (stats.txt atualizado)",
        modo,
        n,
        threads,
        duracao.as_millis()
    );
}

#[cfg(test)]
mod tests {
    use super::*;

    // π(n) tabelado para n pequenos — fonte: OEIS A006880.
    const KNOWN_PI: &[(usize, usize)] = &[
        (100, 25),
        (1_000, 168),
        (10_000, 1_229),
        (100_000, 9_592),
        (1_000_000, 78_498),
    ];

    /// Soma dos primos (módulo 2⁶⁴) — checksum rápido.
    fn checksum_u64(bits: &[u8]) -> u64 {
        bits.iter()
            .enumerate()
            .skip(2)                       // ignora 0 e 1
            .fold(0u64, |acc, (i, &b)| if b == 1 {
                acc.wrapping_add(i as u64)
            } else { acc })
    }

    /// Testa a contagem π(n) contra valores tabelados.
    #[test]
    fn counts_match_known_values() {
        for &(n, expected) in KNOWN_PI {
            let bits = sieve_seq(n);
            let got  = bits.iter().filter(|&&b| b == 1).count();
            assert_eq!(got, expected, "π({n}) deveria ser {expected}");
        }
    }

    /// Compara bit a bit a versão sequencial com a paralela.
    #[test]
    fn seq_equals_par_checksum() {
        let n        = 1_000_000;      // rápido o bastante p/ CI
        let threads  = 8;              // ajuste se sua máquina tiver menos

        let seq_bits = sieve_seq(n);
        let par_bits = sieve_par(n, threads);

        // 1. Vetores idênticos
        assert_eq!(seq_bits, par_bits,
            "Sieve seq e par divergem para n={n}");

        // 2. Checksum idêntico (reforço)
        let c_seq = checksum_u64(&seq_bits);
        let c_par = checksum_u64(&par_bits);
        assert_eq!(c_seq, c_par, "Checksums diferentes para n={n}");
    }
}
