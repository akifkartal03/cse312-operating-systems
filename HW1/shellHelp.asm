.data
newLine: .asciiz "\n"
msg: .asciiz "File was not found!"
symbol: .asciiz "Shell> "   
filename: .space 41  

.text

main:	
    InfinitLoop:
        #print shell sign
        li $v0, 4
        la $a0, symbol
        syscall
        #read filename
        li $v0, 8
        la $a0, filename
        syscall
        #create process
        li $v0, 18
        syscall
        #check exit command
        li $t0,1
        beq	$v0, $t0, exit
        #check file is exist
        li $t1,-1
        beq	$v0, $t1, giveMessage
        j InfinitLoop
    giveMessage:
        li $v0, 4
        la $a0, msg
        syscall
        li $v0, 4
        la $a0, newLine
        syscall
        j InfinitLoop
    exit:
        li $v0, 17
        la $a0, 0
        syscall
