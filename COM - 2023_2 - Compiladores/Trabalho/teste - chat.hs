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
            |Const Integer deriving Show

--expr :: Parsec String u Expr
expr = buildExpressionParser tabela fator
       <?> "expression"

--fator :: Parsec String u Expr
fator = parens expr
       <|> fmap Const natural
       <?> "simple expression"

--partida :: Parsec String u Expr
partida = do
    e <- expr
    eof
    return e

main = do
    putStr "Expressão:"
    e <- getLine 
    case runParser partida [] "Expressoes" e of
        Left er -> print er
        Right v -> (print v)