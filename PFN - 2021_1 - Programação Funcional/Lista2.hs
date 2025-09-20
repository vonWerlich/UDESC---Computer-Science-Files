--autor: Kauan Henrique Werlich Curso: Programação Funcional
module Lista2 
(pertence,
intercessao,
inversoLista,
nUltimos,
enesimo,
repetir,
intercalacao,
removerElem,
menor,
ordenarLista,
insereElem,
primeirosDuplas,
somaDuplas,
menoresDuplas,
menoresn',
maioresn',
separarDuplas,
mdc,
inversoDupla,
simetrico,
pares,
inverteDNA',
inverteDNA,
trocoCafe',
--trocoCafe'',
trocoCafe,
--notasTroco,
magica',
magica
)where

--1: verifica se um elemento pertente a uma lista.
pertence n [] = False
pertence n (x:xs) = if n == x then True else pertence n xs

--2: retorna a intercessão entre duas listas.
intercessao _ [] = []
intercessao [] _ = []
intercessao (x:xs) y = if (pertence x y == True) then (x : intercessao xs y) else intercessao xs y

{- 
Funções já implementadas no prelude que são usadas em inversoLista e em enesimo:
last (x:[]) = x
last (x:xs) = last xs 

init (x:[]) = []
init (x:xs) = x : init xs
-}

--3: retorna o inverso de uma lista.
inversoLista [] = []
inversoLista (x) = last x : inversoLista (init x)

{-
Função já implementada no prelude usada em 'nUltimos' e em 'enesimo':
length :: (Num b) => [a] -> b
length [] = 0
length (_:xs) = 1 + length xs
-}

--4: retorna os n últimos elementos de uma lista.
nUltimos n [] = []
nUltimos n (x:xs) = if n >= length (x:xs) then x:xs else nUltimos n xs

{-
A função 'enesimo' só funciona com valores inteiros >= 1, pois não existe posição negativa em uma lista.
Por isso não achei necessário definir o caso de parada  enesimo n [] = -1   , pois a função não precisa dele e essa posição não existe.
-}

--5: recebe um número n e uma lista e retorna o n ésimo elemento da lista. Se n for maior que o tamanho da lista, retorna -1.
enesimo n (x:xs) | n > length (x:xs) = -1 
                 | n == length (x:xs) = last (x:xs)
                 | n < length (x:xs) = enesimo n (init (x:xs))

--6: recebe dois números inteiros n e m, e retorna uma lista com n vezes o número m.
repetir n m = if n >0 then m : repetir (n-1) m else []

--7: recebe duas listas e faz a intercalação dos elementos, resultando na junção das duas listas em uma lista ordenada.
intercalacao (x) (y) = ordenarLista (x++y)

--8: retorna o menor valor de uma lista.
{-
Em Haskell o prelude fornece a função 'minimum', que assim como a função 'menor' retorna o menor valor de uma lista.
-}
menor::(Ord a) => [a]->a
menor [] = error"indefinido"
menor [x] = x
menor (x:xs) = if x <= (menor xs) then x else menor xs

--9: recebe uma lista e um elemento e retorna a lista sem a primeira ocorrência desse elemento.
removerElem n [] = []
removerElem n (x:xs) = if n == x then xs else x : removerElem n xs

--10: ordena os elementos de uma lista.
ordenarLista [] = []
ordenarLista (xs) = x : ordenarLista (removerElem x xs)
                        where x = menor xs
             
--11: recebe um elemento e uma lista ordenada e insere este elemento na lista colocando o na posição correta,
--ou seja, a lista resultante deve estar ordenada. Se o elemento já pertencer à lista, ele não deve ser incluído.
insereElem n (x) = if pertence n (x) == True then (x) else ordenarLista (n:x)

--12: recebe uma lista de duplas [(a,b)] e retorna uma lista com o primeiro elemento de cada dupla [a].
primeirosDuplas ([]) = []
primeirosDuplas ((a,b):ab) = (a: primeirosDuplas (ab)) 

--13: recebe uma lista de duplas e retorna uma lista com a soma dos elementos de cada dupla.
somaDuplas ([]) = []
somaDuplas ((a,b):ab) = (a+b: somaDuplas ab)

--14: recebe uma lista de duplas e retorna uma lista contendo todas as duplas cujo primeiro elemento seja menor que o segundo.
menoresDuplas ([]) = []
menoresDuplas ((a,b): ab) = if a < b then ((a,b): menoresDuplas ab) else menoresDuplas ab

menoresn' _ [] = []
menoresn' n (x:xs) = if x <= n then x: menoresn' n xs else menoresn' n xs

