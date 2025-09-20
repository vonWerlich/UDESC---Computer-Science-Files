--Autor: Kauan Henrique Werlich
--Prova de Programação Funcional

module Prova1
(menoresn',
maioresn',
maioresMenores,
marcar,
inserir,
)
where

import Data.List

{-Questão 1: Declare uma função que receba como parâmetros uma lista e um dado d, a função
deve retornar uma dupla de listas, a primeira lista deve conter todos os elementos menores
que d e a segunda todos os elementos maiores.-}

--Funções auxiliares:
menoresn' [] _ = []
menoresn' (x:xs) n  = if x < n then x: menoresn' xs n  else menoresn' xs n 

maioresn' [] _ = [] 
maioresn' (x:xs) n = if x > n then x: maioresn' xs n  else maioresn' xs n 

--Função principal:
maioresMenores :: Ord a => [a] -> a -> ([a],[a])
maioresMenores [] _ = ([],[])
maioresMenores (xs) n = (menoresn' xs n,maioresn' xs n)

{-Questão 2: Declare uma função que receba como parâmetros uma string e um caractere c , a
função deve retorn ar a string recebida substituindo todas ocorrências do caractere c pelo
caractere ‘*’.-}

marcar:: [Char] -> Char -> [Char]
marcar [] _ = []
marcar (x:xs) n = if x==n then '*' : marcar xs n else x : marcar xs n

{-Questão 3: Declare uma função que receba como parâmetros um elemento e uma lista
previamente ordenada, a função deve inserir esse elemento na lista tendo como resultado uma
lista ordenada contendo o novo elemento. A lista não deve ser reordenada, a função deve
percorrer a lista até achar a posição correta.-}

inserir :: Ord a => a -> [a] -> [a]
inserir _ [] = []
inserir n (x:xs) = if n > x then x : inserir n xs else n : (x:xs)

{-Questão 4: Declare uma função que receba duas listas previamente ordenadas e faça a
intercalação (merge) dos elementos tendo como resultado a junção das duas listas em uma
lista também ordenada. A lista não deve ser reordenada , deve ser feita a intercalação dos
elementos.-}

intercalacao :: Ord a => [a] -> [a] -> [a]
intercalacao [] (xs) = xs
intercalacao (xs) [] = xs 
intercalacao (x:xs) (y:ys) = if x <= y then x : intercalacao xs (y:ys) else y : intercalacao (x:xs) ys

{-Questão 5: Declare uma função que retorne o número de palavras em uma string .-}


fst' (x) = fst y
           where y = numerarPalavras x

numerarPalavras [] = ([],[])
numerarPalavras (x) = unzip y
                      where y = zip' x

zip' (x) = zip [1..] y
                 where y = words x

--Função principal:
contaPalavras (x) = last y
                    where y = fst' x

{-Questão 6: Declare uma função que receba como parâmetro uma String e retorne uma dupla com
o caractere que ocorreu o maior número de vezes nessa String e o número de ocorrências.-}


 
filter' (x) = filter (\n -> n /=' ') x

zip'' [] = []
zip'' (x:xs) = (x,1) : zip'' xs







