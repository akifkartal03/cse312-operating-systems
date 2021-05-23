.data 

msg:   .asciiz "\nFinished\n"
msg1:   .asciiz "Result: "
.text 
.globl main

main: 

	li $v0, 4       
    la $a0, msg1     
    syscall

	li $v0, 4 
	move $a0, $a1 
	syscall

	li $v0, 4       
    la $a0, msg   
    syscall

	
    li $v0, 20
    syscall