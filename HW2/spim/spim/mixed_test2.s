.data
program1:   .asciiz "helloworld.s"
program2:   .asciiz "helloworld.s"
program3:   .asciiz "helloworld.s"
msg4:       .asciiz "waiting for childs..\n"

.text

main:   
        li $t0, 0

thread:
    beq $t0, 10 exit
    addi $t0,$t0,1
    j thread


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