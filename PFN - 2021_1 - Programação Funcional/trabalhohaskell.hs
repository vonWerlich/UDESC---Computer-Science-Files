--Autor: Kauan Henrique Werlich

{-
Tutorial rápido de como usar no GHCI:
1. Chamar a função main;
2. Passar o nome do arquivo que deve ser lido;
3. O programa retorna as palavras alfabeticamente ordenadas com o número das linhas onde essas palavras aparecem.

Essa função só ordenará as palavras com 3 letras ou mais, e só aceita letras sem acentuação e espaços em brancos. Por exemplo, se 
a palavra "Término" for colocada, o progama só lê "Trmino". Além disso, dígitos e pontuação também são ignorados.
-}

import Data.Char -- para usar as funções isLetter (equivalente de isAlpha) e isSpace
import Data.List -- para usar a função sort (que ordena uma lista, no caso desse programa ordenar alfabeticamente)

main = do putStr "Arquivo: "
          nome <- getLine
          txt <- readFile nome -- coloca o texto em string
          let txt' = filter' txt -- filtra se é letra ou espaço em branco
          let txt'' = minuscula txt' -- trasforma o texto todo em minúsculas (para não avaliar palavras com diferença em maiúscula e minúscula de maneira diferente
          let linhas = lines txt'' -- divide o texto em linhas
          let lnumeradas = zip [1..] linhas -- numera as linhas
          let palavras = divpalavras lnumeradas -- numera as palavras de acordo com a linha onde estão e também filtra as que tem menos de três letras
          let palavrasinv = inverter palavras -- inverte a ordem das duplas para ordená-las alfabeticamente
          let palavrasordinv = sort palavrasinv -- ordena alfabeticamente as duplas invertidas
          let palavrasord = inverter palavrasordinv -- reordena as duplas invertidas 
          let palavrasagrup = agrupar palavrasord -- agrupa os números das linhas em que uma mesma palavra aparece
          let palavrasagrup' = remduplicataspal palavrasagrup -- remove repetições/duplicatas das linhas
          imprimir palavrasagrup' -- imprime as palavras na tela pulando linha
          print "Fim do texto!"



filter' (x) = filter (\x -> isLetter x || isSpace x) x

minuscula (x) = map toLower x

repetir x = x: repetir x

divpalavras :: [(a, String)] -> [(a, String)]
divpalavras [] = []
divpalavras ((a,b):xs) = zip y w ++divpalavras xs
                       where y = repetir a 
                             z = words b
                             w = filter (\x -> length x >= 3) z

inverter [] = []
inverter ((a,b):xs) = (b,a):inverter xs

agrupar' p [] = [] 
agrupar' p ((i,p'):ds) = if p==p' then i : agrupar' p ds else []

agrupar :: (Eq b) => [(a, b)] -> [([a], b)]
agrupar [] = []
agrupar ((i,p):ds) = (agrupar' p ((i,p):ds),p): agrupar y
                     where y = filter (\(_,a) -> a/=p) ds

removeDuplicatas :: (Eq a) => [a] -> [a]
removeDuplicatas lista = removeDuplicatas' lista []

removeDuplicatas' :: (Eq a) => [a] -> [a] -> [a]
removeDuplicatas' [] _ = []
removeDuplicatas' (x:xs) lista2 | (x `elem` lista2) = removeDuplicatas' xs lista2
                                | otherwise = x : removeDuplicatas' xs (x:lista2)

remduplicataspal [] = []
remduplicataspal (((a),p):xs) = (removeDuplicatas a, p) : remduplicataspal xs

imprimir [] = putStrLn ""
imprimir ((n, l):ls) = do putStr (show n)
                          putStr ".\t"
                          putStrLn l
                          imprimir ls
