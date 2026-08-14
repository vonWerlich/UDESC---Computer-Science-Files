// Exercício 5 Disciplina Rust
// Aluno: Kauan Henrique Werlich

use std::collections::{BinaryHeap, HashMap};
use std::fs::{self, File};
use std::path::Path;
use std::io::{BufReader, BufWriter, Read, Write};
use std::env;

// Huffman tree
#[derive(Debug)]
#[allow(dead_code)]
pub enum Huffman {
    Leaf { c: char, freq: u32 },
    Node { freq: u32, left: Box<Huffman>, right: Box<Huffman> },
}

// Heap node para construção da árvore
struct HeapNode {
    freq: u32,
    order: usize, //desempate
    tree: Box<Huffman>,
}

impl PartialEq for HeapNode {
    fn eq(&self, other: &Self) -> bool {
        self.freq == other.freq && self.order == other.order
    }
}
impl Eq for HeapNode {}
impl PartialOrd for HeapNode {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        Some(self.cmp(other))
    }
}
impl Ord for HeapNode {
    fn cmp(&self, other: &Self) -> std::cmp::Ordering {
        // comparar freq ascendente, desempatar por ordem ascendente, depois inverter
        // para que BinaryHeap (max-heap) trate menor frequência como maior prioridade.
        self.freq
            .cmp(&other.freq)
            .then_with(|| other.order.cmp(&self.order))
            .reverse()
    }
}

// Gerar códigos de Huffman  // cria o dicionário
pub fn gerar_codigos(huff: &Huffman, prefixo: Vec<bool>, mapa: &mut HashMap<char, Vec<bool>>) {
    match huff {
        Huffman::Leaf { c, .. } => {
            mapa.insert(*c, prefixo);
        }
        Huffman::Node { left, right, .. } => {
            let mut esq = prefixo.clone();
            esq.push(false);
            gerar_codigos(left, esq, mapa);
            let mut dir = prefixo;
            dir.push(true);
            gerar_codigos(right, dir, mapa);
        }
    }
}

// Compactar arquivo
fn compactar(caminho_entrada: &str, caminho_saida: &str) {
    // leio todo texto em String; read_to_string assume UTF-8. Se arquivo contiver bytes inválidos, erro.
    let mut arquivo = File::open(caminho_entrada).expect("Erro ao abrir arquivo de entrada");
    let mut conteudo = String::new();
    // ownership de conteudo: String cresce conforme lê UTF-8 validado
    arquivo.read_to_string(&mut conteudo).expect("Erro ao ler");

    if conteudo.is_empty() {
        // Cria um arquivo .huff vazio
        let _ = File::create(caminho_saida);
        return;
    }

    // conto frequência de cada char Unicode scalar (iterador .chars() coopera com multibyte UTF-8)
    let mut freq_map = HashMap::new();
    for c in conteudo.chars() {
        *freq_map.entry(c).or_insert(0) += 1;
    }

    let mut caracteres: Vec<char> = freq_map.keys().cloned().collect();
    caracteres.sort();

    let mut heap = BinaryHeap::new();
    for (i, &c) in caracteres.iter().enumerate() {
        heap.push(HeapNode {
            freq: freq_map[&c],
            order: i,
            tree: Box::new(Huffman::Leaf { c, freq: freq_map[&c] }),
        });
    }

    // combinar nós até sobrar um: cada iteração reduz tamanho do heap em 1
    let mut ordem = caracteres.len();
    while heap.len() > 1 {
        let x = heap.pop().unwrap();
        let y = heap.pop().unwrap();
        let freq = x.freq + y.freq;
        let node = Box::new(Huffman::Node {
            freq,
            left: x.tree,
            right: y.tree,
        });
        heap.push(HeapNode {
            freq,
            order: ordem,
            tree: node,
        });
        ordem += 1;
    }

    let arvore = heap.pop().unwrap().tree;

    let mut codigos = HashMap::new();
    gerar_codigos(&arvore, vec![], &mut codigos);

    // preparo escrita bufferizada para performance (reduzir syscalls)
    let mut escritor = BufWriter::new(File::create(caminho_saida).unwrap());

    // escrever cabeçalho 
    let n = caracteres.len() as u16; // n == número de símbolos distintos (u16 BE)
    let t = conteudo.len() as u32;   // t == número total de caracteres (u32 BE)
    escritor.write_all(&n.to_be_bytes()).unwrap();
    escritor.write_all(&t.to_be_bytes()).unwrap();

    for &c in &caracteres {
        escritor.write_all(&(c as u16).to_be_bytes()).unwrap(); //caracter
        escritor.write_all(&freq_map[&c].to_be_bytes()).unwrap(); //frequencia
    }

    // escreve o corpo comprimido: bits concatenados
    let mut buffer = 0u8; //acumulador de bits
    let mut bits = 0; //rastreia quantos bits já foram escritos
    for c in conteudo.chars() {
        for &bit in &codigos[&c] { //Conversão do caracter para sua versão em huffman
            buffer <<= 1; //Move os bits do buffer uma posição para a esquerda.
            if bit { buffer |= 1; } //Se for true , define o último bit de buffer como 1.
                                    //Se for false (0), ele já está em 0 após o shift, então não faz nada.
            bits += 1;
            if bits == 8 {
                escritor.write_all(&[buffer]).unwrap();
                buffer = 0;
                bits = 0;
            }
        }
    }
    if bits > 0 { //tratar byte incompleto, optei por preencher com zeros
        buffer <<= 8 - bits;
        escritor.write_all(&[buffer]).unwrap();
    }
    // BufWriter fecha ao sair da função
}

