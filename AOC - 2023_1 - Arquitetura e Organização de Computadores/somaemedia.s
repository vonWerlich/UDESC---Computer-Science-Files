	.data
texto: 
	.asciiz "\nERRO"
	.data
texto2: 
	.asciiz "\n"
	
	.text
	.globl main
main:
	li $s2, 0 # contador
while:
	li $v0, 5  # get n
    	syscall
    	
    	add $s0, $v0, $zero # $s0 = n
    	beq $s0, -1, end # se $s1 = -1 então vá p/ while
    	
	add $s1, $s1, $s0 # $s1 = $s1 + $s0
	add $s2, $s2, 1
	
	bne $s0, -1, while # se $s1 != -1 então vá p/ while
	
end:
	li $v0, 1  # print $s1
    	add $a0, $s1, $zero
    	syscall
    	
    	la $a0, texto2 # print \n depois da soma
	li $v0, 4  
    	syscall
    	
    	beqz $s1, erro  # se o contador for igual a zero, retorna ERRO
    	
    	div $s1, $s2 # soma / contador
    	mfhi $a0  # load high into $a0
    	mflo $a0  # load low into $a0
    	
    	li $v0, 1  # print média
    	syscall
    	
	li $v0, 10 # Código para encerrar o programa
	syscall # encerra o programa
erro:
	la $a0, texto
	li $v0, 4  # print string
    	syscall
    	
    	li $v0, 10 # Código para encerrar o programa
	syscall # encerra o programa
