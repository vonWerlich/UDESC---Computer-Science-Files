
/* [dependencies]
byteorder = "1"
utf8-read = "0.4.0"  */

use std::{collections::HashMap};
use std::fs::File;
use std::io::{Cursor, Read, Write};
use byteorder::{BigEndian, WriteBytesExt, ReadBytesExt};
use std::io;
use utf8_read::Reader;

fn frequencia(arq:String, map_freq:&mut HashMap<char, u32>) -> io::Result<usize>  {
    let fs = File::open(arq)?;
    let mut buf = Reader::new(&fs);
    let conteudo = buf.into_iter(); 

    let mut num:usize = 0;
    let mut c:char;
    for r in conteudo {
        c = r.expect("frequencia:Erro na leitura de arquivo de entrada");
        num += 1;
        match map_freq.get(&c) {
            None => {map_freq.insert(c, 1);}
            Some (v) => {map_freq.insert(c, v+1);}
        }
    }
    Ok(num)

}

fn escrita (arq:String, map_freq: &HashMap<char, u32>) -> io::Result<()> {
    let mut fs = File::create_new(arq)?;
    let mut buffer = Cursor::new(Vec::new());
    buffer.write_u16::<BigEndian>(map_freq.len() as u16)?;
    for i in map_freq {
        buffer.write_u32::<BigEndian>(*i.0 as u32)?;
        buffer.write_u32::<BigEndian>(*i.1)?;

    }
    fs.write_all(buffer.get_mut())?;
    Ok(())
}
fn leitura(arq:String) -> io::Result <()> {
    let mut fs = File::open(arq)?;
    let mut v:Vec<u8> = Vec::new();
    fs.read_to_end (&mut v)?;
    let mut buffer = Cursor::new(v);

    let tam = buffer.read_u16::<BigEndian>().unwrap();
    let mut c:char;
    let mut f:u32;
    println!("Número de símbolos: {tam}");
    for _i in 0..tam {
        c = char::from_u32(buffer.read_u32::<BigEndian>().unwrap()).unwrap();
        f = buffer.read_u32::<BigEndian>().unwrap();
        println!("{c} - {f}");
    }
    Ok(())
}

fn main() {
    let mut map_freq = HashMap::new();
    let temp = "/temp/freq.bin";
    let arq = "/temp/teste1.txt";
    match frequencia(arq.to_string(), &mut map_freq) {
        Ok(t) => { 
            println!("O arquivo possui {t} caracteres.");
            match escrita(temp.to_string(), &map_freq) {
                Ok (_) => {let _ = leitura(temp.to_string()); }
                Err (e) => { println!("Arquivo {temp} não pode ser criado.\n {e}");} 
            }
        }
        Err(_) => {println!("Arquivo {arq} não existe.");}
    }
}