// (Re)construir árvore a partir das frequências
fn construir_arvore(lista: Vec<(char, u32)>) -> Box<Huffman> {
    let mut heap = BinaryHeap::new();

    let mut ordenado = lista;
    ordenado.sort_by(|a, b| a.0.cmp(&b.0));

    //inicializar a heap com as folhas
    for (i, (c, f)) in ordenado.iter().enumerate() {
        heap.push(HeapNode {
            freq: *f,
            order: i,
            tree: Box::new(Huffman::Leaf { c: *c, freq: *f }),
        });
    }

    let mut ordem = ordenado.len();
    //Construir a árvore combinando os dois menores nós até sobrar um:
    while heap.len() > 1 {
        let x = heap.pop().unwrap();
        let y = heap.pop().unwrap();
        let freq = x.freq + y.freq;
        let node = Box::new(Huffman::Node {
            freq,
            left: x.tree,
            right: y.tree,
        });
        heap.push(HeapNode {
            freq,
            order: ordem,
            tree: node,
        });
        ordem += 1;
    }

    //retorna a raiz da árvore
    heap.pop().unwrap().tree
}

// Descompactar arquivo
fn descompactar(caminho_entrada: &str, caminho_saida: &str) {
    let mut leitor = BufReader::new(File::open(caminho_entrada).unwrap());

    let mut buf_u16 = [0u8; 2];
    let mut buf_u32 = [0u8; 4];

    let metadata = fs::metadata(caminho_entrada).unwrap();
    if metadata.len() == 0 {
        // Cria um arquivo vazio de saída
        let _ = File::create(caminho_saida);
        return;
    }

    leitor.read_exact(&mut buf_u16).unwrap();
    let n = u16::from_be_bytes(buf_u16) as usize;

    leitor.read_exact(&mut buf_u32).unwrap();
    let t = u32::from_be_bytes(buf_u32) as usize;

    let mut lista = Vec::new();
    for _ in 0..n {
        leitor.read_exact(&mut buf_u16).unwrap();
        let c = char::from_u32(u16::from_be_bytes(buf_u16) as u32).unwrap();
        leitor.read_exact(&mut buf_u32).unwrap();
        let f = u32::from_be_bytes(buf_u32);
        lista.push((c, f));
    }

    let arvore = construir_arvore(lista);

    let mut bytes_codificados = Vec::new();
    leitor.read_to_end(&mut bytes_codificados).unwrap();

    let mut resultado = String::new();
    let mut atual = &arvore;
    let mut total_lidos = 0;

    'externo: for byte in bytes_codificados {
        for i in (0..8).rev() {
            let bit = (byte >> i) & 1;
            match &**atual {
                Huffman::Leaf { c, .. } => {
                    resultado.push(*c);
                    total_lidos += 1;
                    if total_lidos == t {
                        break 'externo;
                    }
                    atual = &arvore;
                }
                Huffman::Node { left, right, .. } => {
                    atual = if bit == 0 { left } else { right };

                    if let Huffman::Leaf { c, .. } = &**atual {
                        resultado.push(*c);
                        total_lidos += 1;
                        if total_lidos == t {
                            break 'externo;
                        }
                        atual = &arvore;
                    }
                }
            }
        }
    }


    let mut escritor = BufWriter::new(File::create(caminho_saida).unwrap());
    escritor.write_all(resultado.as_bytes()).unwrap();
}

