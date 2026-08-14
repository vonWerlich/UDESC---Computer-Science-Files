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



use std::{
    env,
    fs::File,
    io::{BufWriter, Write},
    time::Instant,
};
use bitvec::prelude::*;
use crossbeam_utils::thread;

/// ---------- FLAGS & PARSE SIMPLES ----------------------------------
#[derive(Debug)]
enum SaveFmt {
    None,
    Txt,
    Bin,
}
impl SaveFmt {
    fn from_str(s: &str) -> SaveFmt {
        match s {
            "txt" => SaveFmt::Txt,
            "bin" => SaveFmt::Bin,
            _ => SaveFmt::None,
        }
    }
}

#[derive(Debug)]
struct Args { // Estrutura que representa todos os argumentos fornecidos pela linha de comando.
    n: usize,             // Limite superior da busca de primos
    modo: String,         // Modo de execução: "seq" ou "par"
    threads: usize,       // Número de threads a usar (1 se no sequencial)
    save: SaveFmt,        // Formato de salvamento dos primos encontrados
    show: usize,          // k primeiros/últimos a mostrar
}

fn parse_args() -> Args {
    let a: Vec<String> = env::args().collect();
    if a.len() < 3 {
        eprintln!(
            "Uso: {} <n> <seq|par> [threads] [--save txt|bin] [--show k]",
            a[0]
        );
        std::process::exit(1);
    }
    let n = a[1]
        .parse::<usize>()
        .expect("n deve caber em usize e ser positivo");
    let modo = a[2].clone();
    assert!(modo == "seq" || modo == "par", "modo precisa ser seq ou par");

    let mut threads = 1;
    let mut save = SaveFmt::None;
    let mut show = 0;

    let mut i = 3;
    if modo == "par" {
        threads = if i < a.len() && !a[i].starts_with("--") {
            i += 1;
            a[i - 1]
                .parse::<usize>()
                .expect("threads deve ser inteiro positivo")
        } else {
            std::thread::available_parallelism()
                .map(|n| n.get())
                .unwrap_or(1)
        };
    }
    while i < a.len() {
        match a[i].as_str() {
            "--save" if i + 1 < a.len() => {
                save = SaveFmt::from_str(&a[i + 1]);
                i += 2;
            }
            "--show" if i + 1 < a.len() => {
                show = a[i + 1].parse::<usize>().unwrap_or(0);
                i += 2;
            }
            _ => {
                eprintln!("Argumento não reconhecido: {}", a[i]);
                std::process::exit(1);
            }
        }
    }
    Args {
        n,
        modo,
        threads,
        save,
        show,
    }
}
/// ---------- SIEVE BÁSICOS -----------------------------------------
fn base_primes(lim: usize) -> Vec<usize> {
    let mut m = vec![true; lim + 1];

    m[0] = false;

    if lim >= 1 {
        m[1] = false;
    }
    let r = (lim as f64).sqrt() as usize;
    for p in 2..=r {
        if m[p] {
            let mut mult = p * p;
            while mult <= lim {
                m[mult] = false;
                mult += p;
            }
        }
    }
    m.iter()
        .enumerate()
        .filter_map(|(i, &b)| if b { Some(i) } else { None })
        .collect()
}

/// Implementa o crivo de Eratóstenes de forma sequencial.
/// Retorna um vetor de bits (u8), onde 1 indica que o número é primo.
fn crivo_sequencial(n: usize) -> BitVec {
    let mut bits = bitvec![1; n + 1]; // todos true (potencialmente primos)
    bits.set(0, false);
    if n >= 1 {
        bits.set(1, false);
    }
    let r = (n as f64).sqrt() as usize;
    for p in 2..=r {
        if bits[p] {
            let mut mult = p * p;
            while mult <= n {
                bits.set(mult, false);
                mult += p;
            }
        }
    }
    bits
}

