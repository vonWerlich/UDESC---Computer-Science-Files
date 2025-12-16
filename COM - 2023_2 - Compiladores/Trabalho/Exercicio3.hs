-- Kauan Henrique Werlich
-- Exercício 3 de Compiladores : Continuando a implementação feita para o Exercício 2,
-- declare uma função posOrdem que percorre o tipo algébrico Expr gerando uma String
-- com a expressão em notação pósfixada.

-- Implementação da função PosOrdem

import Text.Parsec
import Text.Parsec.Expr
import qualified Text.Parsec.Token as T
import Text.Parsec.Language

lingDef = emptyDef
          { T.commentStart      = "{-"
            , T.commentEnd      = "-}"
            , T.commentLine     = "--"
            , T.reservedOpNames = ["+", "-", "/", "*"]
          }

lexico = T.makeTokenParser lingDef
  
natural       = T.natural lexico
symbol        = T.symbol lexico
parens        = T.parens lexico
reservedOp    = T.reservedOp lexico

tabela   = [[prefix "-" Neg], 
            [binario "*" (:*:) AssocLeft, binario "/" (:/:) AssocLeft ],
            [binario "+" (:+:) AssocLeft, binario "-" (:-:) AssocLeft ]
           ]
  
binario  name fun assoc = Infix (do{reservedOp name; return fun }) assoc
prefix   name fun       = Prefix (do{reservedOp name; return fun })

data Expr = Expr :+: Expr 
            |Expr :-: Expr 
            |Expr :*: Expr 
            |Expr :/: Expr 
            |Neg Expr 
            |Const Integer
            deriving Show

expr :: Parsec String s Expr
expr = buildExpressionParser tabela fator
       <?> "expression"

fator :: Parsec String s Expr
fator = parens expr
       <|> do {n <- natural; return (Const n)}
       <?> "simple expression"

partida :: Parsec String s Expr
partida = do {e <- expr; eof; return e}

parserE e = runParser partida [] "Expressoes" e

posOrdem (e1 :+: e2) = posOrdem e1 ++ posOrdem e2 ++ "+ "
posOrdem (e1 :-: e2) = posOrdem e1 ++ posOrdem e2 ++ "- "
posOrdem (e1 :*: e2) = posOrdem e1 ++ posOrdem e2 ++ "* "
posOrdem (e1 :/: e2) = posOrdem e1 ++ posOrdem e2 ++ "/ "
posOrdem (Neg e) = posOrdem e ++ "negate "
posOrdem (Const i) = show i ++ " "

parserExpr s = case parserE s of
                     Left er -> print er
                     Right v -> (putStr (posOrdem v))

main = do putStr "Expressão:"
          e <- getLine 
          parserExpr e