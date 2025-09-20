module Lista1
(ehTriangulo
,tipoTriangulo
,triangulo
,somaPares
,somaPot2m
,primo) where

ehTriangulo a b c =  (a + b) > c && (a + c) > b &&  (b + c) > a 

tipoTriangulo a b c = if a == b && a == c then  "equilatero" else
                      if a == b || b == c || a == c then   "isosceles" else "escaleno"

triangulo a b c = if (a + b) > c && (a + c) > b &&  (b + c) > a  then if a == b && a == c then  "equilatero" else
                      if a == b || b == c || a == c then   "isosceles" else "escaleno" else "nao eh um triangulo"

somaPares  :: ( Int  ->  Int ) 
somaPares n | n == 0 ||n==1    =  0
            | n > 0     = if rem n 2 == 0 then somaPares (n - 2) + n else somaPares (n-1)

somaPot2m :: Int-> Int -> Int
somaPot2m m n | n ==0 = m
              | n>0 = somaPot2m m (n-1) + (m*(2^n))



divisor :: Int -> [Int]
divisor n = [ i | i <- [2..n], n `mod` i == 0]  
nmfator :: Int -> Int
nmfator n = length (divisor n)


primo :: Int -> Bool
primo n | nmfator n == 1 = True
        | nmfator n > 1 = False