.data

 #Author : Akif Kartal
 #ID	 : 171044098
 #Task  : Producer Consumer Problem with two different version

msg:   .asciiz "producer1"
msg1:   .asciiz "consumer1"
msg11:   .asciiz "producer"
msg12:   .asciiz "consumer"
msg2:   .asciiz "Buffer in Main: "
msg3:   .asciiz "Buffer in Producer: "
msg9:   .asciiz "Buffer in Consumer: "
msg4:  .asciiz "Waiting to join all threads...\n"
msg5:  .asciiz "All threads are finished!\n"
msg7:  .asciiz " "
msg8:  .asciiz "Waiting for mutex...\n"
msg10:  .asciiz "m1"

newLine:   .asciiz "\n"
.text
.globl producer1
.globl consumer1
.globl producer
.globl consumer
main:

	li $t0,0 #global buffer between threads
	li $t1,10 #global variable
	#create producer thread
	li $v0, 18
	la $a0, msg #thread funciton name
    syscall

    #create consumer thread
    li $v0, 18
    la $a0, msg1  #thread funciton name
    syscall

    #create mutex
    li $v0, 23
    la $a0, msg10 #mutex name
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
    #if result is not zero
    #keep waiting for all threads
    bnez  $v0, joinStart

    #if all threads are joined...
    li $v0, 4
    la $a0, msg5
    syscall
 exit:
 	li $v0, 20 # Main exit
    syscall

 #----------PART1(no mutex)----------------

 producer1:
 	li $t2,0 # int i = 0
	#in random time make context switch
    	#generate 3 random number

producerLoop1:
    bgt $t2,$t1,exitProducerThread1 # if i > 10 then exit

    #add element to buffer
    addi $t0,$t0,1


    bne $t2,2,cont1
    li $v0, 24 # context Switch syscall
    syscall
cont1:
    bne $t2,7,cont2
    li $v0, 24 # context Switch syscall
    syscall
cont2:

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

    bne $t3,4,cont3
    li $v0, 24 # context Switch syscall
   syscall
cont3:
   bne $t3,9,cont4
   li $v0, 24 # context Switch syscall
   syscall
cont4:

    addi $t3,$t3,1 # ++i
    j consumerLoop1

 exitConsumerThread1:
 	li $v0, 20 # exit thread syscall
    syscall


 #---------PART2(with Mutex)-------------
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
    #if result is not zero
    #keep waiting for mutex
    bnez  $v0, producerMutex

    #mutex locked
    #add element to buffer
    addi $t0,$t0,1

    bne $t2,2,cont5
    li $v0, 24 # context Switch syscall
    syscall
cont5:
    bne $t2,7,cont6
    li $v0, 24 # context Switch syscall
    syscall
cont6:

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
    #keep waiting for mutex
    #if result is not zero
    bnez  $v0, consumerMutex

    #mutex locked
    #remove element to buffer
    addi $t0,$t0,-1

    bne $t3,4,cont7
    li $v0, 24 # context Switch syscall
    syscall
cont7:
    bne $t3,9,cont8
    li $v0, 24 # context Switch syscall
    syscall
cont8:

    li $v0, 22  #mutex unlock syscall
    syscall

    addi $t3,$t3,1 # ++i
    j consumerLoop

 exitConsumerThread:
 	li $v0, 20 # exit thread syscall
    syscall



