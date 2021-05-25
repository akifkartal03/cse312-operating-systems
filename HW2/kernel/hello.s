.data 

msg:   .asciiz "\nFinished\n"
msg1:   .asciiz "Result: "
.text 
.globl main

main: 
	li $t0, 0
	
loop:
	beq $t0, 10 exit
	addi $t0,$t0,1
	j loop
exit:
	li $v0, 4       
        la $a0, msg1     
        syscall

	li $v0, 1 
	move $a0, $t0 
	syscall
	
	li $v0, 4       
        la $a0, msg     
        syscall
        
         li $v0, 20
        syscall
        

