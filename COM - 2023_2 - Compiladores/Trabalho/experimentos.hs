return :: a -> M a
>> :: M a -> M b -> M b --não precisa definir
>>= :: M a -> (a -> M b) -> M b

data M a = MS (String, a) deriving Show

instance Monad M where 
	return x = MS("", x)
	MS m >>= f' = let (s, a) = m in let MS (s', b) = f a in MS(s ++ s',b)
	
instance function M where
	fmap f (MS (s,a) = MS (s, fa)
	
instance Application M where 
	pure x = MS ("", x)
	MS(s1, f) <*> MS (s2, x) = MS(s1 <>s2, f x)
	
erro s = MS("Erro:"++s,())
adv s = MS("Advertencia:"++s,())

verifica(e1 :+: e2) = do (e1', t1) <- verifica e1
		(e2', t2) <- verifica e2
		if t1==t2 then (e1' :+: e2, t1) 
		else if t1 = TInt && t2 == TDouble then
			return (Int Double e1' :+: e2 , TDouble) else
		do {erro "tipos incompatíveis\n"; return (e1' :+: e2', t1)}


--preciso criar uma lista de variáveis da função para pdoer verificar se a variável já está declarada 