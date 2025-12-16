module GenBytecode where

import Control.Monad.State


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


novoLabel::State Int String 
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
