-- Kauan Henrique Werlich        
-- Trabalho Parte 1 Compiladores

-- Implemente em linguagem Haskell, usando a biblioteca de combinadores monádicos
-- Parsec, um analisador sintático para a linguagem definida abaixo, o código
-- intermediário gerado deve ser um uma árvore sintática abstrata representada pelos tipos
-- algébricos de dados definidos no final deste documento. A linguagem deve manipular
-- pelo menos três tipos de dados: int, double e string. As produções para expressões
-- (lógicas, relacionais e aritméticas) devem ser definidas. 

import System.IO
import Text.Parsec
import Text.Parsec.Expr
import qualified Text.Parsec.Token as T
import Text.Parsec.Language
import Text.Parsec.Token (GenTokenParser(identifier))

-- representação intermediária
type Id = String

data Tipo =  TDouble 
            |TInt 
            |TString 
            |TVoid
            deriving (Eq, Show)

data TCons =  CDouble Double 
             |CInt Int 
             |CString String
             deriving (Eq, Show)

data Expr =  Expr :+: Expr 
            |Expr :-: Expr 
            |Expr :*: Expr 
            |Expr :/: Expr 
            |Neg Expr 
            |Const TCons 
            |IdVar Id 
            |Chamada Id [Expr] 
            |Lit String 
            |IntDouble Expr 
            |DoubleInt Expr 
            deriving (Eq, Show)

data ExprR =  Expr :==: Expr 
             |Expr :/=: Expr 
             |Expr :<: Expr 
             |Expr :>: Expr 
             |Expr :<=: Expr 
             |Expr :>=: Expr 
             deriving (Eq, Show)

data ExprL = ExprL :&: ExprL 
            |ExprL :|: ExprL 
            |Not ExprL 
            |Rel ExprR
            deriving (Eq, Show)

data Var = Id :#: Tipo 
           deriving (Eq, Show)

data Funcao = Id :->: ([Var], Tipo) 
              deriving (Eq, Show)     

data Programa = Prog [Funcao] [(Id, [Var], Bloco)] [Var] Bloco
                deriving Show

type Bloco = [Comando]

data Comando =   If ExprL Bloco Bloco
                |While ExprL Bloco
                |Atrib Id Expr
                |Leitura Id
                |Imp Expr
                |Ret (Maybe Expr)
                |Proc Id [Expr]
                deriving (Eq, Show)
-- produções
programa = do
    f <- listaFuncoes
    bp <- blocoPrincipal
    let fl = map (\(funcao, _, _) -> funcao) f
        fb = [(id, d, l) | (_, id, (d, l)) <- f]
    return (Prog fl fb (fst bp) (snd bp))
    -- A função map é usada para aplicar uma função a cada elemento da lista f.
    -- A função aplicada pega a primeira parte da tupla (Funcao, String, ([Var], [Comando])),
    -- que é a representação da função. Isso resulta em fl, que é uma lista de objetos Funcao.
    -- A outra parte da tupla é usada para construir fb, que é uma lista de tuplas contendo informações sobre as funções.
    -- fl é uma lista de funções.
    -- fb é uma lista de tuplas, onde cada tupla contém um Id, uma lista de variáveis [Var] e um bloco.
    --(fst bp) é a primeira parte do bloco principal.
    -- snd bp) é a segunda parte do bloco principal.

listaFuncoes = do{f <- funcao; fs <- listaFuncoes; return (f:fs)}
          <|> return []

funcao = do {t <- tipoRetorno; id <- indentifier; p <- parens declParametros; b <- blocoPrincipal;
             return ((id :->: (p, t)), id, b)}

tipoRetorno =     do{t <- tipo; return t}
              <|> do{reserved "void"; return TVoid}

