  
        .data
msg:   .asciiz "helloworld.s"
msg0:   .asciiz "helloworld1.s"
msg1:   .asciiz "helloworld2.s"
msg3:  .asciiz "Thread returned!\n"
msg2:  .asciiz "Waiting for thread...\n"

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

exit:   li $v0, 4       # syscall 4 (print_str)
        la $a0, msg2
        syscall

        li $v0, 19      # wait for any thread
        syscall
        beqz $v0, exit  # return == 0, keep waiting.

        li $v0, 4       # syscall 4 (print_str)
        la $a0, msg3
        syscall

exit1:   li $v0, 10
        syscall 