
#mips compiled version of shell.c
.data
newLine: .asciiz "\n"
msg: .asciiz "Exec Error: File was not found!"
symbol: .asciiz "Shell> "   
filename: .space 41  

.text
.globl main

main:	
    InfinitLoop:
        #type_prompt()
        li $v0, 4
        la $a0, symbol
        syscall
        #read_command(argv[0],argv);
        li $v0, 8
        la $a0, filename
        syscall
        #create process and exec file.
        #pid = fork()
        #execvp(argv[0], argv)
        li $v0, 18
        syscall
        #check exit command
        #if (strcmp(filename,"exit") == 0)
        li $t0,1
        beq	$v0, $t0, exit
        #check file is exist
        li $t1,-1
        beq	$v0, $t1, giveMessage
        j InfinitLoop
    giveMessage:
        #printf("Exec error: %s\n", strerror(errno));
        li $v0, 4
        la $a0, msg
        syscall
        li $v0, 4
        la $a0, newLine
        syscall
        j InfinitLoop
    exit:
        #exit(0);
        li $v0, 17
        la $a0, 0
        syscall
