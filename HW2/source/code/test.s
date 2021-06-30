 .data
 
 #Author : Akif Kartal
 #ID	 : 171044098
 #Task  : Simple Test for sytem calls
 
msg:   .asciiz "thrFunc"
msg3:  .asciiz "All Threads are finished!\n"
msg2:  .asciiz "Waiting to join all threads...\n"
msg1:  .asciiz "Hello from Thread\n"
msg4:  .asciiz "\n\n"
msg5:  .asciiz "Global Variable: "
.text
.globl thrFunc
main:   
        li $t0,1 #global variable initial value is 1

        li $v0, 18 #create syscall
        la $a0, msg  
        syscall
        
        li $v0, 18 #create syscall
        la $a0, msg 
        syscall
join:
        li $v0, 4       
        la $a0, msg2
        syscall

        li $v0, 19 # join syscall
        syscall
        bnez $v0, join # if result is not zero wait
 
        li $v0, 4       
        la $a0, msg3 #threads are finished message
        syscall
exitMain:
		li $v0, 4       
        la $a0, msg5
        syscall

        li $v0, 1
        move $a0,$t0
        syscall 

        li $v0, 4       
        la $a0, msg4
        syscall

        li $v0, 20 # exit thread syscall
        syscall
thrFunc:
        #thread function for both thread
        li $v0, 4       
        la $a0, msg1 # give message
        syscall

        addi $t0,$t0,1 # increment global variable

        li $v0, 4       
        la $a0, msg5
        syscall

        li $v0, 1 #print gloabal variable
        move $a0,$t0
        syscall 

        li $v0, 4       
        la $a0, msg4
        syscall
exitThr:
        li $v0, 20 # exit thread syscall
        syscall