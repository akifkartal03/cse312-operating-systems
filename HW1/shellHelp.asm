
#run shell.asm file in spim
.data
newLine: .asciiz "\n"
msg: .asciiz "Exec Error: File was not found!"
filename: .asciiz "shell.asm "  

.text
.globl main

main:	
        la $a0, filename # char *args[]={"./spim", "-file","shell.asm",NULL};
        li $v0, 18 # execvp(args[0],args);
        syscall
        #check file is exist
        li $t1,-1
        beq	$v0, $t1, giveMessage
        j exit
    giveMessage:
        #printf("Exec error: %s\n", strerror(errno));
        li $v0, 4
        la $a0, msg
        syscall
        li $v0, 4
        la $a0, newLine
        syscall
    exit:
        #exit(0);
        li $v0, 17
        la $a0, 0
        syscall
