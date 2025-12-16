# autor: Kauan Henrique Werlich
# disciplina: Arquitetura e Organização de Computadores (AOC)
	.text
	.globl main
main:
	li $v0, 5
	syscall
	move $a0, $v0
	jal somaAteN
	move $a0, $v0
	li $v0, 1
	syscall # imprimir
	
end:
	li $v0, 10
	syscall
somaAteN:
	# if ($a0 < 1)
	blt $a0, 1, fat_parada # pode ser feito com "beq $a0, $zero, fat_parada",
	# mas esse é melhor por que só funciona para números positivos
	
	# salvar contexto
	addi $sp, $sp, -8
	sw $s0, 0($sp)
	sw $ra, 4($sp)
	# código principal com chamada recursiva
	move $s0, $a0
	addi $a0, $a0, -1
	jal somaAteN # $v0 = fatorial($a0 -1)
	add $v0, $v0, $s0 # $v0 += $s0
	# restaurar
	lw $s0, 0($sp)
	lw $ra, 4($sp)
	addi $sp, $sp, 8
	# retornar
	jr $ra
fat_parada:
	ori $v0, $zero, 0
	jr $ra