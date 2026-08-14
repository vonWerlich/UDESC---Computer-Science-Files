use std::fmt::{self, Display, Formatter};

// Estrutura principal da árvore binária de busca
pub struct Tree<T> {
    root: Option<Box<NoArvore<T>>>, // raiz da árvore, pode estar vazia
}

// Estrutura de cada nó da árvore
pub struct NoArvore<T> {
    // subárvore esquerda
    direita: Option<Box<NoArvore<T>>>,                           // valor armazenado
    esquerda: Option<Box<NoArvore<T>>>,       valor: T,      // subárvore direita
}

impl<T: Ord> Tree<T> {
    // Cria uma nova árvore vazia
    pub fn new() -> Self {
        Tree { root: None }
    }

    // Insere um novo valor na árvore
    pub fn insert(&mut self, value: T) {
        // Função recursiva para inserir o valor no local correto
        fn inserir_no<T: Ord>(node: &mut Option<Box<NoArvore<T>>>, value: T) {
            match node {
                Some(n) => {
                    // Vai para a subárvore esquerda se for menor
                    if value < n.valor {
                        inserir_no(&mut n.esquerda, value);
                    } else {
                        // Vai para a direita se for maior ou igual
                        inserir_no(&mut n.direita, value);
                    }
                }
                // Se chegou num "nó vazio", cria o novo nó aqui
                None => {
                    *node = Some(Box::new(NoArvore {
                        valor: value,
                        esquerda: None,
                        direita: None,
                    }));
                }
            }
        }

        inserir_no(&mut self.root, value);
    }

    // Remove e retorna o maior valor da árvore (caso exista)
    pub fn remove_max(&mut self) -> Option<T> {
        // Percorre recursivamente para a direita até achar o maior
        fn remove_max_node<T>(node: &mut Option<Box<NoArvore<T>>>) -> Option<T> {
            // Se ainda há subárvore direita, continua buscando nela
            if node.as_ref()?.direita.is_some() {
                return remove_max_node(&mut node.as_mut()?.direita);
            }

            // Nó atual é o maior. Remove-o e ajusta ponteiros.
            let boxed = node.take()?;      // remove o nó
            *node = boxed.esquerda;            // substitui pelo filho esquerdo (se houver)
            Some(boxed.valor)               // retorna o valor removido
        }

        remove_max_node(&mut self.root)
    }

    // Remove um valor específico da árvore, retorna true se conseguiu remover
    pub fn remove(&mut self, value: &T) -> bool {
        fn remove_node<T: Ord>(node: &mut Option<Box<NoArvore<T>>>, value: &T) -> bool {
            let n = match node {
                Some(n) => n,
                None => return false, // valor não encontrado
            };

            if value < &n.valor {
                // busca recursivamente à esquerda
                return remove_node(&mut n.esquerda, value);
            } else if value > &n.valor {
                // busca recursivamente à direita
                return remove_node(&mut n.direita, value);
            }

            // achou o nó a ser removido
            let mut old = node.take().unwrap();

            match (old.esquerda.take(), old.direita.take()) {
                (None, None) => {
                    // caso 1: nó sem filhos
                    *node = None;
                }
                (Some(left), None) => {
                    // caso 2: só filho à esquerda
                    *node = Some(left);
                }
                (None, Some(right)) => {
                    // caso 3: só filho à direita
                    *node = Some(right);
                }
                (Some(left), Some(right)) => {
                    // caso 4: dois filhos
                    // encontra o menor da subárvore direita
                    let mut right = right;
                    let mut min = &mut right;
                    while let Some(ref mut leftmost) = min.esquerda {
                        min = leftmost;
                    }

                    // troca os valores do nó atual com o menor da subárvore direita
                    std::mem::swap(&mut old.valor, &mut min.valor);

                    // recoloca os filhos antigos
                    old.esquerda = Some(left);
                    old.direita = Some(right);
                    *node = Some(old);

                    // continua tentando remover o valor (agora deslocado) à direita
                    return remove_node(&mut node.as_mut().unwrap().direita, value);
                }
            }
            true
        }

        remove_node(&mut self.root, value)
    }