// ========================= MAIN ==============================

/* 
fn main() {
    // Altere aqui para "1" ou "2"
    let opcao = "2";

    let entrada_txt = "entrada.txt";
    let saida_huff = "saida.huff";
    let saida_txt = "saida.txt";

    match opcao {
        "1" => {
            println!("==> Compactando '{}'", entrada_txt);

            if !Path::new(entrada_txt).exists() {
                eprintln!("Arquivo '{}' não encontrado.", entrada_txt);
                return;
            }

            if Path::new(saida_huff).exists() {
                println!("Substituindo '{}'", saida_huff);
                fs::remove_file(saida_huff).unwrap();
            }

            compactar(entrada_txt, saida_huff);
            println!("Compactado em '{}'", saida_huff);
        }

        "2" => {
            println!("==> Descompactando '{}'", saida_huff);

            if !Path::new(saida_huff).exists() {
                eprintln!("Arquivo '{}' não encontrado.", saida_huff);
                return;
            }

            if Path::new(saida_txt).exists() {
                println!("Substituindo '{}'", saida_txt);
                fs::remove_file(saida_txt).unwrap();
            }

            descompactar(saida_huff, saida_txt);
            println!("Descompactado em '{}'", saida_txt);
        }

        _ => {
            eprintln!("Opção inválida! Use \"1\" para compactar ou \"2\" para descompactar.");
        }
    }
}
*/

fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() < 2 {
        eprintln!("Uso: cargo run -- <1 para compactar | 2 para descompactar>");
        return;
    }

    let opcao = args[1].as_str();

    let entrada_txt = "entrada.txt";
    let saida_huff = "saida.huff";
    let saida_txt = "saida.txt";

    match opcao {
        "1" => {
            println!("==> Compactando '{}'", entrada_txt);

            if !Path::new(entrada_txt).exists() {
                eprintln!("Arquivo '{}' não encontrado.", entrada_txt);
                return;
            }

            if Path::new(saida_huff).exists() {
                println!("Substituindo '{}'", saida_huff);
                fs::remove_file(saida_huff).unwrap();
            }

            compactar(entrada_txt, saida_huff);
            println!("Compactado em '{}'", saida_huff);
        }

        "2" => {
            println!("==> Descompactando '{}'", saida_huff);

            if !Path::new(saida_huff).exists() {
                eprintln!("Arquivo '{}' não encontrado.", saida_huff);
                return;
            }

            if Path::new(saida_txt).exists() {
                println!("Substituindo '{}'", saida_txt);
                fs::remove_file(saida_txt).unwrap();
            }

            descompactar(saida_huff, saida_txt);
            println!("Descompactado em '{}'", saida_txt);
        }

        _ => {
            eprintln!("Opção inválida! Use \"1\" para compactar ou \"2\" para descompactar.");
        }
    }
}
/* PARA USAR NA LINHA DE COMANDO:
cargo run -- 1  # Para compactar entrada.txt → saida.huff
cargo run -- 2  # Para descompactar saida.huff → saida.txt
*/

#[cfg(test)]
mod tests {
    use super::*;
    use std::fs::{self, File};
    use std::io::Write;

    fn cria_arquivo(nome: &str, conteudo: &str) {
        let mut f = File::create(nome).unwrap();
        f.write_all(conteudo.as_bytes()).unwrap();
    }

    fn compara_arquivos(a: &str, b: &str) -> bool {
        fs::read(a).unwrap() == fs::read(b).unwrap()
    }

