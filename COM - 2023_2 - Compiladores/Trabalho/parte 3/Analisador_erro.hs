-- Kauan Henrique Werlich        
-- Trabalho Parte 1 Compiladores

-- Implemente em linguagem Haskell, usando a biblioteca de combinadores monádicos
-- Parsec, um analisador sintático para a linguagem definida abaixo, o código
-- intermediário gerado deve ser um uma árvore sintática abstrata representada pelos tipos
-- algébricos de dados definidos no final deste documento. A linguagem deve manipular
-- pelo menos três tipos de dados: int, double e string. As produções para expressões
-- (lógicas, relacionais e aritméticas) devem ser definidas. 

-- Trabalho Parte 2 Compiladores
-- O analisador semântico deve receber como entrada a AST, representada pelo tipo de
-- dado algébrico Programa, fazer a verificação de tipos e retornar uma AST
-- correspondente incluindo as coerções de tipos, erros e advertências deverão ser emitidos
-- no processo.

-------- PARTE 1

import System.IO
import Text.Parsec
import Text.Parsec.Expr
import qualified Text.Parsec.Token as T
import Text.Parsec.Language
import Text.Parsec.Token (GenTokenParser(identifier))
import Data.List
import Control.Monad.State

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

data Var = Id :#: (Tipo, Int) --alteração parte 3
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