    // Percorre em ordem (esquerda → raiz → direita), retorna vetor de referências
    pub fn in_order(&self) -> Vec<&T> {
        fn walk<'a, T>(node: &'a Option<Box<NoArvore<T>>>, acc: &mut Vec<&'a T>) {
            if let Some(n) = node {
                walk(&n.esquerda, acc);
                acc.push(&n.valor);
                walk(&n.direita, acc);
            }
        }

        let mut result = Vec::new();
        walk(&self.root, &mut result);
        result
    }

    // Percorre em pré-ordem (raiz → esquerda → direita)
    pub fn pre_order(&self) -> Vec<&T> {
        fn walk<'a, T>(node: &'a Option<Box<NoArvore<T>>>, acc: &mut Vec<&'a T>) {
            if let Some(n) = node {
                acc.push(&n.valor);
                walk(&n.esquerda, acc);
                walk(&n.direita, acc);
            }
        }

        let mut result = Vec::new();
        walk(&self.root, &mut result);
        result
    }

    // Percorre em pós-ordem (esquerda → direita → raiz)
    pub fn post_order(&self) -> Vec<&T> {
        fn walk<'a, T>(node: &'a Option<Box<NoArvore<T>>>, acc: &mut Vec<&'a T>) {
            if let Some(n) = node {
                walk(&n.esquerda, acc);
                walk(&n.direita, acc);
                acc.push(&n.valor);
            }
        }

        let mut result = Vec::new();
        walk(&self.root, &mut result);
        result
    }

    // Remove um valor e imprime o resultado (sucesso ou falha)
    pub fn remove_and_print(&mut self, value: T)
    where
        T: Display,
    {
        if self.remove(&value) {
            println!("Elemento {} removido com sucesso.", value);
        } else {
            println!("Elemento {} não encontrado.", value);
        }
    }

    // Remove e imprime o maior elemento da árvore (ou avisa se está vazia)
    pub fn remove_max_and_print(&mut self)
    where
        T: Display,
    {
        match self.remove_max() {
            Some(max) => println!("Maior elemento removido: {}", max),
            None => println!("A árvore está vazia, nenhum elemento removido."),
        }
    }
}

// Implementa Display para exibir os 3 percursos principais da árvore
impl<T: Display + Ord> Display for Tree<T> {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        let in_order: Vec<String> = self.in_order().iter().map(|x| format!("{}", x)).collect();
        let pre_order: Vec<String> = self.pre_order().iter().map(|x| format!("{}", x)).collect();
        let post_order: Vec<String> = self.post_order().iter().map(|x| format!("{}", x)).collect();

        writeln!(f, "Pré-ordem   (raiz, esquerda, direita): [{}]", pre_order.join(", "))?;
        writeln!(f, "Em ordem    (esquerda, raiz, direita): [{}]", in_order.join(", "))?;
        writeln!(f, "Pós-ordem  (esquerda, direita, raiz): [{}]", post_order.join(", "))
    }
}

// Função principal de teste da árvore
fn main() {
    let mut tree = Tree::new();

    // Inserções na árvore
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(6);
    tree.insert(8);

    // Exibe a árvore nos 3 percursos
    println!("Árvore:\n{}", tree);

    // Remove o maior elemento
    tree.remove_max_and_print();

    // Exibe árvore após a remoção
    println!("Árvore após remover o maior:\n{}", tree);

    // Tenta remover elementos específicos (com mensagem)
    tree.remove_and_print(10); // não existe
    tree.remove_and_print(5);  // existe

    // Árvore final
    println!("Árvore final:\n{}", tree);

    // Mostra os vetores dos percursos finais
    println!("Percursos da árvore final:");
    println!("Pré-ordem   (raiz, esquerda, direita): {:?}", tree.pre_order());
    println!("Em ordem    (esquerda, raiz, direita): {:?}", tree.in_order());
    println!("Pós-ordem  (esquerda, direita, raiz): {:?}", tree.post_order());
}
