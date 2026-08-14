///  Aluno: Kauan Henrique Werlich
///  Crivo de Eratóstenes com Segmentação: versão sequencial e paralela

use std::{
    env,
    fs::File,
    io::{BufWriter, Write},
    time::Instant,
};

use crossbeam_utils::thread;
use bitvec::prelude::*;


#[derive(Debug)]
enum SaveFmt { // Enum que indica em qual formato salvar os primos encontrados
    None, // Não salva
    Txt,
    Bin,
}

impl SaveFmt { // Implementação para converter string ("txt", "bin", etc) para SaveFmt
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

/// Função que lê os argumentos passados pela linha de comando
fn parse_args() -> Args { 
    let a: Vec<String> = env::args().collect();
    if a.len() < 3 {
        eprintln!("Uso: {} <n> <seq|par> [threads] [--save txt|bin] [--show k]", a[0]);
        std::process::exit(1);
    }
    let n = a[1].parse::<usize>().expect("n deve ser usize e positivo");
    let modo = a[2].clone();
    assert!(modo == "seq" || modo == "par", "modo deve ser seq ou par");

    let mut threads = 1;
    let mut save = SaveFmt::None;
    let mut show = 0;
    let mut i = 3;

    // Se modo é paralelo, verifica se o usuário informou quantas threads usar
    if modo == "par" {
        threads = if i < a.len() && !a[i].starts_with("--") {
            i += 1;
            a[i - 1].parse().expect("threads deve ser inteiro positivo")
        } else {
            // Se não informou, usa número de threads disponíveis no sistema
            std::thread::available_parallelism().map(|n| n.get()).unwrap_or(1)
        };
    }

    // Processa argumentos opcionais: --save e --show
    while i < a.len() {
        match a[i].as_str() {
            "--save" if i + 1 < a.len() => {
                save = SaveFmt::from_str(&a[i + 1]);
                i += 2;
            }
            "--show" if i + 1 < a.len() => {
                show = a[i + 1].parse().unwrap_or(0);
                i += 2;
            }
            _ => {
                eprintln!("Argumento não reconhecido: {}", a[i]);
                std::process::exit(1);
            }
        }
    }

    Args { n, modo, threads, save, show }
}

fn base_primes(limit: usize) -> Vec<usize> {
    let mut sieve = vec![true; limit + 1];
    sieve[0] = false;
    if limit >= 1 { sieve[1] = false; }
    let sqrt = (limit as f64).sqrt() as usize;
    for p in 2..=sqrt {
        if sieve[p] {
            let mut multiple = p * p;
            while multiple <= limit {
                sieve[multiple] = false;
                multiple += p;
            }
        }
    } // Converte o vetor de booleanos em vetor de índices que são primos
    sieve.iter().enumerate()
        .filter_map(|(i, &b)| if b { Some(i) } else { None })
        .collect()
}

/// Versão paralela segmentada do crivo de Eratóstenes
/// Divide o intervalo em blocos (segmentos) e cada thread processa alguns segmentos
fn crivo_segmentado(n: usize, threads: usize) -> Vec<usize> {
    let segment_size = 1_000_000; // Tamanho de cada bloco
    let sqrt_n = (n as f64).sqrt() as usize;
    let base = base_primes(sqrt_n); // base_primes retorna Vec<usize> com todos os primos até sqrt(n)

    let mut all_primes = base.clone(); // guardar todos os primos encontrados

    let chunk_count = ((n - sqrt_n) + segment_size - 1) / segment_size; // Número de segmentos

    let mut results = vec![Vec::new(); threads]; // Vetor para guardar resultados parciais de cada thread

    thread::scope(|s| {
        for (i, result_slot) in results.iter_mut().enumerate() {
            let base = base.clone();
            s.spawn(move |_| {
                let mut local = Vec::new();
                for chunk_id in (i..chunk_count).step_by(threads) {
                    let low = sqrt_n + 1 + chunk_id * segment_size;
                    if low > n {
                        break;
                    }
                    let high = (low + segment_size - 1).min(n);
                    
                    // Cria um bitvec para marcar os números primos no intervalo [low, high]
                    let mut is_prime = bitvec![1; high - low + 1];

                    // Marca múltiplos de cada primo base como não primo
                    for &p in &base {
                        let mut start = ((low + p - 1) / p) * p;
                        if start < p * p {
                            start = p * p;
                        }
                        for j in (start..=high).step_by(p) {
                            is_prime.set(j - low, false);

                        }
                    }
                    for (j, b) in is_prime.iter().enumerate() {
                        if *b {
                            local.push(low + j);
                        }
                    }

                }
                *result_slot = local;
            });
        }
    }).unwrap();

    for local_primes in results { // Junta os resultados de todas as threads
        all_primes.extend(local_primes);
    }

    all_primes.sort_unstable(); // Ordena (opcional)
    all_primes
}

/// Versão sequencial do crivo de Eratóstenes usando bitvec
fn crivo_sequencial(n: usize) -> Vec<usize> {
    let mut bits = bitvec![1; n + 1];
    bits.set(0, false); // 0 não é primo
    if n >= 1 { bits.set(1, false); } // 1 também não é primo
    let r = (n as f64).sqrt() as usize;
    for p in 2..=r {
        if bits[p] {
            let mut mult = p * p;
            while mult <= n {
                bits.set(mult, false); // marca os múltiplos como não primos
                mult += p;
            }
        }
    }
    bits.iter().enumerate() //Cria um iterador sobre todos os bits, na ordem
        .filter_map(|(i, b)| if *b { Some(i) } else { None })
        .collect() //Retorna uma Vec<usize> com todos os números primos até n.
}

// Salva os primos encontrados em arquivo .txt ou .bin
fn save_primes(primes: &[usize], args: &Args) -> std::io::Result<()> {
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

    match args.save {
        SaveFmt::Txt => {
            for &p in primes {
                write!(buf, "{}\r\n", p)?;
            }
        }
        SaveFmt::Bin => {
            for &p in primes {
                buf.write_all(&(p as u64).to_le_bytes())?;
            }
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

fn main() {
    let args = parse_args();

    println!("Iniciando cálculo até {} (modo: {}, threads: {})", args.n, args.modo, args.threads);
    let t0 = Instant::now();
    let primes = if args.modo == "seq" {
        crivo_sequencial(args.n)
    } else {
        crivo_segmentado(args.n, args.threads)
    };
    let ms = t0.elapsed().as_millis();

    let pi = primes.len();
    let cksum: u64 = primes.iter().map(|&p| p as u64).fold(0, |acc, x| acc.wrapping_add(x));

    println!("\nCálculo concluído!");
    println!("Número de primos encontrados π(n) = {}", pi);
    println!("Checksum: {}", cksum);
    println!("Tempo: {} ms", ms);

    append_stats(&args, ms, pi, cksum).expect("Falha ao gravar stats");
    println!("Estatísticas salvas em stats.csv");

    //println!("DEBUG: bits[2..20] = {:?}", &bits[2..20]); // teste se os bits estão certos

    let _ = save_primes(&primes, &args);
    if args.show > 0 {
        println!("Primeiros {:?}", &primes[..args.show.min(primes.len())]);
        println!("Últimos  {:?}", &primes[primes.len().saturating_sub(args.show)..]);
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    /// Teste básico: compara o número de primos em (n) para valores tabelados e conhecidos
    #[test]
    fn pi_tabelado() {
        let tabela = [
            (100, 25),
            (1_000, 168),
            (10_000, 1_229),
            (100_000, 9_592),
            (1_000_000, 78_498),
        ];
        for (n, expected) in tabela {
            let primos = crivo_segmentado(n, 1);
            assert_eq!(primos.len(), expected);
        }
    }

    /// Testa se a versão paralela produz o mesmo resultado que a sequencial
    #[test]
    fn seq_vs_par() {
        let n = 1_000_000;
        let seq = crivo_segmentado(n, 1);
        let par = crivo_segmentado(n, 4);
        assert_eq!(seq, par);
    }

    /// checksum deve coincidir entre seq e par.
    #[test]
    fn checksum_match() {
        let n = 3_000_000;
        let seq = crivo_segmentado(n, 1);
        let par = crivo_segmentado(n, 4);

        fn checksum(v: &[usize]) -> u64 {
            v.iter().fold(0u64, |acc, &x| acc.wrapping_add(x as u64))
        }

        assert_eq!(checksum(&seq), checksum(&par));
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