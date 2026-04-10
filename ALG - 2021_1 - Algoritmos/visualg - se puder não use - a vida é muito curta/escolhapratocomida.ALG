Algoritmo "Escolher o prato de comida"
// Kauan Henrique Werlich
// Data atual  : 23/06/2021
//O algoritmo considera a mesma opção de proteína para todas as refeições pedidas
Var
num_refeicoes,opcao_proteina,opcao_prato : inteiro
valor_refeicao,conta : real
entrega: caractere
Inicio
escreval ("Quantas refeições deseja?")
leia (num_refeicoes)

se num_refeicoes < 0 entao
escreval ("Erro no número de refeições")
senao
fimse
escreval ("Escolha a opção:")
escreval ("1 - Arroz, feijão, salada")
escreval ("2 - Macarrão, ervilha, salada")
leia (opcao_prato)

se (opcao_prato <> 1) e (opcao_prato <> 2)  entao
escreval ("Erro na opção do prato")
senao
fimse

valor_refeicao <- 8
conta <- num_refeicoes * valor_refeicao

escreval ("Escolha proteína:")
escreval ("1 - Bife de Panela")
escreval ("2 - Peixe Grelhado")
escreval ("3 - Sem carne")
leia (opcao_proteina)

se (opcao_proteina <> 1) e (opcao_proteina <> 2) e (opcao_proteina <> 3) entao
escreval ("Erro na opção de proteína")
senao
fimse

se opcao_proteina <>3 entao
conta <- (conta + (num_refeicoes * 10))
senao
fimse

escreval ("Precisa de entrega? (responda SIM ou NAO)")
leia (entrega)
se (entrega = "SIM") ou (entrega = "Sim") ou (entrega = "sim") entao
conta <- (conta + 4)
senao
fimse

escreval ("Total:", conta)

Fimalgoritmo