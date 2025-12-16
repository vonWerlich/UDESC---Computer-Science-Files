	.text
	.globl main
main:
	li $v0, 5  # get n
    	syscall
    	
    	add $s1, $v0, $zero # $s1 = n
	li $s0, 1 # $s0 = 1
while:
	mul $s0, $s0, $s1 # $s0 = $s0 * $s1 (32 bits baixos)
	addi $s1, $s1, -1 # $s1 = $s1 - 1
	bnez $s1, while # se $s1 != 0 então vá p/ while
end:
	li $v0, 1  # print result
    	add $a0, $s0, $zero
    	syscall
    	
	li $v0, 10 # Código para encerrar o programa
	syscall # encerra o programa
