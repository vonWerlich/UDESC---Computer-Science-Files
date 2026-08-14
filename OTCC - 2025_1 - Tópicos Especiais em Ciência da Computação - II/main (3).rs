
// Exercício 4 - Optativa Rust
// Kauan H. Werlich

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

/// Estrutura interna do iterador: mantém uma pilha de referências a nós
pub struct TreeIter<'a, T> {
    stack: Vec<&'a NoArvore<T>>,
    current: Option<&'a NoArvore<T>>,
}

impl<'a, T> TreeIter<'a, T> {
    /// Cria um novo iterador a partir de uma referência à raiz
    fn new(root: Option<&'a Box<NoArvore<T>>>) -> Self {
        TreeIter {
            stack: Vec::new(),
            current: root.map(|b| b.as_ref()), // converte Option<&Box<NoArvore<T>>> em Option<&NoArvore<T>>
        }
    }
}


/// Iterator para o TreeIter.
/// Cada chamada a next() retorna a próxima referência &T em-ordem.
impl<'a, T> Iterator for TreeIter<'a, T> {
    type Item = &'a T;

    fn next(&mut self) -> Option<Self::Item> {
        // Desce o mais possível à esquerda, empilhando cada nó
        while let Some(node) = self.current {
            self.stack.push(node);
            self.current = node.esquerda.as_deref();
        }

        // Se empilhar algo, é porque existe próximo elemento
        let node = self.stack.pop()?;
        // Após visitar esse nó, parte para a subárvore direita
        self.current = node.direita.as_deref();

        Some(&node.valor)
    }
}

// Necessário para que for v in &tree { … } funcione.
// Ou seja, quando chama .into_iter() em &Tree<T>, ele deve construir o TreeIter.
impl<'a, T> IntoIterator for &'a Tree<T> {
    type Item = &'a T;
    type IntoIter = TreeIter<'a, T>;

    fn into_iter(self) -> Self::IntoIter {
        TreeIter::new(self.root.as_ref())
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
    tree.insert(4);
    tree.insert(2);

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

    println!("\nIterando em ordem usando Iterator");
    for v in &tree {
        println!("{v}");//println!("{}, v");
    }
}

///////////////////////////////////////////////////////////////////////////////

#[cfg(test)]
mod tests {
    use super::Tree;

    #[test]
    fn test_insercao_in_order() {
        let mut tree = Tree::new();
        tree.insert(5);
        tree.insert(3);
        tree.insert(7);
        tree.insert(1);
        tree.insert(4);

        /*tree.post_order() retorna Vec<&T>
        precisa de Vec<T> para comparar com vec![1, 2, 3]
        .into_iter() -> chama o método de iterador de Vec, não o da árvore
        .copied() transforma &T em T (se T for Copy)
        .collect() junta tudo de novo num Vec<T> */

        let resultado: Vec<_> = tree.in_order().into_iter().copied().collect();
        assert_eq!(resultado, vec![1, 3, 4, 5, 7]);
    }

    #[test]
    fn test_pre_order() {
        let mut tree = Tree::new();
        tree.insert(5);
        tree.insert(3);
        tree.insert(7);
        tree.insert(1);
        tree.insert(4);

        let resultado: Vec<_> = tree.pre_order().into_iter().copied().collect();
        assert_eq!(resultado, vec![5, 3, 1, 4, 7]);
    }

    #[test]
    fn test_post_order() {
        let mut tree = Tree::new();
        tree.insert(5);
        tree.insert(3);
        tree.insert(7);
        tree.insert(1);
        tree.insert(4);

        let resultado: Vec<_> = tree.post_order().into_iter().copied().collect();
        assert_eq!(resultado, vec![1, 4, 3, 7, 5]);
    }

    #[test]
    fn test_remove_existente() {
        let mut tree = Tree::new();
        tree.insert(5);
        tree.insert(3);
        tree.insert(7);

        assert!(tree.remove(&3));
        let resultado: Vec<_> = tree.in_order().into_iter().copied().collect();
        assert_eq!(resultado, vec![5, 7]);
    }

    #[test]
    fn test_remove_inexistente() {
        let mut tree = Tree::new();
        tree.insert(5);
        tree.insert(3);

        assert!(!tree.remove(&10));
        let resultado: Vec<_> = tree.in_order().into_iter().copied().collect();
        assert_eq!(resultado, vec![3, 5]);
    }

    #[test]
    fn test_remove_maximo() {
        let mut tree = Tree::new();
        tree.insert(5);
        tree.insert(10);
        tree.insert(3);

        let max = tree.remove_max();
        assert_eq!(max, Some(10));
        let resultado: Vec<_> = tree.in_order().into_iter().copied().collect();
        assert_eq!(resultado, vec![3, 5]);
    }

    #[test]
    fn test_remove_maximo_em_vazio() {
        let mut tree: Tree<i32> = Tree::new();
        let max = tree.remove_max();
        assert_eq!(max, None);
    }

    #[test]
    fn test_iterador_in_order() {
        let mut tree = Tree::new();
        tree.insert(8);
        tree.insert(3);
        tree.insert(10);
        tree.insert(1);

        let resultado: Vec<_> = (&tree).into_iter().copied().collect(); //into_iter da árvore!
        assert_eq!(resultado, vec![1, 3, 8, 10]);
    }

    #[test]
    fn test_iterador_em_arvore_vazia() {
        let tree: Tree<i32> = Tree::new();
        let mut iter = (&tree).into_iter();
        assert_eq!(iter.next(), None);
    }

}
