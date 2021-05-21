.data
msg:   .asciiz "helloworld.s"
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

        li $v0, 19
        syscall


exit1:  li $v0, 10
    	syscall