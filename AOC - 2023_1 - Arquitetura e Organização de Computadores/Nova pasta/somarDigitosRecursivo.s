# autor: Kauan Henrique Werlich
# disciplina: Arquitetura e Organização de Computadores (AOC)
# esse programa é parecido com o do exercício anterior, só com alguns
# passos a menos
	.data
texto: # escrever \n após imprimir número
	.asciiz "\n"
	
	.text
	.globl main
main:
	li $v0, 5 # ori $v0,$zero, 5
	syscall
	ori $a0, $v0, 0 # $a0 = $v0 => ler número para somar dígitos
	beq $a0, $zero, end # se número lido for 0, terminar programa
	
	jal dividePorDez # salta para a função
	
	ori $a0, $v0, 0 # $a0 = $v0
	li $v0, 1 # código para imprimir inteiro
	syscall
	
	la $a0, texto
	li $v0, 4  # print \n após o inteiro
    	syscall
    	
	j main # continue lendo outros números
end:
	li $v0, 10 # código para terminar o programa
	syscall
dividePorDez:
	beq $a0, $zero, fatorParada # se $a0 for igual a 0, vá para o branch
	
	addi $sp, $sp, -8 # deslocando o topo da pilha 8 bytes
	sw $s0, 0($sp) # armazenando $ra nos últimos 4 bytes da pilha
	sw $ra, 4($sp) # armazenando $s0 nos 4 bytes após $ra
	
	divu $a0, $a0, 10 # divide $a0 por 10 e põe o quociente em $a0. 
	mfhi $s0 # move o conteúdo de HI (resto) para $s0
	
	jal dividePorDez # recursão

	add $v0, $s0, $v0 # somar os valores armazenados na pilha
	
	# restaurar
	lw $s0, 0($sp) # restaura valor de $s0
	lw $ra, 4($sp) # restaura valor de $ra
	addi $sp, $sp, 8 # ajustando topo da pilha para "excluir" os itens
	
	jr $ra # vai para o endereço salvo em $ra
	
fatorParada: # se $a0 for igual a 0, vá para o último endereço salvo
	add $v0, $zero, $zero
	jr $ra