maioresn' _ [] = [] 
maioresn' n (x:xs) = if x > n then x: maioresn' n xs else maioresn' n xs

--15: recebe um valor v e uma lista, deve retornar uma dupla de listas, a primeira lista deve conter os elementos
--que são menores ou iguais a v e a segunda lista deve retornar os elementos maiores que v.
separarDuplas _ [] = ([],[])
separarDuplas v (x:xs) = ((y),(z))
                  where y = menoresn' v (x:xs)
                        z = maioresn' v (x:xs)

--16: Implemente o Algoritmo de Euclides Estendido, tal como a função gcd disponível em Prelude. O Algoritmo de Euclides estendido permite calcular
--o máximo divisor comum (MDC) fornecendo como resultado os coeficientes. Considere a seguinte regra: a se b = 0, mdc(b, a mod b) se b > 0,

{- Função alternativa para resolver o mdc, utilizando o Algoritmo de Euclides e a propriedade enunciada por ele para resolver o problema
mdccomum (1,_) = 1
mdccomum (_,1) = 1
mdccomum (a,b)   | a > b = mdccomum (a-b,b)
                 | a == b = a
                 | a < b = mdccomum (a,b-a)
-}
mdc (a,b) | b<0 = error"nao existe mdc de numero negativo"
          | b == 0 = a
          | b > 0 = mdc (b,a `mod` b)

--17: Recebe uma lista de duplas [(x,y)], e retorna uma lista com o inverso de cada dupla, ou seja [(y,x)].
inversoDupla [] = []
inversoDupla ((a,b):ab) = (b,a):inversoDupla ab

--18: Recebe uma lista de duplas, e retorna uma lista indicando se os elementos são iguais ou não entre si(True/False).
simetrico [] = []
simetrico ((a,b): ab) | a == b = True: simetrico ab
                      |otherwise = False: simetrico ab

--19: Recebe um número inteiro e retorna uma lista de duplas de inteiros distintos (x,y) tal que 1 ≤ x, y ≤ i.
pares n = [(x,y) | x <- [1..n], y <- [1..n], x /= y]

--20: Supõe que a sequência de DNA é formada pelas letras A, T, C e G. Recebe uma sequência de DNA,
--e retorna a sequência invertendo as letras, tal que: A será T e T será A, C será G e G será C. Ao final, toda a sequência deve também ser invertida.
inverteDNA' [] = []
inverteDNA' (x:xs) | x == 'A' = 'T': inverteDNA' xs
                   | x == 'T' = 'A': inverteDNA' xs
                   | x == 'C' = 'G': inverteDNA' xs
                   | x == 'G' = 'C': inverteDNA' xs
                   |otherwise = error"letra diferente de A, T, C ou G"

inverteDNA (x) = inversoLista xs
                where xs = inverteDNA' x

--21: Recebe o valor do café (Int) e o valor em dinheiro pago pelo cliente (Int), e retorna uma lista de tuplas [(a, b)],
--tal que a é o valor da moeda, e b a quantidade de moedas deste valor. São permitidas moedas de 5, 10, 20 e 50 centavos,
--e deve ser sempre retornado moedas de maior valor antes.
moedas = [50,20,10,5]
{-
trocoCafe a b = [(x,y) | x <- head (z),y <- trocoCafe' (z) w]
                            where z = moedas
                                  w = b - a-}

trocoCafe' [] t = []
trocoCafe' (x:xs) t = if t `div` x > 0 then t `div` x : trocoCafe' (xs) z else 0 : trocoCafe' xs t
                           where z = t `mod` x

trocoCafe'' [] [] = []
trocoCafe'' (x) (y) = if head y == 0 then trocoCafe'' (tail x) (tail y) else (head x,head y) : trocoCafe'' (tail x) (tail y)


trocoCafe x y | y < x = error"o valor pago pelo cliente é menor que o valor do café"
              | y == x = []
              | y > x = trocoCafe'' moedas (a)
                where b = y - x 
                      a = trocoCafe' moedas b



--22: recebe e retorna uma string, com o comportamento abaixo:
--Input String: "AB" / Output String: "AABAA"
--Input String: "ABC" / Output String: "AAABBCBBAAA"
--Input String: "abC" / Output String: "aaabbCbbaaa"
--Input String: "ABCD" / Output String: "AAAABBBCCDCCBBBAAAA"
magica' [] = []
magica' (x:xs) = repetir z x ++ magica' (xs)
                where z = length (x:xs)

magica (x:xs) = y ++ inversoLista z
                  where y = magica' (x:xs)
                        z = init y

