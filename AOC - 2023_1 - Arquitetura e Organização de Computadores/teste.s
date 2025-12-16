	.text
	.globl main
main:
	ori $v0,$zero, 5
	syscall
	ori $a0, $v0, 0
	ori $v0, $zero, 5
	syscall
	ori $a1, $v0, 0
	ori $v0, $zero, 0
	jal contaOcorrencias
	ori $a0, $v0, 0
	ori $v0, $zero, 1
	syscall
	j end
contaOcorrencias:
	addi $sp, $sp, -12
	sw $ra, 0($sp)
	sw $t0, 4($sp)
	beq $a0, $zero, count
	divu $a0, $a0, 10
	mfhi $t0
	sw $t0, 8($sp)
	jal contaOcorrencias
	lw $t0, 8($sp)
count:
	bne $a1, $t0, jump
	addi $v0, $v0, 1
jump:
	lw $t0, 4($sp)
	lw $ra, 0($sp)
	addi $sp, $sp, 12
	jr $ra
end:
	li $v0, 10
	syscall