/// Versão paralela do crivo de Eratóstenes.
/// Usa divisão de faixa e threads independentes para marcar múltiplos de primos base.
#[allow(dead_code)]
fn crivo_paralelo(n: usize, threads: usize) -> BitVec {
    let r = (n as f64).sqrt() as usize;
    let base = base_primes(r); // continua usando Vec<usize> para os primos base

    let mut bits = bitvec![1; n + 1];
    bits.set(0, false);
    if n >= 1 {
        bits.set(1, false);
    }

    // marca primos até raiz sequencialmente
    for &p in &base {
        let mut mult = p * p;
        while mult <= r {
            bits.set(mult, false);
            mult += p;
        }
    }

    let interval = n - r;
    let chunk = (interval + threads - 1) / threads;

    // Para manipular fatias de BitVec de forma segura e eficiente, criaremos um vetor de Mutexes (um para cada thread)
    // ou então vamos operar em fatias do BitVec como bits

    // Para evitar problemas de mutabilidade concorrente, vamos criar um vetor de BitVec com fatias para as threads e depois mesclar?

    // Porém, BitVec não permite facilmente mutabilidade concorrente em fatias.
    // Para contornar, podemos usar unsafe ou dividir o BitVec em chunks byte a byte.

    // Alternativamente, fazer o paralelismo em segmentos independentes com mutex para escrever de volta.

    use std::sync::{Arc, Mutex};
    let bits = Arc::new(Mutex::new(bits));

    thread::scope(|s| {
        for (_idx, start) in (r + 1..=n).step_by(chunk).enumerate() {
            let bits = Arc::clone(&bits);
            let end = (start + chunk - 1).min(n);
            let base = base.clone();

            s.spawn(move |_| {
                let size = end - start + 1;
                let mut segment = bitvec![1; size];

                for &p in &base {
                    let mut mult = ((start + p - 1) / p) * p;
                    if mult < p * p {
                        mult = p * p;
                    }
                    while mult <= end {
                        segment.set(mult - start, false);
                        mult += p;
                    }
                }

                // copia segmento para o vetor principal
                let mut bits_lock = bits.lock().unwrap();
                for i in 0..size {
                    bits_lock.set(start + i, segment[i]);
                }
            });
        }
    }).unwrap();

    Arc::try_unwrap(bits).unwrap().into_inner().unwrap()
}

#[allow(dead_code)]
fn crivo_paralelo_segmentado(n: usize, threads: usize) -> Vec<u8> {
    let r = (n as f64).sqrt() as usize;
    let base = base_primes(r);

    let mut sieve = vec![1u8; n + 1];
    sieve[0] = 0;
    if n >= 1 {
        sieve[1] = 0;
    }

    // Marca primos até r sequencialmente
    for &p in &base {
        let mut mult = p * p;
        while mult <= r {
            sieve[mult] = 0;
            mult += p;
        }
    }

    // Parâmetros do segmento - ajuste para caber na sua memória/cache
    let segment_size = 10_000_000usize.min(n - r); 

    // Gerar segmentos (start, end)
    let mut segments = Vec::new();
    let mut start = r + 1;
    while start <= n {
        let end = (start + segment_size - 1).min(n);
        segments.push((start, end));
        start = end + 1;
    }

    use std::sync::{Arc, Mutex};
    let base = Arc::new(base);
    let sieve_arc = Arc::new(Mutex::new(sieve));

    crossbeam_utils::thread::scope(|scope| {
        let mut handles = Vec::new();
        for chunk in segments.chunks(threads) {
            // para cada "lote" com até `threads` segmentos, cria threads para cada segmento
            for &(seg_start, seg_end) in chunk {
                let base = Arc::clone(&base);
                let sieve_arc = Arc::clone(&sieve_arc);

                let handle = scope.spawn(move |_| {
                    let size = seg_end - seg_start + 1;
                    let mut segment = vec![1u8; size];

                    // Marca múltiplos dos primos base dentro do segmento
                    for &p in base.iter() {
                        let mut mult = ((seg_start + p - 1) / p) * p;
                        if mult < p * p {
                            mult = p * p;
                        }
                        while mult <= seg_end {
                            segment[mult - seg_start] = 0;
                            mult += p;
                        }
                    }

                    // Copia o segmento marcado para o vetor principal (com lock)
                    let mut sieve = sieve_arc.lock().unwrap();
                    for i in 0..size {
                        sieve[seg_start + i] = segment[i];
                    }
                });
                handles.push(handle);
            }
            // Espera essas threads finalizarem antes de criar o próximo lote
            for handle in handles.drain(..) {
                handle.join().unwrap();
            }
        }
    }).unwrap();

    // Retorna o vetor principal atualizado
    Arc::try_unwrap(sieve_arc).unwrap().into_inner().unwrap()
}


