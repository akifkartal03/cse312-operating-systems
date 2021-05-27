  
.data

msg:   .asciiz "thrFunc"
msg3:  .asciiz "Thread finished!\n"
msg2:  .asciiz "Waiting to join thread...\n"
msg1:  .asciiz "Helloo\n"

.text
.globl thrFunc
main:   

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
        li $v0, 20
        syscall 

thrFunc:

        li $v0, 4       
        la $a0, msg1
        syscall
exitThr:
        li $v0, 20
        syscall