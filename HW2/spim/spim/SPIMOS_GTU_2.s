.data

 #Author : Akif Kartal
 #ID	 : 171044098
 #Task  : Producer Consumer Problem with two different version

buffer: .space 400 #Buffer, MAX_SIZE is 100, it can be modified.(400=100*4).
msg:   .asciiz "producer1"
msg1:   .asciiz "consumer1"
msg2:   .asciiz "Buffer: "
msg4:  .asciiz "Waiting to join all threads...\n"
msg5:  .asciiz "All threads are finished!\n"
msg7:  .asciiz " "
msg8:  .asciiz "Waiting for mutex...\n"

newLine:   .asciiz "\n"
.text

.globl producer1
.globl consumer1

main:
    #TODO
    #in loop producer consumner random i do context siwtch sysycall.....


	li $t0,0
	li $t1,10
	#create producer thread
	li $v0, 18
	la $a0, msg
    syscall

    #create consumer thread
    li $v0, 18
    la $a0, msg1
    syscall
joinStart:
	#join threads(pthread_join())
    li $v0, 4
    la $a0, msg4 #print message
    syscall

    li $v0, 4
    la $a0, msg2 #print message
    syscall

    li $v0, 1 #print buffer
    move $a0, $t0
    syscall

    li $v0, 4
    la $a0, newLine #newLine
    syscall

    li $v0, 19  #join syscall
    syscall
    bnez  $v0, joinStart #if result is not zero keep waiting for all threads

    #if all threads are joined...
    li $v0, 4
    la $a0, msg5
    syscall
 exit:
 	li $v0, 20 # Main exit
    syscall

 #------------PART2-------------------
 producer:
 	li $t2,0 # int i = 0

 	#give waiting mutex message
    #li $v0, 4
    #la $a0, msg8 #print message
    #syscall
producerLoop:
    bgt $t2,$t1,exitProducerThread # if i > 10 then exit
producerMutex:
    li $v0, 21  #mutex lock syscall
    syscall
    bnez  $v0, producerMutex #if result is not zero keep waiting for mutex

    #mutex locked
    #add element to buffer
    addi $t0,$t0,1

    li $v0, 22  #mutex unlock syscall
    syscall

    addi $t2,$t2,1 # ++i
    j producerLoop

 exitProducerThread:
 	li $v0, 20 # exit thread syscall
    syscall

 consumer:
 	li $t3,0 # int i = 0

 	#give waiting mutex message
    #li $v0, 4
    #la $a0, msg8 #print message
    #syscall
consumerLoop:
    bgt $t3,$t1,exitConsumerThread # if i > 10 then exit
consumerMutex:
    li $v0, 21  #mutex lock syscall
    syscall
    bnez  $v0, consumerMutex #if result is not zero keep waiting for mutex

    #mutex locked
    #remove element to buffer
    addi $t0,$t0,-1

    li $v0, 22  #mutex unlock syscall
    syscall

    addi $t3,$t3,1 # ++i
    j consumerLoop

 exitConsumerThread:
 	li $v0, 20 # exit thread syscall
    syscall

 #------------PART1-------------------

 producer1:
 	li $t2,0 # int i = 0

 	#give waiting mutex message
    #li $v0, 4
    #la $a0, msg8 #print message
    #syscall
producerLoop1:
    bgt $t2,$t1,exitProducerThread1 # if i > 10 then exit

    #add element to buffer
    addi $t0,$t0,1

    addi $t2,$t2,1 # ++i
    j producerLoop1

 exitProducerThread1:
 	li $v0, 20 # exit thread syscall
    syscall

 consumer1:
 	li $t3,0 # int i = 0

 	#give waiting mutex message
    #li $v0, 4
    #la $a0, msg8 #print message
    #syscall
consumerLoop1:
    bgt $t3,$t1,exitConsumerThread1 # if i > 10 then exit

    #remove element to buffer
    addi $t0,$t0,-1

    addi $t3,$t3,1 # ++i
    j consumerLoop1

 exitConsumerThread1:
 	li $v0, 20 # exit thread syscall
    syscall


