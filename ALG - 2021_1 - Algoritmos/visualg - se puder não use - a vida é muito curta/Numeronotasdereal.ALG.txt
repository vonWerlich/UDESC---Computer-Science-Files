Algoritmo "Numeronotasdereal"

//Kauan Henrique Werlich

var

   nReal, n100, n50, n20, n10, n5, n2, n1 : Inteiro
   
inicio

  Escreval("Informe um valor inteiro em Reais(R$): ")
  Leia(nReal)

  n100 <- nReal \ 100
  nReal <- nReal % 100

  n50 <- nReal \ 50
  nReal <- nReal % 50

  n20 <- nReal \ 20
  nReal <- nReal % 20

  n10 <- nReal \ 10
  nReal <- nReal % 10

  n5 <- nReal \ 5
  nReal <- nReal % 5

  n2 <- nReal \ 2
  nReal <- nReal % 2

  n1 <- nReal

  Se n100 <> 0 Entao
  Escreval("O número de notas de 100 é: ", n100)
  Fimse
  Se n50 <> 0 Entao
  Escreval("O número de notas de 50 é: ", n50)
  Fimse
  Se n20 <> 0 Entao
  Escreval("O número de notas de 20 é: ", n20)
  Fimse
  Se n10 <> 0 Entao
  Escreval("O número de notas de 10 é: ", n10)
  Fimse
  Se n5 <> 0 Entao
  Escreval("O número de notas de 5 é: ", n5)
  Fimse
  Se n2 <> 0 Entao
  Escreval("O número de notas de 2 é: ", n2)
  Fimse
  Se n1 <> 0 Entao
  Escreval("O número de notas de 1 é: ", n1)
  Fimse

fimalgoritmo