/// ---------- UTILIDADES --------------------------------------------

/// Calcula um checksum simples da lista de primos:
/// Soma todos os índices marcados como primos, com overflow permitido (mod 2^64).
/// Útil para verificar se duas execuções (seq vs par) produziram o mesmo conjunto.
fn checksum(bits: &BitVec) -> u64 {
    bits.iter()
        .enumerate()
        .skip(2)
        .fold(0u64, |acc, (i, b)| if *b { acc.wrapping_add(i as u64) }
        else { acc })
}

fn save_primes(bits: &BitVec, args: &Args) -> std::io::Result<()> {
    if matches!(args.save, SaveFmt::None) {
        return Ok(());
    }
    let fname = format!(
        "primes_{}_{}_{}.{}",
        args.n,
        args.modo,
        args.threads,
        match args.save {
            SaveFmt::Txt => "txt",
            SaveFmt::Bin => "bin",
            SaveFmt::None => unreachable!(),
        }
    );
    let file = File::create(fname)?;
    let mut buf = BufWriter::new(file);

use std::io::Write;

    match args.save {
        SaveFmt::Txt => {
            for (i, b) in bits.iter().enumerate().skip(2) {
                if *b {
                    writeln!(buf, "{}", i)?;
                }
            }
        }
        SaveFmt::Bin => {
            let raw = bits.as_raw_slice();
            // Alinha o slice de usize para u8 (bytes)
            let (_, bytes, _) = unsafe { raw.align_to::<u8>() };
            buf.write_all(bytes)?;
        }
        SaveFmt::None => {}
    }

    Ok(())
}

/// Salva as estatísticas da execução no arquivo `stats.csv`
/// Cada linha contém: modo, n, threads, tempo (ms), pi(n), checksum, primos/s
fn append_stats(args: &Args, ms: u128, q: usize, cksum: u64) -> std::io::Result<()> {
    let new_file = !std::path::Path::new("stats.csv").exists();
    let mut f = BufWriter::new(File::options().create(true).append(true).open("stats.csv")?);
    if new_file {
        writeln!(f, "modo,n,threads,ms,pi,checksum,primos_por_seg")?;
    }
    let pps = if ms > 0 { (q as u128 * 1000 / ms) as u64 } else { 0 };
    writeln!(
        f,
        "{},{},{},{},{},{},{}",
        args.modo, args.n, args.threads, ms, q, cksum, pps
    )?;
    Ok(())
}

fn show_sample(bits: &BitVec, k: usize) {
    if k == 0 {
        return;
    }
    let mut first = Vec::with_capacity(k);
    let mut last = Vec::with_capacity(k);

    for (i, b) in bits.iter().enumerate().skip(2) {
        if *b {
            if first.len() < k {
                first.push(i);
            }
            last.push(i);
            if last.len() > k {
                last.remove(0);
            }
        }
    }
    println!("Primeiros {k}: {:?}", first);
    println!("Últimos  {k}: {:?}", last);
}
/// ---------- MAIN ---------------------------------------------------

fn main() {
    let args = parse_args();

    println!("=============================");
    println!("Crivo de Eratóstenes em Rust");
    println!("Modo: {}", args.modo);
    println!("Limite superior (n): {}", args.n);
    println!("Threads: {}", args.threads);
    println!("=============================\n");

    println!("Iniciando cálculo dos primos...");

    let t0 = Instant::now();
    let bits = if args.modo == "seq" {
        println!("Executando versão SEQUENCIAL...");
        crivo_sequencial(args.n)
    } else {
        println!("Executando versão PARALELA com {} threads...", args.threads);
        crivo_paralelo(args.n, args.threads)
        //crivo_paralelo_segmentado(args.n, args.threads)
    };
    let ms = t0.elapsed().as_millis();

    let pi = bits.iter().filter(|b| **b).count();
    let cksum = checksum(&bits);

    println!("\nCálculo concluído!");
    println!("Número de primos encontrados π(n) = {}", pi);
    println!("Checksum = {}", cksum);
    println!("Tempo total: {} ms", ms);

    append_stats(&args, ms, pi, cksum).expect("Falha ao gravar stats");
    println!("Estatísticas salvas em stats.csv");

    //println!("DEBUG: bits[2..20] = {:?}", &bits[2..20]); // teste se os bits estão certos

    save_primes(&bits, &args).expect("Falha ao salvar primos");
    println!("Primos salvos em arquivo");

    show_sample(&bits, args.show);
    println!("=============================");
}