parametro = do{t <- tipo; id <- indentifier; return (id:#:(t,0))}

declParametros = do{p <- parametro; ps <- parametros; return (p:ps)}
                 <|> return []

parametros = do{symbol ","; declParametros}
             <|> return []

blocoPrincipal = do {symbol "{"; b <- blocoPrincipal'; symbol "}"; return b}

blocoPrincipal' = do{d <- declaracoes; l <- listaCmd; return (d, l)}

declaracoes = do{t <- tipo; id <- listaId; symbol ";"; ds <- declaracoes; return ([(x:#:(t,0)) | x <- id] ++ ds)}
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
            T.identStart = letter <|> char '_', 
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

-----------   PARTE 2 

data Semantica a = MS (String, a) 
                   deriving Show

instance Functor Semantica where
         fmap f (MS (s, a)) = MS(s, f a)

instance Applicative Semantica where
    pure x = MS("", x)
    MS(s1, f) <*> MS(s2, x) = MS(s1 <> s2, f x)

instance Monad Semantica where
    MS(s, a) >>= f = let MS(s', b) = f a in MS (s++s', b)

red = "\x1b[31m"     -- texto em vermelho
yellow = "\x1b[33m"  -- texto em amarelo
reset = "\x1b[0m"    -- reseta para cor padrão

erro s = MS (red ++ "Erro: " ++ reset ++ s ++ "\n", ())
adv s = MS (yellow ++ "Advertencia: " ++ reset ++ s ++ "\n", ())

data VerTipo = I | D | S | V | E deriving (Eq, Show)

printTipo I = "Int"
printTipo D = "Double"
printTipo S = "String"
printTipo V = "Void"

tipo2 t | t == TInt = I
       | t == TDouble = D
       | t == TString = S
       | t == TVoid = V
       | otherwise = E

varId (id :#: _) = id
varTipo (_ :#: (t, _)) = t

-- função para verificar se a variável está declarada
procIdVar _ [] = E
procIdVar id (lv: lvs) = if varId lv == id
                then tipo2 (varTipo lv)
                else procIdVar id lvs

funcId (id :->: _) = id
funcTipo (_ :->: (_, t)) = t
funcParamentros (_ :->: (lp, _)) = lp

listaFuncId (id, _, _) = id
listaFuncVar (_, var, _) = var
listaFuncBloco (_, _, bloco) = bloco 

procFunc id (fs:fss) = if funcId fs == id 
                       then fs 
                       else procFunc id fss

procIdFunc _ [] = E
procIdFunc id (fs:fss) = if funcId fs == id 
                         then tipo2 (funcTipo fs)
                         else procIdFunc id fss

constante (Const (CInt a)) = I
constante (Neg (Const (CInt a))) = I
constante (Const (CDouble a)) = D
constante (Neg (Const (CDouble a))) = D
constante (Const (CString a)) = S
constante _ = E
 
exprA (a :+: _) = a
exprA (a :-: _) = a
exprA (a :*: _) = a
exprA (a :/: _) = a
exprA a = a

exprB (_ :+: b) = b
exprB (_ :-: b) = b
exprB (_ :*: b) = b
exprB (_ :/: b) = b
exprB b = b


exprO (_ :+: _) a b = (a :+: b)
exprO (_ :-: _) a b = (a :-: b)
exprO (_ :*: _) a b = (a :*: b)
exprO (_ :/: _) a b = (a :/: b)

exprMsg (_ :+: _)  = "+"
exprMsg (_ :-: _)  = "-"
exprMsg (_ :*: _)  = "*"
exprMsg (_ :/: _)  = "/"

intParaDouble (Neg c) = Neg (IntDouble c)
intParaDouble c = IntDouble c

doubleParaInt (Neg c) = Neg (DoubleInt c)
doubleParaInt c = DoubleInt c

verExprBin id' expr (ta, a) (tb, b)
  | ta == E && (tb == I || tb == D) = return (tb, exprO expr a b)
  | (ta == I || ta == D) && tb == E = return (ta, exprO expr a b)
  | ta == D && tb == I = do
    adv ("Na função '" ++ id' ++ "':\nConversão de Int para Double na operação '" ++ exprMsg expr ++ "'")
    return (D, exprO expr a (intParaDouble b))
  | ta == I && tb == D = do
    adv ("Na função '" ++ id' ++ "':\nConversão de Int para Double na operação '" ++ exprMsg expr ++ "'")
    return (D, exprO expr (intParaDouble a) b)
  | ta == D && tb == D = return (D, exprO expr a b)
  | ta == I && tb == I = return (I, exprO expr a b)
  | ta == S && (tb == I || tb == D) = do
    erro ("Na função '" ++ id' ++ "':\nOperação " ++ exprMsg expr ++ " não aceita String nos seus operadores")
    return (tb, exprO expr a b)
  | (ta == I || ta == D) && tb == S = do
    erro ("Na função '" ++ id' ++ "':\nOperação " ++ exprMsg expr ++ " não aceita String nos seus operadores")
    return (ta, exprO expr a b)
  | ta == V || tb == V = do
    erro ("Na função '" ++ id' ++ "':\nOperação " ++ exprMsg expr ++ " não aceita procedimentos nos seus operadores")
    return (E, exprO expr a b)
  | otherwise = return (E, exprO expr a b)

verParametros'' id' (Chamada id lp) lv fs = do
    if length lp == length numP
        then do
            vlp <- verParametros' id id' lp flp lv fs
            return (Chamada id vlp)
        else if length lp > length numP
            then do
                erro ("Na função '" ++ id' ++ "':\n" ++ "Excesso de argumentos na função " ++ id ++ " ")
                return (Chamada id lp)
            else do
                erro ("Na função '" ++ id' ++ "':\n" ++ "Muitos poucos argumentos na chamada de função '" ++ id ++ "'")
                return (Chamada id lp)
    where 
        f = procFunc id fs
        flp = funcParamentros f
        numP = funcParamentros (procFunc id fs)



idChamada (Chamada id _) = id

verParametros' _ _ [] [] _ _ = return []
verParametros' id id' (lp:lps) (fp:fps) lv fs = do
    vlp <- verExpr id' lp lv fs
    vlps <- verParametros' id id' lps fps lv fs

    if fst vlp == I && vp == D
        then do
            adv ("Na função '" ++ id' ++ "':\n"
                 ++ "Conversão de Int para Double na passagem do parâmetro '"
                 ++ idP ++ "' da função '" ++ id ++ "'")
            return ((intParaDouble (snd vlp)):vlps)
    else if fst vlp == D && vp == I
        then do
            adv ("Na função '" ++ id' ++ "':\n"
                 ++ "Conversão de Double para Int na passagem do parÂmetro '"
                 ++ idP ++ "' da função '" ++ id ++ "'")
            return ((doubleParaInt (snd vlp)):vlps)
    else if fst vlp == S && vp /= S
        then do
            erro ("Na função '" ++ id' ++ "':\n"
                  ++ "O parâmetro '" ++ idP ++ "', na função '"
                  ++ id ++ "', do tipo "
                  ++ t ++ " não pode ser atribuído com o tipo " ++ printTipo (fst vlp))
            return ((snd vlp):vlps)
    else return ((snd vlp):vlps)
    where 
        vp = tipo2 (varTipo fp)
        t = printTipo vp
        idP = varId fp


verChamada id' (Chamada id lp) lv fs
  | f == E = do
    erro ("Na função '" ++ id' ++ "':\nA função '" ++ id ++ "' não está definida")
    return chm
  | otherwise = do
    v <- verParametros'' id' chm lv fs
    return v
  where
    chm = (Chamada id lp)
    f = procIdFunc id fs


verExpr _ (Const c) _ _ = return (constante (Const c), (Const c))

verExpr id' (IdVar id) lv _ = do
    if varTipo == E 
        then do
            erro ("Na função '" ++ id' ++ "':\n" ++ "Referência indefinida para a variável '" ++ id ++ "'")
            return (E, (IdVar id))
        else return (varTipo, (IdVar id))
    where 
        varTipo = procIdVar id lv

                               
verExpr id' (Chamada id lp) lv fs = do
    if funcTipo == E
        then do
            erro ("Na função '" ++ id' ++ "':\n"
                ++ "Referencia indefinida para a função '" ++ id ++ "'")
            return (E, (Chamada id lp))
        else do
            vlp <- verChamada id' chm lv fs
            return (funcTipo, vlp)
    where 
        chm = (Chamada id lp)
        funcTipo = procIdFunc id fs
        fp = funcParamentros (procFunc id fs)



verExpr id' expr lv fs = do a <- verExpr id' (exprA expr) lv fs
                            b <- verExpr id' (exprB expr) lv fs
                            verExprBin id' expr a b

exprRA (a :==: _) = a
exprRA (a :/=: _) = a
exprRA (a :<: _) = a
exprRA (a :>: _) = a
exprRA (a :<=: _) = a
exprRA (a :>=: _) = a

exprRB (_ :==:b) = b
exprRB (_ :/=:b) = b
exprRB (_ :<: b) = b
exprRB (_ :>: b) = b
exprRB (_ :<=:b) = b
exprRB (_ :>=:b) = b

exprRO (_ :==: _) a b = (a :==: b)
exprRO (_ :/=: _) a b = (a :/=: b)
exprRO (_ :<: _) a b = (a :<: b)
exprRO (_ :>: _) a b = (a :>: b)
exprRO (_ :<=: _) a b = (a :<=: b)
exprRO (_ :>=: _) a b = (a :>=: b)

exprRMsg (_ :==: _) = "=="
exprRMsg (_ :/=: _) = "/="
exprRMsg (_ :<: _) = "<"
exprRMsg (_ :>: _) = ">"
exprRMsg (_ :<=: _) = "<="
exprRMsg (_ :>=: _) = ">="

verExprR id' exprR lv fs = do
    a <- verExpr id' (exprRA exprR) lv fs
    b <- verExpr id' (exprRB exprR) lv fs
    if fst a == D && fst b == I
        then do
            adv ("Na função '" ++ id' ++ "':\n"
                ++ "Conversão de Int para Double na operação '"
                ++ exprRMsg exprR ++ "'")
            return (exprRO exprR (snd a) (intParaDouble (snd b)))
        else if fst a == I && fst b == D 
            then do 
                adv ("Na função '" ++ id' ++ "':\n"
                    ++ "Conversão de Int para Double na operação '"
                    ++ exprRMsg exprR ++ "'")
                return (exprRO exprR (intParaDouble (snd a)) (snd b)) 
        else if fst a == S && (fst b == I || fst b == D)
            then do
                erro ("Na função '" ++ id' ++ "':\n"
                    ++ "Operacao " ++ exprRMsg exprR 
                    ++ " so aceita String se estiver nos dois operadores")
                return (exprRO exprR (snd a) (snd b))
        else if (fst a == I || fst a == D) && fst b == S
            then do
                erro ("Na função '" ++ id' ++ "':\n" 
                    ++ "Operacao " ++ exprRMsg exprR 
                    ++ " so aceita String se estiver nos dois operadores")
                return (exprRO exprR (snd a) (snd b))
        else if fst a == V || fst b == V 
            then do
                erro ("Na função '" ++ id' ++ "':\n"
                    ++ "Operacao " ++ exprRMsg exprR 
                    ++ " so aceita String se estiver nos dois operadores")
                return (exprRO exprR (snd a) (snd b))
        else return (exprRO exprR (snd a) (snd b))

exprLA (a :&: _) = a
exprLA (a :|: _) = a

exprLB (_ :&: b) = b
exprLB (_ :|: b) = b

exprLO (_ :&: _) a b = (a :&: b)
exprLO (_ :|: _) a b = (a :|: b)

verExprL id' (Rel exprR) lv fs = do vr <- verExprR id' exprR lv fs
                                    return (Rel vr)
verExprL id' (Not (Rel exprR)) lv fs = do vr <- verExprR id' exprR lv fs
                                          return (Not (Rel vr))
verExprL id' (Not exprL) lv fs = do a <- verExprL id' (exprLA exprL) lv fs
                                    b <- verExprL id' (exprLB exprL) lv fs
                                    return (Not ((exprLO exprL a b)))                           
verExprL id' exprL lv fs = do a <- verExprL id' (exprLA exprL) lv fs
                              b <- verExprL id' (exprLB exprL) lv fs
                              return (exprLO exprL a b)


elemExiste  _ i [] = False
elemExiste f id (e:es) |f id == f e = True
                       |otherwise = elemExiste f id es

verAtrib' id' (Atrib id expr) lv fs = do v <- verExpr id' expr lv fs
                                         return (Atrib id (snd v))

verAtrib id' (Atrib id expr) lv fs = do
    v <- verExpr id' expr lv fs
    if fst v == I && var == D 
        then do
            adv ("Na função '" ++ id' ++ "':\n"
                ++ "Conversão de Int para Double na atribuição de '" ++ id ++ "'")
            return (Atrib id (intParaDouble (snd v)))
    else if fst v == D && var == I
        then do
            adv ("Na função '" ++ id' ++ "':\n"
                ++ "Conversão de Double para Int na atribuição de '" ++ id ++ "'")
            return (Atrib id (doubleParaInt (snd v)))
    else if fst v == S && var /= S
        then do
            erro ("Na função '" ++ id' ++ "':\n" 
                ++ "A variável '" ++ id ++ "' do tipo " 
                ++ t ++ " não pode ser atribuida com o tipo " ++ printTipo (fst v))
            return (Atrib id (snd v))
    else if fst v /= S && var == S
        then do
            erro ("Na função '" ++ id' ++ "':\n" 
                ++ "A variável '" ++ id ++ "' do tipo " 
                ++ t ++ " não pode ser atribuida com o tipo " ++ printTipo (fst v))
            return (Atrib id (snd v))
    else return (Atrib id (snd v))
    where 
        var = procIdVar id lv
        t = printTipo var


verRet id' (Ret (Just expr)) t lv fs = do
    v <- verExpr id' expr lv fs
    if fst v == I && t == D
        then do
            adv ("Na função '" ++ id' ++ "':\n"
                ++ "Conversão de Int para Double no retorno")
            return (Ret (Just (intParaDouble (snd v))))
    else if fst v == D && t == I
        then do
            adv ("Na função '" ++ id' ++ "':\n"
                ++ "Conversão de Double para Int no retorno")
            return (Ret (Just (doubleParaInt (snd v))))
    else if fst v /= t && not (t == V && expr == (Const (CInt 0)))
        then do
            erro ("Na função '" ++ id' ++ "':\n" 
                ++ "Tipo do retorno incompatível, se espera "
                ++ printTipo t
                ++ " em vez de " ++ printTipo (fst v))
            return (Ret (Just expr))
    else return (Ret (Just expr))


verProc' id' (Proc id lExpr) lv fs = do
    if length lExpr == length numP
        then do
            vlExpr <- verProc id' lExpr lp lv fs
            return (Proc id vlExpr)
    else if length lExpr > length numP
        then do
            erro ("Na função '" ++ id' ++ "':\n"
                ++ "Excesso de argumentos na funcao " ++ id ++ " ")
            return (Proc id lExpr)
    else do
        erro ("Na função '" ++ id' ++ "':\n"
            ++ "Muito poucos argumentos na chamada de funcao '" ++ id ++ "'")
        return (Proc id lExpr) 
    where 
        f = procFunc id fs
        lp = funcParamentros f
        numP = funcParamentros (procFunc id fs)


verProc _ [] [] lv fs = return []
verProc id' (e:es) (p:ps) lv fs = do
    ve <- verExpr id' e lv fs
    ves <- verProc id' es ps lv fs
    if fst ve == I && vp == D
        then do
            adv ("Na função '" ++ id' ++ "':\n"
                ++ "Conversão de Int para Double em '"
                ++ id ++ "'")
            return ((intParaDouble (snd ve)):ves)
    else if fst ve == D && vp == I
        then do
            adv ("Na função '" ++ id' ++ "':\n"
                ++ "Conversão de Double para Int em '"
                ++ id ++ "'")
            return ((doubleParaInt (snd ve)):ves)
    else if fst ve == S && vp /= S
        then do
            erro ("Na função '" ++ id' ++ "':\n"
                ++ "O parâmetro '" ++ id ++ "' do tipo "
                ++ t ++ " não pode ser atribuído com o tipo " ++ printTipo (fst ve))
            return ((snd ve):ves) 
    else return ((snd ve):ves)                                    
    where
        vp = tipo2 (varTipo p)
        t = printTipo vp
        id = varId p


verComando id' (If exprL b1 b2) t lv fs = do vL <- verExprL id' exprL lv fs
                                             vb1 <- verBloco id' b1 t lv fs
                                             vb2 <- verBloco id' b2 t lv fs
                                             return ( If vL vb1 vb2)

verComando id' (While exprL b) t lv fs = do vL <- verExprL id' exprL lv fs
                                            vb <- verBloco id' b t lv fs
                                            return (While vL vb)

verComando id' (Atrib id expr) _ lv fs = if elemExiste varId var lv
                                        then do v <- verAtrib id' atr lv fs
                                                return v
                                        else do erro ("Na função '" ++ id' ++ "':\n"
                                                      ++ "O identidicador '" ++ id 
                                                      ++ "' esta indefinido")
                                                v' <- verAtrib' id' atr lv fs
                                                return v'
                                        where 
                                             atr = (Atrib id expr)
                                             var id = (id :#: (TVoid, 0))
                                      
verComando _ (Leitura id) _ _ _ = return (Leitura id)
verComando id' (Imp expr) _ lv fs = do v <- verExpr id' expr lv fs
                                       return (Imp (snd v))

-- Para retorno de Função precisa da tripla
verComando id' (Ret (Just expr)) t lv fs = do v <- verRet id' r t lv fs
                                              return v
                                           where 
                                              r = (Ret (Just expr))

verComando id' (Ret Nothing) t _ _ = do if t /= V
                                        then do erro ("Na função '" ++ id' ++ "':\n" 
                                                       ++ "Tipo do retorno icompativel, se espera "
                                                       ++ printTipo t)
                                                return (Ret Nothing)
                                        else return (Ret Nothing)

verComando id' (Proc id lExpr) _ lv fs = do if f == E
                                             then do erro ("Na função '" ++ id' ++ "':\n"
                                                           ++ "A função '" ++ id ++ "' não esta definida")
                                                     return prc
                                            else do v <- verProc' id' prc lv fs
                                                    return v
                                        where 
                                             prc = (Proc id lExpr)
                                             f = procIdFunc id fs
                                       
verBloco :: Id ->Bloco -> VerTipo -> [Var] -> [Funcao] -> Semantica Bloco
verBloco _ [] _ _ _ = return []
verBloco id (b:bs) t lv fs = do vb <- (verComando id b t lv fs)
                                vbs <- (verBloco id bs t lv fs)
                                return (vb:vbs)

verReptFunc [] = (False, "")
verReptFunc (fs:fss) |elemExiste funcId fs fss = (True, funcId fs)
                     |otherwise = verReptFunc fss

verReptVar [] = (False, "")
verReptVar (lv:lvs) |elemExiste varId lv lvs = (True, varId lv)
                    |otherwise = verReptVar lvs

verReptFuncParametro [] = return True
verReptFuncParametro (fs:fss) = do let v = verReptVar (funcParamentros fs)
                                   if fst v
                                   then do erro ("Na função '" ++ id ++ "':\n"
                                                 ++ "O parametro '" ++ snd v ++ "' foi declarado mais de uma vez")
                                           return False
                                   else return True
                                where
                                        id = funcId fs

verFuncoes fs = do let f = verReptFunc fs
                   if fst f
                   then do erro("A função '" ++ snd f ++ "' foi declarada mais de uma vez")
                           return False
                   else return True

verVariaveis id' lv = do let v = verReptVar lv
                         if fst v
                         then do erro ("Na função '" ++ id' ++ "':\n"
                                        ++ "A variável '" ++ snd v ++ "' foi declarada mais de uma vez")
                                 return False
                         else return True                 

verFuncao f fs = do vlv <- verVariaveis id lv
                    if vlv
                    then do vb <- verBloco id b t lv fs
                            return (id, lv, vb)
                    else return f
                    where 
                         id = listaFuncId f
                         t = procIdFunc id fs
                         lv = (listaFuncVar f) ++ (funcParamentros (procFunc id fs))
                         b = listaFuncBloco f

verListaFuncoes [] _ = return []
verListaFuncoes (lf:lfs) fs = do vlf <- (verFuncao lf fs)
                                 vlfs <- (verListaFuncoes lfs fs)
                                 return (vlf:vlfs)
                        
semantico (Prog fs lf lv b) = do vfs <- verFuncoes fs
                                 vlp <- verReptFuncParametro fs
                                 vlv <- verVariaveis "main" lv
                                 if vfs
                                 then do 
                                        vlf <- verListaFuncoes lf fs
                                        if vlv
                                        then do
                                                vb <- verBloco "main" b V lv fs
                                                return (Prog fs vlf lv vb)
                                        else return (Prog fs vlf lv b) 
                                 else return (Prog fs lf lv b)

printSemantica' p = do putStrLn (fst p)
                       print (snd p)

printSemantica p = do let seman = semantico p
                      case seman of
                        MS p -> printSemantica' p




infoVar [] s = error $ "posVar: Variavel " ++ s ++ " nao declarada\n" 
infoVar (i:#:tp:vs) s = if i == s then tp else  infoVar vs s

tipoFun [] s = error $ "Funcao " ++ s ++ " nao declarada\n"
tipoFun (i:->: (ps, t):fs) s = if i == s then  t else tipoFun fs s


genInt i | i < 6 = "\ticonst_" ++ show i ++ "\n"
         | i < 128 = "\tbipush " ++ show i ++ "\n"
		 | otherwise = "\tldc " ++ show i ++ "\n"
 
genOp TInt   s  = "\ti" ++ s ++ "\n"
genOp TDouble s = "\td" ++ s ++ "\n"
genOp _      s  = error "genOp: tipo invalido\n" 

genTipo TInt    = "i"
genTipo TDouble = "d"
genTipo TString = "a"

genAtrib TInt    TDouble pos = "\td2i\n\tistore " ++ show pos ++ "\n"
genAtrib TDouble TInt    pos = "\ti2d\n\tdstore " ++ show pos ++ "\n"
genAtrib TString TString pos = "\tastore " ++ show pos ++ "\n"
genAtrib tl tr pos          = if tl == tr then "\t" ++ genTipo tl ++ "store " ++ show pos ++ "\n" else error "genAtrib: tipos incompativeis\n"

tipoArg TInt    = "I"
tipoArg TDouble = "D"
tipoArg TVoid   = "V"
tipoArg TString = "Ljava/lang/String;"

genArgs ts = concat (map tipoArg ts)

genCab nome = return (".class public " ++ nome ++ 
                      "\n.super java/lang/Object\n\n.method public <init>()V\n\taload_0\n\tinvokenonvirtual java/lang/Object/<init>()V\n\treturn\n.end method\n\n")

genMainCab s l = return (".method public static main([Ljava/lang/String;)V" ++
                         "\n\t.limit stack " ++ show s ++
                         "\n\t.limit locals " ++ show l ++ "\n\n")

genProg nome (Prog fun cfun tab b) = do c <- genCab nome 
                                        mc <- genMainCab 4 4 
                                        b' <- genBloco tab fun b
                                        return (c++mc++b'++"\n.end method\n")
genBloco tab fun b = do {b' <- mapM (genCmd tab fun) b; return (concat b')} 


genRel TDouble TDouble l s = "\tdcmpl\n\tif"++s++" "++l++"\n"	
genRel TInt    TInt l s    = "\tif_icmp"++s++" "++l++"\n"
genRel TString TString l s = if s == "eq" || s == "ne" then "\tif_acmp"++s++" "++l++"\n" else error ("genRel:Comparacao invalida com strings\n")
genRel _ _ _ _             = error "genRel: Comparacao nao implementada" 


genExprR tab fun v f (e1:==:e2) = do {(t1, e1') <- genExpr tab fun e1; (t2,e2') <- genExpr tab fun e2; return (e1'++e2'++genRel t1 t2 v "eq"++"\tgoto "++f++"\n")}  
genExprR tab fun v f (e1:/=:e2) = do {(t1, e1') <- genExpr tab fun e1; (t2,e2') <- genExpr tab fun e2; return (e1'++e2'++genRel t1 t2 v "ne"++"\tgoto "++f++"\n")}
genExprR tab fun v f (e1:<:e2)  = do {(t1, e1') <- genExpr tab fun e1; (t2,e2') <- genExpr tab fun e2; return (e1'++e2'++genRel t1 t2 v "lt"++"\tgoto "++f++"\n")}
genExprR tab fun v f (e1:<=:e2) = do {(t1, e1') <- genExpr tab fun e1; (t2,e2') <- genExpr tab fun e2; return (e1'++e2'++genRel t1 t2 v "le"++"\tgoto "++f++"\n")}
genExprR tab fun v f (e1:>:e2)  = do {(t1, e1') <- genExpr tab fun e1; (t2,e2') <- genExpr tab fun e2; return (e1'++e2'++genRel t1 t2 v "gt"++"\tgoto "++f++"\n")}
genExprR tab fun v f (e1:>=:e2) = do {(t1, e1') <- genExpr tab fun e1; (t2,e2') <- genExpr tab fun e2; return (e1'++e2'++genRel t1 t2 v "ge"++"\tgoto "++f++"\n")}

novoLabel :: Control.Monad.State.State Int String
novoLabel = do {n <- get; put (n+1); return ("l"++show n)}


genExprL tab fun v f (e1:&:e2) = do {l1 <- novoLabel; e1' <- genExprL tab fun l1 f e1; e2' <- genExprL tab fun v f e2; return (e1'++l1++":\n"++e2')}
genExprL tab fun v f (e1:|:e2) = do {l1 <- novoLabel; e1' <- genExprL tab fun v l1 e1; e2' <- genExprL tab fun v f e2; return (e1'++l1++":\n"++e2')}
genExprL tab fun v f (Not e)   = do {e' <- genExprL tab fun f v e; return e'}
genExprL tab fun v f (Rel e)   = do {e' <- genExprR tab fun v f e; return e'}


genCmd tab fun (While e b) = do {li <- novoLabel; lv <- novoLabel; lf <- novoLabel; e' <- genExprL tab fun lv lf e; b' <- genBloco tab fun b; return (li++":\n"++e'++lv++":\n"++b'++"\tgoto "++li++"\n"++lf++":\n")}
genCmd tab fun (Atrib i e) = do {(tr, e') <- genExpr tab fun e; let (tl, pos) = infoVar tab i in return (e' ++ genAtrib tl tr pos)}
genCmd tab fun (Imp e) = do {(t, e') <- genExpr tab fun e; return ("\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n" ++ e' ++ "\tinvokevirtual java/io/PrintStream/println(" ++ tipoArg t ++")V\n")} 
genCmd tab fun (Ret Nothing)  = return "\treturn\n"
genCmd tab fun (Ret (Just e)) = do {(t, e') <- genExpr tab fun e; return (e'++"\t"++genTipo t++"return\n")}
genCmd tab fun _ = return ""

genExpr tab fun (IdVar i) = do {let (t, p) = infoVar tab i in return (t, "\t" ++ genTipo t ++ "load " ++ show p ++ "\n")}
genExpr tab fun (Const (CInt i)) = return (TInt, genInt i)
genExpr tab fun (Const (CDouble d)) = return (TDouble, "\tldc2_w " ++ show d ++ "\n")
genExpr tab fun (Lit s) = return (TString, "\tldc " ++ "\"" ++ s ++ "\"" ++ "\n")
genExpr tab fun (IntDouble e) = do {(_, e') <- genExpr tab fun e; return (TDouble, e' ++ "\ti2d\n")}
genExpr tab fun (DoubleInt e) = do {(_, e') <- genExpr tab fun e; return (TInt, e' ++ "\td2i\n")}   
genExpr tab fun (Neg e) = do {(t, e') <- genExpr tab fun e; return (t, genOp t "neg")}
genExpr tab fun (Chamada i es) = do {es' <- mapM (genExpr tab fun) es; return (tipoFun fun i, concat (map snd es') ++ "\tinvokestatic "++i++"("++genArgs (map fst es')++")"++tipoArg (tipoFun fun i) ++ "\n")} 
genExpr tab fun (e1 :+: e2) = do {(t1, e1') <- genExpr tab fun e1; (t2, e2') <- genExpr tab fun e2; return (t1, e1' ++ e2' ++ genOp t1 "add")}
genExpr tab fun (e1 :-: e2) = do {(t1, e1') <- genExpr tab fun e1; (t2, e2') <- genExpr tab fun e2; return (t1, e1' ++ e2' ++ genOp t1 "sub")}
genExpr tab fun (e1 :*: e2) = do {(t1, e1') <- genExpr tab fun e1; (t2, e2') <- genExpr tab fun e2; return (t1, e1' ++ e2' ++ genOp t1 "mul")}
genExpr tab fun (e1 :/: e2) = do {(t1, e1') <- genExpr tab fun e1; (t2, e2') <- genExpr tab fun e2; return (t1, e1' ++ e2' ++ genOp t1 "div")}

gerar nome p = fst $ runState (genProg nome p) 0 

tab  = ["x":#:(TDouble, 1), "a":#:(TInt, 3)]
tfun = ["maior" :->: (["a":#:(TInt, 0), "b":#:(TInt, 0)], TInt)]
 
e1 = (IdVar "x" :+: ((Const (CDouble 2)) :*: IntDouble (IdVar "a")))
e2 = (IdVar "x" :+: IntDouble (Chamada "maior" [(Const (CInt 1)), IdVar "a"]))
e3 = (IdVar "a" :+: Chamada "maior" [(Const (CInt 1)), IdVar "a"])


-- função que lê um .txt com um programa e retorna a árvore sintática se o
-- programa estiver no formato esperado -> caso contrário, o parser dá erro
main = do input <- readFile "texto.txt"
          let sin = parserE input
          case sin of 
                Left er -> print er
                Right v -> printSemantica v