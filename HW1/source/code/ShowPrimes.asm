.data
	prm: .asciiz "prime"
	opPar: .asciiz "("
	clsPar: .asciiz ")"
	newLine: .asciiz "\n"
	# don't use memory for other variables for better performance.
	# I will use registers to store and retrieve the other variables.
.text
.globl main

main:

	addi $t0,$zero,0
	addi $t1,$zero,1000
	Loop:
		bge $t0,$t1,return0
		move $a0,$t0
		jal is_prime
		move $t3,$v0
		beq $t3,1, print1
		jal print2
		addi $t0,$t0,1
		j Loop
	print1:
		li $v0, 1
		move $a0,$t0
		syscall
		li $v0,4
		la $a0,opPar
		syscall	
		li $v0,4
		la $a0,prm
		syscall
		li $v0,4
		la $a0,clsPar
		syscall
		li $v0,4
		la $a0,newLine
		syscall
		addi $t0,$t0,1
		j Loop
	print2:
		li $v0, 1
		move $a0,$t0
		syscall
		li $v0,4
		la $a0,newLine
		syscall	
		addi $t0,$t0,1
		j Loop
	
	is_prime:
		li $t4,0
		blt $a0,2,ret0
		li $t5,2
		Loop2:
			bge $t5,$a0,check
			div $a0, $t5      
        		mfhi $t6           
        		beq $t6, 0, increment
        		addi $t5,$t5,1
			j Loop2 
		check:
			bgt $t4,0,ret0
			li $v0,1
			jr $ra
		ret0:
			li $v0,0
			jr $ra
		increment:
			addi $t4,$t4,1
			addi $t5,$t5,1
			j Loop2
				
	return0:
		# exit the program(return 0)
		li $v0,10
		syscall
		
		