  
.data

msg:   .asciiz "thrFunc"
msg3:  .asciiz "All Threads are finished!\n"
msg2:  .asciiz "Waiting to join thread...\n"
msg1:  .asciiz "Hello from Thread\n"
msg4:  .asciiz "\n"

.text
.globl thrFunc
main:   
        li $t0,1

        li $v0, 18 
        la $a0, msg  
        syscall
        
        li $v0, 18 
        la $a0, msg 
        syscall

        #li $v0, 23 
        #syscall

exit:   
        li $v0, 4       
        la $a0, msg2
        syscall

        li $v0, 19      
        syscall
        bnez $v0, exit 
 
        li $v0, 4       
        la $a0, msg3
        syscall

exit1:   
        li $v0, 1
        move $a0,$t0
        syscall 

        li $v0, 4       
        la $a0, msg4
        syscall

        li $v0, 20
        syscall 

thrFunc:

        li $v0, 4       
        la $a0, msg1
        syscall

        addi $t0,$t0,1

        li $v0, 1
        move $a0,$t0
        syscall 

        li $v0, 4       
        la $a0, msg4
        syscall
exitThr:
        li $v0, 20
        syscall