.data
	
	#int arr[MAX_SIZE];
	arr: .space 400 # MAX_SIZE is 100, it can be modified.(400=100*4).
	msg1: .asciiz "Enter size of Array:"
	msg2: .asciiz "Enter array elements one by one\n"
	space: .asciiz " "
	newLine: .asciiz "\n"
	# don't use memory for other variables for better performance.
	# I will use registers to store and retrieve the other variables.
	
.text
.globl main

main:
	#t0 register = size
	li $v0, 4
	la $a0, msg1
	syscall
	li $v0, 5
	syscall
	move $t0, $v0
	sll $t0, $t0, 2 # multiply array size with 4 to traverse array in misp
	li $v0, 4
	la $a0, msg2
	syscall
	li $t1, 0
	Loop:
		bge $t1, $t0, AfterLoop # i < n
		li $v0, 5
		syscall
		move $t2, $v0
		sw $t2, arr($t1) 
	   	addi $t1, $t1, 4 # ++i
	   	j Loop
	AfterLoop:
		#set argument variables
		move $a0,$t0
		jal bubbleSort #call sort algorithm
		move $a0,$t0
		j print	
	bubbleSort:
		li $t3, 0 #int i;
		li $t4, 0 #int j;
		li $t5, 0 #int temp;
		move $t6,$a0 
		move $t7,$a0 #t7 = n
		subi $t6, $t6, 4 # t6 = n - 1
		LoopOut:
			bge $t3,$t6,return
			move $t7,$a0 #t7 = n
			sub $t7,$t7,$t3 # n-i
			subi $t7, $t7, 4 #n-i-1
			li $t4, 0 #int j;
			LoopInner:
				bge $t4,$t7,increment
				lw $t5,arr($t4) # t5 = arr[j];
				addi $s1, $t4, 4 #s1 = j+1
				lw $s0, arr($s1) #s0 = arr[j+1]
				ble $t5,$s0,inc
				sw $s0, arr($t4) # arr[j] = arr[j + 1];
				sw $t5, arr($s1) # arr[j + 1] = temp;
				inc:
					addi $t4, $t4, 4 # ++j
					j LoopInner
		increment:
			addi $t3, $t3, 4 # ++i
			j LoopOut
		return:
			jr $ra
			
	print:
		li $t5, 0
		Loop5:
			bge $t5, $t0, exit # i < n
			lw $t4, arr($t5)
			li $v0, 1
			move $a0,$t4
			syscall 
			li $v0,4
			la $a0,space
			syscall
	   		addi $t5, $t5, 4 # ++i
	   		j Loop5
		exit:
			li $v0,4
			la $a0,newLine
			syscall
			# exit the program(return 0)
			li $v0,10
			syscall
				
				
				
				
			
		