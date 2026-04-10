Algoritmo "Altura e sexo de 50 pessoas"
// Kauan Henrique Werlich
// O programa foi alterado para receber a variável sexo tanto em letra maiúscula quanto minúscula
//
Var
num_pessoas,num_M,num_F: inteiro
altura,maior_altura,menor_altura,soma_F,media_F,percentual: real
sexo: caracter

Inicio
soma_F <- 0
num_M <- 0
num_F <- 0
num_pessoas <- 1
maior_altura <- 0
menor_altura<- 0

ENQUANTO (num_pessoas <= 2) FACA
    escreval("Digite a altura da pessoa em metros:")
    leia(altura)
    escreval ("Digite o sexo da pessoa(M para masculino e F para feminino):")
    leia (sexo)
    
    se (sexo = "F")ou(sexo = "f") entao
    soma_F <- soma_F + altura
    num_F <- num_F + 1
    fimse

    se (sexo = "M")ou(sexo = "m") entao
    num_M <- num_M + 1
    fimse
    
    se (maior_altura < altura) entao
    maior_altura<- altura
    fimse
    se (menor_altura > altura) entao
    menor_altura<- altura
    fimse
    
    num_pessoas <- num_pessoas + 1

FIMENQUANTO

   media_F <- soma_F/(num_F)
   escreval("Média de altura das mulheres:", media_F)
   
   escreval("Maior altura:", maior_altura)
   escreval("Menor altura:", menor_altura)
   escreval("Numero de homens:", num_M)
   
   se (num_F = num_M) e (num_F <> 0) entao
   escreval ("O número de homens é igual ao de mulheres.")
     senao
     se (num_F > num_M) e num_M <> 0 entao
     percentual <- (1 - (num_F/num_M))
     escreval ("O número de mulheres é", percentual, " % maior que o de homens.")
       senao
       se (num_M > num_F) e num_F <> 0 entao
       percentual <- (1 - (num_M/num_F))
       escreval ("O número de homens é", percentual, " % maior que o de mulheres.")
       fimse
     fimse
   fimse
Fimalgoritmo