/*# Sequencial, não grava primos, mostra 10 no console
cargo run --release -- 1000000 seq --show 10

# Paralelo com 8 threads, grava bitset, não mostra nada
cargo run --release -- 1000000 par 8 --save bin */


/// ---------- TESTES -------------------------------------------------
#[cfg(test)]
mod tests {
    use super::*;

    const TABELA: &[(usize, usize)] = &[
        (100, 25),
        (1_000, 168),
        (10_000, 1_229),
        (100_000, 9_592),
        (1_000_000, 78_498),
    ];

    /// Teste básico: compara π(n) para valores tabelados e conhecidos
    #[test]
    fn pi_tabelado() {
        for &(n, pi_ref) in TABELA {
            assert_eq!(crivo_sequencial(n).iter().filter(|b| **b).count(), pi_ref);
        }
    }

    /// Testa se a versão paralela produz o mesmo resultado que a sequencial
    #[test]
    fn seq_vs_par() {
        let n = 1_000_000;
        let seq = crivo_sequencial(n);
        let par = crivo_paralelo(n, 8);
        assert_eq!(seq, par);
    }

    /// Soma dos primos (mod 2^64) deve coincidir entre seq e par.
    #[test]
    fn checksum_match() {
        let n = 3_000_000;
        let seq = crivo_sequencial(n);
        let par = crivo_paralelo(n, 8);

        let cksum_seq = checksum(&seq);
        let cksum_par = checksum(&par);

        assert_eq!(cksum_seq, cksum_par);
    }

}


/*Comandos usados para criar os gráficos:
# === SEQUENCIAL ===
cargo run --release -- 100000 seq
cargo run --release -- 1000000 seq
cargo run --release -- 10000000 seq
cargo run --release -- 30000000 seq
cargo run --release -- 100000000 seq
cargo run --release -- 300000000 seq
cargo run --release -- 1000000000 seq
cargo run --release -- 3000000000 seq
cargo run --release -- 5000000000 seq
cargo run --release -- 10000000000 seq

# === PARALELO COM 2 THREADS ===
cargo run --release -- 100000 par 2
cargo run --release -- 1000000 par 2
cargo run --release -- 10000000 par 2
cargo run --release -- 30000000 par 2
cargo run --release -- 100000000 par 2
cargo run --release -- 300000000 par 2
cargo run --release -- 1000000000 par 2
cargo run --release -- 3000000000 par 2
cargo run --release -- 5000000000 par 2
cargo run --release -- 10000000000 par 2

# === PARALELO COM 4 THREADS ===
cargo run --release -- 100000 par 4
cargo run --release -- 1000000 par 4
cargo run --release -- 10000000 par 4
cargo run --release -- 30000000 par 4
cargo run --release -- 100000000 par 4
cargo run --release -- 300000000 par 4
cargo run --release -- 1000000000 par 4
cargo run --release -- 3000000000 par 4
cargo run --release -- 5000000000 par 4
cargo run --release -- 10000000000 par 4

# === PARALELO COM 8 THREADS ===
cargo run --release -- 100000 par 8
cargo run --release -- 1000000 par 8
cargo run --release -- 10000000 par 8
cargo run --release -- 30000000 par 8
cargo run --release -- 100000000 par 8
cargo run --release -- 300000000 par 8
cargo run --release -- 1000000000 par 8
cargo run --release -- 3000000000 par 8
cargo run --release -- 5000000000 par 8
cargo run --release -- 10000000000 par 8 

# === PARALELO COM 16 THREADS ===
cargo run --release -- 100000 par 16
cargo run --release -- 1000000 par 16
cargo run --release -- 10000000 par 16
cargo run --release -- 30000000 par 16
cargo run --release -- 100000000 par 16
cargo run --release -- 300000000 par 16
cargo run --release -- 1000000000 par 16
cargo run --release -- 3000000000 par 16
cargo run --release -- 5000000000 par 16
cargo run --release -- 10000000000 par 16
*/