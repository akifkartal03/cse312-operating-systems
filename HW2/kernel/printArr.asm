
#print array
afterLoop:
    	li $t4, 0
    	printLoop:
    		beq $t0,$t4 print
    		lw $a0, a($t4)
    		li $v0, 1
    		syscall
    		li $v0, 4       
    		la $a0, newLine    
    		syscall
    		addi $t4, $t4 4 # ++i
    		j printLoop
   	
	print:
	li $v0, 4       
    	la $a0, msg3    
    	syscall
    	move $a0, $t1
    	li $v0, 1
    	syscall
    	li $v0, 4       
    	la $a0, newLine    
    	syscall