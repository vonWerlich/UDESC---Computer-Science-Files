Algoritmo "Sistema de segurança da @Metal"
// Kauan Henrique Werlich
// Data atual  : 23/06/2021
// O programa abaixo não funciona adequadamente por causa do comando alarme(),
Var

cod_evento : inteiro
ligacao : caractere

Inicio

escreval ("Digite o código:")
escreval ("0 - Entrada de pessoa não autorizada")
escreval ("1 - Máquina de produção parada")
escreval ("2 - Matéria-prima espalhada")
escreval ("3 - Acidente de trabalho")
escreval ("4 - Falta de luz")
leia (cod_evento)

se (cod_evento <> 0) e (cod_evento <> 1) e (cod_evento <> 2)  e (cod_evento <> 3) e (cod_evento <> 4) entao
escreval ("Erro no valor do código, por favor insira um dos códigos listados acima.")
fimse

se cod_evento = 0 entao
escreval("Ligar para a segurança - ramal 0.")
fimse

se cod_evento = 1 entao
escreval ("Ligar para a manutenção - ramal 9.")
fimse

se cod_evento = 2 entao
escreval ("Esvaziar o recinto e proximidades.")
alarme()
escreval ("Informe a manutenção: ramal 9.")
fimse

se cod_evento = 3 entao
escreval ("Ligar para os bombeiros: 193")
alarme()
escreval ("Você conseguiu ligar? (escreva SIM ou NAO")
leia (ligacao)
  se (ligacao = "NAO")  ou (ligacao = "Nao") ou (ligacao = "nao") entao
  escreval ("Ligue para a segurança – ramal 0.")
  fimse
fimse

se cod_evento = 4 entao
escreval("Esvaziar o recinto e proximidades.")
fimse

Fimalgoritmo