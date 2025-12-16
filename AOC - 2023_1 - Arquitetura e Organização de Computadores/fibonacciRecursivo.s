# autor: Kauan Henrique Werlich
# disciplina: Arquitetura e Organização de Computadores (AOC)
	.text
	.globl main
main:
	li $v0, 5 # ler inteiro
	syscall
	add $a0, $v0, $zero # $a0 = $v0
	jal fibonacci_Rec
	
	move $a0, $v0 # colocar a saída da função para ser impressa no console
	li $v0, 1 # imprimir inteiro
	syscall
end:
	li $v0, 10 # cõdigo para terminar o programa
	syscall
	
fibonacci_Rec:
	slti $t0, $a0, 2
	bne $t0, $zero, fator_parada # se $a0 for diferente de 0 (igual a 1) vá para o branch
	
	# salvar contexto
	addi $sp, $sp, -12 # deslocando o topo da pilha 12 bytes
	sw $s0, 0($sp) # armazenando $s0 nos últimos 4 bytes da pilha
	sw $s1, 4($sp) # armazenando $s1 nos 4 bytes após $s0
	sw $ra, 8($sp) # armazenando $ra nos 4 bytes após $s1
	
	#código principal da função recursiva
	move $s1, $a0
	addi $a0, $a0, -1
	jal fibonacci_Rec
	move $s0, $v0
	
	addi $a0, $s1, -2
	jal fibonacci_Rec
	move $s1, $v0
	
	add $v0, $s0, $s1
	
	# restaurar
	lw $s0, 0($sp) # restaurando o valor de $s0
	lw $s1, 4($sp) # restaurando o valor de $s1
	lw $ra, 8($sp) # restaurando o valor de $ra
	addi $sp, $sp, 12 # ajustando topo da pilha para "excluir" os itens
	
	jr $ra #retornar
	
fator_parada: # se a entrada for menor que 2, a função retorna 1
	addi $v0, $zero, 1
	jr $ra