parametro = do{t <- tipo; id <- indentifier; return (id:#:t)}

declParametros = do{p <- parametro; ps <- parametros; return (p:ps)}
                 <|> return []

parametros = do{symbol ","; declParametros}
             <|> return []

blocoPrincipal = do {symbol "{"; b <- blocoPrincipal'; symbol "}"; return b}

blocoPrincipal' = do{d <- declaracoes; l <- listaCmd; return (d, l)}

declaracoes = do{t <- tipo; id <- listaId; symbol ";"; ds <- declaracoes; return ([(x:#:t) | x <- id] ++ ds)}
              <|> return []

tipo =     do{reserved "int"; return TInt}
       <|> do{reserved "double"; return TDouble}
       <|> do{reserved "string"; return TString}

listaId = do{id <- indentifier; ids <- listaId'; return (id:ids)} 

listaId' = do{symbol ","; listaId}
           <|> return []

bloco = do {symbol "{"; l <- listaCmd; symbol "}"; return l}

listaCmd = do {c <- comando; cs <- listaCmd; return (c:cs)}
          <|> return []

listaParametros = do{l <- listaParametros'; return l}
                  <|> return []

listaParametros' = do{e <- expr; l <- listaParametros''; return (e:l)}

listaParametros'' = do{symbol ","; l <-listaParametros'; return l}
                     <|> return []

comando =     do{reserved "return"; el <- tvzExpressao; symbol ";"; return el}
          <|> do{reserved "if"; el <- parens exprL; b <- bloco; s <- senao; return (If el b s)}
          <|> do{reserved "while"; el <- parens exprL; b <- bloco; return (While el b)}
          <|> do{reserved "print"; e <- parens expr; symbol ";"; return (Imp e)}
          <|> do{reserved "read"; id <- parens (indentifier); symbol ";"; return (Leitura id) }
          <|> try comandoId
          <|> try chamadaFuncao

comandoId = do{id <- indentifier; symbol "="; e <- expr; symbol ";"; return (Atrib id e)}
chamadaFuncao = do{id <- indentifier; l <- parens (listaParametros); symbol ";"; return (Proc id l)}

tvzExpressao = do{e <- expr; return (Ret (Just e))}
               <|> return (Ret (Nothing))

senao =    do{reserved "else"; b <- bloco; return b}
        <|>do{return []}

-- Definições da linguagem
lingDef = emptyDef{
            T.commentStart = "{-",
            T.commentEnd = "-}",
            T.commentLine = "--",
            T.identStart = letter<|> char '_', 
            T.identLetter = alphaNum <|> char '_',
            -- Configura palavras reservadas
            T.reservedNames = ["if", "else", "return", "while", "id", "print",
                               "read", "int", "string", "double", "void"]
            }

lexico = T.makeTokenParser lingDef

natural = T.natural lexico
symbol = T.symbol lexico
parens = T.parens lexico
reservedOp = T.reservedOp lexico
indentifier = T.identifier lexico

integer = T.integer lexico
float = T.float lexico
stringLiteral = T.stringLiteral lexico
reserved = T.reserved lexico

-- Tabela de Ordem de operação
tabela   = [[prefix "-" Neg], 
            [binario "*" (:*:) AssocLeft, binario "/" (:/:) AssocLeft ],
            [binario "+" (:+:) AssocLeft, binario "-" (:-:) AssocLeft ]
           ]
tabelaL = [[prefix "!" Not],
           [binario "&&" (:&:) AssocLeft],
           [binario "||" (:|:) AssocLeft]
           ]

binario name nome assoc = Infix (do{reservedOp name; return nome }) assoc
prefix name nome        = Prefix (do{reservedOp name; return nome })

expr = buildExpressionParser tabela fator
       <?> "expression"   
        
fator = parens expr
       <|> try fatorChamadaFuncao
       <|> try fatorVariavel
       <|> try fatorFloat
       <|> try fatorInteiro
       <|> do{s <- stringLiteral; return (Const (CString s))}
       <?> "simple expression"

fatorChamadaFuncao = do{id <- indentifier; vs <- parens (listaParametros); return (Chamada id vs)}
fatorVariavel = do{id <- indentifier; return (IdVar id)}
fatorFloat = do {f <- float; return (Const (CDouble f))}
fatorInteiro = do {n <- natural; return (Const (CInt (fromIntegral n)))}

exprR = do{e1 <- expr; o <- op; e2 <- expr; return (Rel (o e1 e2))}

op =     do {reservedOp "=="; return (:==:)}
     <|> do {reservedOp "/="; return (:/=:)}
     <|> do {reservedOp "<"; return (:<:)}
     <|> do {reservedOp ">"; return (:>:)}
     <|> do {reservedOp "<="; return (:<=:)}
     <|> do {reservedOp ">="; return (:>=:)}

exprL = buildExpressionParser tabelaL fatorL 

fatorL = parens exprL
        <|> do{n <- exprR; return n}
        <?> "simple expression"

partida :: Parsec String u Programa
partida = do {e <- programa; eof; return e}

parserE e = runParser partida [] "Expressoes" e
 
parserExpr s = case parserE s of
                     Left er -> print er
                     Right v -> (print v)

-- função que lê um .txt com um programa e retorna a árvore sintática se o
-- programa estiver no formato esperado -> caso contrário, o parser dá erro
main = do input <- readFile "texto.txt"
          parserExpr input