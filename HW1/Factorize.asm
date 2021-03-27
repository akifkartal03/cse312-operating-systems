.data
	msg: .asciiz "Enter a Number: "
	zero: .asciiz "No value!\n"
	comma: .asciiz ", "
	newLine: .asciiz "\n"
	# don't use memory for other variables for better performance.
	# I will use registers to store and retrieve the other variables.
.text
.globl main

main:

	li $v0, 4
	la $a0, msg
	syscall
	li $v0, 5
	syscall
	move $t0, $v0
	blt $t0, 0, printNegatives
	bgt $t0, 0, printPozitives
	li $v0, 4
	la $a0, zero
	syscall
	exit:
		# exit the program(return 0)
		li $v0,10
		syscall
	
	printNegatives:
		li $t1,-1
		Loop1:
			ble $t1,$t0,printNumber
			div $t0, $t1      
        		mfhi $t2           
        		beq $t2, 0, print
        		subi $t1,$t1,1
			j Loop1
		printNumber:
			li $v0, 1
			move $a0,$t0
			syscall
			li $v0,4
			la $a0,newLine
			syscall
			j exit
		print:
			li $v0, 1
			move $a0,$t1
			syscall 
			li $v0,4
			la $a0,comma
			syscall
			subi $t1,$t1,1
			j Loop1
		
	printPozitives:
		li $t3,1
		Loop2:
			bge $t3,$t0,printNumber1
			div $t0, $t3      
        		mfhi $t4           
        		beq $t4, 0, print1
        		addi $t3,$t3,1
			j Loop2
		printNumber1:
			li $v0, 1
			move $a0,$t0
			syscall
			li $v0,4
			la $a0,newLine
			syscall
			j exit
		print1:
			li $v0, 1
			move $a0,$t3
			syscall 
			li $v0,4
			la $a0,comma
			syscall
			addi $t3,$t3,1
			j Loop2
	
	