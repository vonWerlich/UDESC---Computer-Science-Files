use std::mem::replace;

#[derive (Debug)]
struct NoLista {
    elem : i32,
    prox: Option<Box<NoLista>>
}

#[derive (Debug)]
pub struct Lista {
    cab : Option<Box<NoLista>>
}

impl Lista {
    fn new() -> Self {
        Lista {cab: None}
    }

    fn insert (&mut self, v:i32) {
        let n = Box::new(NoLista{elem:v, prox:replace(&mut self.cab, None)});
        self.cab = Some (n);
    }
    
    fn iter_lista(&self) -> IterLista {
        IterLista::new(&self.cab)
    } 
    
}

struct IterLista<'a> { 
    prox: &'a Option<Box<NoLista>> 
}

impl<'a> IterLista<'a> {
    fn new(c:&'a Option<Box<NoLista>>) -> Self {
        IterLista {prox:c}
    }

}


impl Iterator for IterLista<'_> {
    type Item = i32;
    fn next (&mut self) -> Option<i32> {
        match self.prox {
            None => None,
            Some (p) => {
                let e = p.elem;
                self.prox = &p.prox;
                Some(e)
            }           
        } 
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn teste1() {
        let mut l:Lista = Lista::new();
        for i in (0..9).rev() {
            l.insert(i);
        }
        for (i, e) in l.iter_lista().enumerate() {
            assert_eq!(i, e as usize);
        }
    }
    #[test]
    fn teste2() {
        let mut l:Lista = Lista::new();
        for i in 1..5 {
            l.insert(i);
        }
        let v1:Vec<i32> = l.iter_lista().map(|x|x*2).collect();
        assert!(v1.into_iter().zip(vec![8, 6, 4, 2]).all(|(a,b)| a == b));
        let v2:Vec<i32> = l.iter_lista().filter(|x|x % 2 == 0).collect();
        assert!(v2.iter().zip(vec![4, 2]).all(|(a,b)| *a == b), "{v2:?} não passou no teste");
    }
}
