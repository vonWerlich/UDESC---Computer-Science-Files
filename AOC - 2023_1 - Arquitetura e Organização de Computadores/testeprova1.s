	.text
	.globl main
main: 
	addiu $a0, $zero, 4
	jal soma
	
	# imprimir resultado
	addu $a0, $zero, $v0
	addiu $v0, $zero, 1
	syscall
end:
	addiu $v0, $zero, 10
	syscall
soma: 
	bne $a0, $zero, soma_corpo
	addiu $v0, $zero, 0
	jr $ra
soma_corpo:
	# salvar contexto
	addi $sp, $sp, -8
	sw $a0, 0($sp)	
	sw $a0, 4($sp)
	
	# código principal
	addu $s0, $zero, $a0
	addi $a0, $a0, -1
	jal soma
	add $v0, $v0, $s0
	
	# restaurar contexto
	lw $s0, 0 ($sp)
	lw $s0, 4 ($sp)
	addi $sp, $sp, 8
	
	# retorna
	jr $ra
	
	