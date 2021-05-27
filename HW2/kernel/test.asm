.data
msg:   .asciiz "\n"	
.text 
#random number generator in mips
main:
    li $t0,0
loop:
    beq $t0,10 exit
    li $a1, 100  #Here you set $a1 to the max bound.
    li $v0, 42  #generates the random number.
    syscall
    add $a0, $a0, 0  #Here you add the lowest bound
    li $v0, 1   #1 print integer
    syscall
    addi $t0 $t0 1
    li $v0, 4       
    la $a0, msg    
    syscall
    j loop
exit:
    li $v0, 10   #exit
    syscall
    