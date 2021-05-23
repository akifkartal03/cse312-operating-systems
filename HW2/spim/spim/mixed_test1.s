  
.data

msg:   .asciiz "test.s"
msg3:  .asciiz "Thread finished!\n"
msg2:  .asciiz "Waiting to join thread...\n"

.text

main:   
        li $v0, 18 
        la $a0, msg  
        syscall
        
        li $v0, 18 
        la $a0, msg 
        syscall

        li $v0, 23
        syscall

exit:   li $v0, 4       
        la $a0, msg2
        syscall

        li $v0, 19      
        syscall
        beqz $v0, exit  

        li $v0, 4       
        la $a0, msg3
        syscall

exit1:   li $v0, 10
        syscall 