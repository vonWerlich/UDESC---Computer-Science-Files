Algoritmo "Três valores em ordem decrescente"
//Kauan Henrique Werlich
//o programa ordena três números inteiros e diferntes entre si.
//não funciona com dois ou três números iguais
Var

 a,b,c :Inteiro

Inicio
 escreval ("Digite o primeiro número:")
 leia (a)
 escreval ("Digite o segundo número:")
 leia (b)
 escreval ("Digite o terceiro número:")
 leia (c)
 
   se (a>b) e (b>c) entao
   escreval (a,b,c)
   senao
     se (a>c) e (c>b) entao
     escreval (a,c,b)
     senao
       se (a>b) e (c>a) entao
       escreval (c,a,b)
       senao
         se (b>c) e (c>a) entao
         escreval (b,c,a)
         senao
           se (b>a) e (a>c) entao
           escreval (b,a,c)
           senao
             se (c>b) e (b>a) entao
             escreval (c,b,a)
             senao
             escreval ("Erro na entrada dos números")
             fimse
           fimse
         fimse
       fimse
     fimse
   fimse
 
Fimalgoritmo