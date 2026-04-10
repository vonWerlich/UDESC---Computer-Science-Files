Algoritmo "Preço do produto a partir do código informado"
//Kauan Henrique Werlich
//Resolução do exercício 2.8 da página 47, livro Forbellone-Eberspächer
//O algoritmo só calcula o preço de um produto por vez
Var

preco, preco1, preco2, preco3, preco4 : real
modop : inteiro

Inicio

escreval ("Digite o preço do produto:")
leia (preco)
escreval ("Escolha a opção de pagamento:")
escreval ("Para pagamento à vista em dinheiro ou cheque, digite 1")
escreval ("Para pagamento à vista no cartão de crédito, digite 2")
escreval ("Para pagamento em duas vezes, digite 3")
escreval ("Para pagamento em três vezes, digite 4")
leia (modop)

preco1 <-  (preco*0.9)
preco2 <-  (preco*0.95)
preco3 <-  (preco)
preco4 <-  (preco*1.1)

se (preco <= 0) entao
escreval ("Erro no preço")
senao
  se (modop = 1) entao
  escreval ("O preço a ser pago é:", preco1)
  senao
     se (modop = 2) entao
     escreval ("O preço a ser pago é:", preco2)
     senao
       se (modop = 3) entao
       escreval ("O preço a ser pago é:", preco3)
       senao
         se (modop = 4) entao
         escreval ("O preco a ser pago é:", preco4)
         senao
         escreval ("Erro no modo de pagamento")
         fimse
       fimse
     fimse
   fimse
fimse

Fimalgoritmo