Algoritmo "Maior de três números inteiros e diferentes"
// Disciplina   : Algoritmos
// Autor(a)    : Kauan Henrique Werlich
// Data atual  : 15/06/2021
Var a: inteiro
    b: inteiro
    c: inteiro


Inicio
escreval("Digite a")
leia (a)
escreval("Digite b")
leia (b)
escreval("Digite c")
leia (c)
SE (a>b) e (a>c)  ENTAO
   escreval (a)
   SENAO
     SE (b>a) e (b>c)  ENTAO
       escreval (b)
       SENAO
         SE (c>a) e (c>b) ENTAO
         escreval (c)
           SENAO escreval ("Alguns dos valores são iguais entre si.")
         FIMSE
     FIMSE
FIMSE
Fimalgoritmo