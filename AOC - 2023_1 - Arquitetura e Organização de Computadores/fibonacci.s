#autor: Kauan Werlich
#disciplina: Arquitetura e Organizacao de Computadores (AOC)
	.text
	.globl main
main:
	li $v0, 5  # get n
    	syscall
    	
    	add $s0, $v0, -1 # $s0 = n # contador - 1 (por conta do bgtz)
	add $s1, $zero, 1 # primeiro numero da sequencia
	add $s2, $zero, 1 # segundo numero da sequencia
	
	bgtz $s0, fibonacci # se o contador for maior que zero será diferente de zero
	blez $s0, end # caso contrário, vá para o fim
fibonacci:
	addi $s0, $s0, -1 # $s0 = $s0 - 1 # contador diminui
	
	add $s3, $s2, $zero # guarda o valor de $s2 em $s3
	add $s2, $s2, $s1 # $s2 = $s2 + $s1
	add $s1, $s3, $zero # $s1 recebe o valor guardado em $s3 
	
	bne $s0, $zero, fibonacci # se o contador for diferente de zero, volte ao loop
end:
	li $v0, 1  # print result
    	add $a0, $s2, $zero
    	syscall
    	
	li $v0, 10 # Código para encerrar o programa
	syscall # encerra o programa
