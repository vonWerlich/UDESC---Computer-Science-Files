#[derive(Debug)]
enum NoLista {
    Cons(i32, Box<NoLista>),
    Nil,
}

#[derive(Debug)]
struct Lista {
    cab: Box<NoLista>,
}

// Cria uma nova lista vazia
fn nova_lista() -> Lista {
    Lista {
        cab: Box::new(NoLista::Nil),
    }
}

// Insere um valor no final da lista (na cauda)
fn inserir_na_cauda(lista: &mut Lista, valor: i32) {
    let mut atual = &mut lista.cab;
    while let NoLista::Cons(_, ref mut prox) = **atual {
        atual = prox;
    }
    **atual = NoLista::Cons(valor, Box::new(NoLista::Nil));
}

// Remove o último valor da lista (da cauda)
fn remover_da_cauda(lista: &mut Lista) {
    let mut atual = &mut lista.cab;

    // Lista vazia?
    if let NoLista::Nil = **atual {
        return;
    }

    // Só um elemento?
    if let NoLista::Cons(_, ref mut prox) = **atual {
        if let NoLista::Nil = **prox {
            **atual = NoLista::Nil;
            return;
        }
    }

    // Caminha até o penúltimo
    while let NoLista::Cons(_, ref mut prox) = **atual {
        if let NoLista::Cons(_, ref mut prox2) = **prox {
            if let NoLista::Nil = **prox2 {
                **prox = NoLista::Nil;
                return;
            }
        }
        atual = prox;
    }
}

// Função que insere um valor em ordem crescente na sublista a partir de um nó
fn inserir_ordenado_nolista(no: Box<NoLista>, valor: i32) -> Box<NoLista> {
    match *no {
        NoLista::Nil => {//Se a lista for Nil, insere direto:
            Box::new(NoLista::Cons(valor, Box::new(NoLista::Nil)))
        }
        NoLista::Cons(v, next) => {
            if valor <= v {
                Box::new(NoLista::Cons(valor, Box::new(NoLista::Cons(v, next))))
            } else {
                let nova_cauda = inserir_ordenado_nolista(next, valor);//recursão
                Box::new(NoLista::Cons(v, nova_cauda))
            }
        }
    }
}

// Função que insere em ordem crescente na lista completa -> recursiva
fn inserir_ordenado_lista(lista: &mut Lista, valor: i32) {
    let antiga = std::mem::replace(&mut lista.cab, Box::new(NoLista::Nil));
    lista.cab = inserir_ordenado_nolista(antiga, valor);
}

fn main() {
    let mut lista = nova_lista();

    println!("{:?}", lista);
    inserir_na_cauda(&mut lista, 10);
    inserir_na_cauda(&mut lista, 30);
    println!("Após inserir na cauda: {:?}", lista);

    remover_da_cauda(&mut lista);
    println!("Após remover da cauda: {:?}", lista);

    inserir_ordenado_lista(&mut lista, 20);
    inserir_ordenado_lista(&mut lista, 5);
    inserir_ordenado_lista(&mut lista, 25);
    println!("Após inserções ordenadas: {:?}", lista);
}
