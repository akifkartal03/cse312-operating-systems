        .data
msg:   .asciiz "helloworld.s"

.text

main:   li $v0, 23      
        la $a0, msg
        syscall


exit:  li $v0, 10
    	syscall