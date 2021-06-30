.data

 #Author : Akif Kartal
 #ID	 : 171044098
 #Task  : Merge Sort with MultiThreading
 	
a: .space 400 #Array, MAX_SIZE is 100, it can be modified.(400=100*4).
msg:   .asciiz "threadFunction"
msg1: .asciiz "Enter size of Array(less than 100): "
msg2: .asciiz "Enter number of Thread: "
msg3: .asciiz "Number of Thread: "
msg4:  .asciiz "Waiting to join all threads...\n"
msg5:  .asciiz "All threads are finished!\n"
msg6:  .asciiz "Sorted Array:\n"
msg7:  .asciiz " "
msg8: .asciiz "Enter array elements one by one\n"
index: .space 80 #index array
sorted: .space 400 # sorted array in merge function

newLine:   .asciiz "\n"	
.text 
.globl threadFunction
main:
	#get size of array
    li $v0, 4
	la $a0, msg1
	syscall
	li $v0, 5
	syscall
	move $t0, $v0
	sll $t0, $t0, 2 # multiply array size with 4 to traverse array in mips
	
	#get number of thread
	li $v0, 4
	la $a0, msg2
	syscall
	li $v0, 5
	syscall
	move $t1, $v0
	sll $t1, $t1, 2 # multiply array size with 4 to traverse array in mips
	li $v0, 4
    la $a0, msg8
    syscall
	
	#fill array with given numbers
	li $t4, 0
	loop:
    		beq $t0,$t4, afterLoop
    		li $v0, 5
            syscall
            move $a0, $v0
    		sw $a0, a($t4)
    		addi $t4, $t4, 4 # ++i
    		j loop
    	afterLoop:
    	#create threads( pthread_create())
    	li $t4, 0
    	createThreads:
    		beq $t1,$t4, afterSecLoop
    		li $v0, 18   #create syscall
            la $a0, msg
        	syscall
    		addi $t4, $t4, 4 # ++i
    		j createThreads
   	
	afterSecLoop:
	#join threads(pthread_join())
    		li $v0, 4       
        	la $a0, msg4 #print message
        	syscall

        	li $v0, 19  #join syscall    
        	syscall
        	bnez  $v0, afterSecLoop #if result is not zero keep waiting for all threads
        	
        	#if all threads are joined...
        	li $v0, 4       
        	la $a0, msg5
        	syscall
        	
        #merging the final parts
        li $a3, 4 #p
        li $v1, 4 #q
        li $a0, 0 #1
        li $a1, 0 #mid
        li $a2, 0 #high
        lastLoop:
        	beq $t1,$v1, afterLastLoop
    		li $a0, 0 #1
    		lw $a1, index($a3)
    		addi $a3, $a3, 4 # ++p
    		lw $a2, index($a3)
    		jal merge
    		addi $v1, $v1, 4 # ++q
    		j lastLoop
        afterLastLoop:
        	#print sorted array
        	li $t4, 0 #i
        	li $v0, 4       
        	la $a0, msg6
        	syscall
	printLoop:
    		beq $t0,$t4, exit
    		lw $a0, a($t4)
    		li $v0, 1
    		syscall
    		li $v0, 4       
    		la $a0, msg7    
    		syscall
    		addi $t4, $t4, 4 # ++i
    		j printLoop
exit:
    li $v0, 4
    la $a0, newLine
    syscall
    li $v0, 20   # main exit
    syscall
    
merge:
	#t4 = h2 - l1 +1
	#count = t4
	#i = t5   l1 = a0
	#k = t6   h1 = a1
	#m = t7   h2 = a2
	sub $t4,$a2,$a0 #h2 - l1
	addi $t4,$t4,4 # count = h2 - l1 + 1
	move $t5,$a0 #i = l1
	addi $t6,$a1,4 # k = h1 + 1
	li $t7,0 # m = 0
	startFirstWhile:
		bgt $t5,$a1, afterFirstWhile
		bgt $t6,$a2, afterFirstWhile
		lw $s0,a($t5) #a[i]
		lw $s1,a($t6) #a[k]
		bge $s0, $s1, secondIf
		sw $s0,a($t7) 
		addi $t7, $t7, 4 # ++m
		addi $t5, $t5, 4 # ++i
		j startFirstWhile
	secondIf:
		bge $s1, $s0, thirdIf
		sw $s1,a($t7) 
		addi $t7, $t7, 4 # ++m
		addi $t6, $t6, 4 # ++k
		j startFirstWhile
	thirdIf:
		bne $s1, $s0, startFirstWhile
		sw $s0,a($t7) 
		addi $t7, $t7, 4 # ++m
		addi $t5, $t5, 4 # ++i
		sw $s1,a($t7) 
		addi $t7, $t7, 4 # ++m
		addi $t6, $t6, 4 # ++k
		j startFirstWhile
	afterFirstWhile:
		bgt $t5,$a1,afterSecondWhile
		sw $s0,a($t7) 
		addi $t7, $t7, 4 # ++m
		addi $t5, $t5, 4 # ++i
		j afterFirstWhile
	
	afterSecondWhile:
		bgt $t6,$a2,afterThirdWhile
		sw $s1,a($t7) 
		addi $t7, $t7, 4 # ++m
		addi $t6, $t6, 4 # ++k
		j afterSecondWhile
	afterThirdWhile:
	move $s2,$a0 #arr_count = l1;
	li $s3,0 #i = 0
	fouthLoop:
		bge $s3,$t4,mergeReturn
		lw $s4,sorted($s3) 
		sw $s4,a($a0) 
		addi $s3, $s3, 4 # ++i
		addi $a0, $a0, 4 # ++l1
		j fouthLoop
	mergeReturn:
	jr $ra
	
mergeSort:
	#low = a0   high = a1
	#mid = t4
	sub $s3,$a1,$a0 #(high - low)
	div $s4,$s3,2 #(high - low) / 2
	add $t4,$a0,$s4 # mid = low + (high - low) / 2	
	bge $a0,$a1,mergeSortReturn
	move $a1,$t4
	jal mergeSort
	addi $a0,$t4,1 #low = mid + 1
	jal mergeSort
	move $a2,$a1
	move $a1,$t4
	jal merge
mergeSortReturn:
	jr $ra
	
	
threadFunction:
	#thread_part = t4   
	#low = t5   high = t6
	#mid = t7   
	move $t4,$t3 #thread_part = part
	addi $t3,$t3,4 #part++
	div $s0,$t0,$t1 # (MAX / THREAD_MAX)
	mul $t5,$t4,$s0 # thread_part * (MAX / THREAD_MAX)
	addi $s1,$t1,-1 # THREAD_MAX -1
	bne $t4,$s1,cont
	add $t6,$t0,-1
cont:
	addi $t2,$t2,4 # ++p_i
	sw $t6,index($t2) #index[++p_i] = high;
	sub $s3,$t6,$t5 #(high - low)
	div $s4,$s3,2 #(high - low) / 2
	add $t7,$t5,$s4 # mid = low + (high - low) / 2
	jal mergeSort
	jal mergeSort
	jal merge
threadExit:
	li $v0, 20 # exit thread syscall
    syscall

	
	
	
	
	
	
	
	
	
	
	
	
	
	
