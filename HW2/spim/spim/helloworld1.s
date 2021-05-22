        .data
msg:   .asciiz "Hello World1\n"
	.extern foobar 4

        .text
        .globl main
main:   li $v0, 4       # syscall 4 (print_str)
        la $a0, msg     # argument: string
        syscall         # print the string

        li $v0, 20
        syscall