    fn testa_fluxo(conteudo: &str, id: usize) {
        let e = format!("entrada{}.txt", id);
        let h = format!("saida{}.huff", id);
        let s = format!("saida{}.txt", id);

        cria_arquivo(&e, conteudo);
        compactar(&e, &h);
        descompactar(&h, &s);
        assert!(compara_arquivos(&e, &s), "Falha no teste {}", id);

        // opcional: limpar arquivos depois
        let _ = fs::remove_file(&e);
        let _ = fs::remove_file(&h);
        let _ = fs::remove_file(&s);
    }

// Testa uma palavra simples com repetições
    #[test]
    fn teste_1_palavra_simples() {
        testa_fluxo("banana", 1);
    }

// Testa frase com espaços
    #[test]
    fn teste_2_frase_com_espacos() {
        testa_fluxo("bananada eh muito bom", 2);
    }

// Testa quebras de linha
    #[test]
    fn teste_3_com_quebra_de_linha() {
        testa_fluxo("linha 1\nlinha 2\nlinha 3", 3);
    }

// Testa muitas repetições de poucos caracteres
    #[test]
    fn teste_4_repeticoes() {
        testa_fluxo("aaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbb", 4);
    }

// Testa todos os caracteres ASCII visíveis
    #[test]
    fn teste_5_ascii_visiveis() {
        let ascii: String = (32u8..127u8).map(|c| c as char).collect();
        testa_fluxo(&ascii, 5);
    }

// Testa entrada vazia
    #[test]
    fn teste_6_vazio() {
        testa_fluxo("", 6);
    }

// Testa entrada longa e repetitiva
    #[test]
    fn teste_7_longo() {
        let texto = "bananada eh muito bom\n".repeat(1000);
        testa_fluxo(&texto, 7);
    }

    #[test]
    fn teste_8_heap_ordenacao() {
        use std::collections::BinaryHeap;
        use std::cmp::Reverse;

        let mut heap = BinaryHeap::new();
        heap.push(Reverse((2, 0)));
        heap.push(Reverse((1, 1)));
        heap.push(Reverse((3, 2)));

        let menores: Vec<u32> = (0..3).map(|_| heap.pop().unwrap().0.0).collect();
        assert_eq!(menores, vec![1, 2, 3]);
    }

    #[test]
    fn teste_9_arvore_simples() {
        use crate::Huffman;

        let a = Box::new(Huffman::Leaf { c: 'a', freq: 3 });
        let b = Box::new(Huffman::Leaf { c: 'b', freq: 7 });

        let raiz = Huffman::Node {
            freq: 10,
            left: a,
            right: b,
        };

        match raiz {
            Huffman::Node { freq, .. } => assert_eq!(freq, 10),
            _ => panic!("Esperado um nó interno"),
        }
    }

    #[test]
    fn teste_10_gera_codigo_simples() {
        use crate::{Huffman, gerar_codigos};
        use std::collections::HashMap;

        let a = Box::new(Huffman::Leaf { c: 'a', freq: 1 });
        let b = Box::new(Huffman::Leaf { c: 'b', freq: 1 });

        let arvore = Huffman::Node {
            freq: 2,
            left: a,
            right: b,
        };

        let mut codigos = HashMap::new();
        gerar_codigos(&arvore, vec![], &mut codigos); // prefixo como Vec<bool>

        // Esperado: 'a' e 'b' com códigos diferentes de mesmo tamanho
        assert_eq!(codigos[&'a'].len(), 1);
        assert_eq!(codigos[&'b'].len(), 1);
        assert_ne!(codigos[&'a'], codigos[&'b']);
    }


    #[test]
    fn teste_11_bits_para_bytes() {
        let bits = "10110011"; // 0b10110011 = 179
        let byte = u8::from_str_radix(bits, 2).unwrap();
        assert_eq!(byte, 179);
    }

    #[test]
    fn teste_12_decodificacao_basica() {
        use std::collections::HashMap;

        let mut tabela = HashMap::new();
        tabela.insert("0", 'a');
        tabela.insert("10", 'b');
        tabela.insert("11", 'c');

        let entrada = "010"; // 'a' (0), 'b' (10)
        let mut atual = String::new();
        let mut saida = String::new();

        for bit in entrada.chars() {
            atual.push(bit);
            if let Some(&c) = tabela.get(&atual[..]) {
                saida.push(c);
                atual.clear();
            }
        }

        assert_eq!(saida, "ab");
    }


}