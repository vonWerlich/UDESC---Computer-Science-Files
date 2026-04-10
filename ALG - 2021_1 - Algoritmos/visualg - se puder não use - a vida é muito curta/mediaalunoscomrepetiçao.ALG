Algoritmo "semnome"
Var
nome:caracter
nota1, nota2, media: real
num_alunos: inteiro
Inicio
num_alunos <- 1
ENQUANTO ( num_alunos <= 3 ) FACA
escreval("Digite nome do aluno")
leia(nome)
escreval("Digite 2 notas do aluno")
leia(nota1)
leia(nota2)
media<- (nota1 + nota2 )/2
escreva("Nome do aluno:", nome, " teve média:", media)
num_alunos<- num_alunos + 1
FIMENQUANTO
Fimalgoritmo
