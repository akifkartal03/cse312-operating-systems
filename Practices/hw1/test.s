	.file	"test.c"
# GNU C11 (Ubuntu 7.5.0-3ubuntu1~18.04) version 7.5.0 (x86_64-linux-gnu)
#	compiled by GNU C version 7.5.0, GMP version 6.1.2, MPFR version 4.0.1, MPC version 1.1.0, isl version isl-0.19-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed:  -imultiarch x86_64-linux-gnu test.c -mtune=generic
# -march=x86-64 -O2 -fverbose-asm -fstack-protector-strong -Wformat
# -Wformat-security
# options enabled:  -fPIC -fPIE -faggressive-loop-optimizations
# -falign-labels -fasynchronous-unwind-tables -fauto-inc-dec
# -fbranch-count-reg -fcaller-saves -fchkp-check-incomplete-type
# -fchkp-check-read -fchkp-check-write -fchkp-instrument-calls
# -fchkp-narrow-bounds -fchkp-optimize -fchkp-store-bounds
# -fchkp-use-static-bounds -fchkp-use-static-const-bounds
# -fchkp-use-wrappers -fcode-hoisting -fcombine-stack-adjustments -fcommon
# -fcompare-elim -fcprop-registers -fcrossjumping -fcse-follow-jumps
# -fdefer-pop -fdelete-null-pointer-checks -fdevirtualize
# -fdevirtualize-speculatively -fdwarf2-cfi-asm -fearly-inlining
# -feliminate-unused-debug-types -fexpensive-optimizations
# -fforward-propagate -ffp-int-builtin-inexact -ffunction-cse -fgcse
# -fgcse-lm -fgnu-runtime -fgnu-unique -fguess-branch-probability
# -fhoist-adjacent-loads -fident -fif-conversion -fif-conversion2
# -findirect-inlining -finline -finline-atomics
# -finline-functions-called-once -finline-small-functions -fipa-bit-cp
# -fipa-cp -fipa-icf -fipa-icf-functions -fipa-icf-variables -fipa-profile
# -fipa-pure-const -fipa-ra -fipa-reference -fipa-sra -fipa-vrp
# -fira-hoist-pressure -fira-share-save-slots -fira-share-spill-slots
# -fisolate-erroneous-paths-dereference -fivopts -fkeep-static-consts
# -fleading-underscore -flifetime-dse -flra-remat -flto-odr-type-merging
# -fmath-errno -fmerge-constants -fmerge-debug-strings
# -fmove-loop-invariants -fomit-frame-pointer -foptimize-sibling-calls
# -foptimize-strlen -fpartial-inlining -fpeephole -fpeephole2 -fplt
# -fprefetch-loop-arrays -free -freg-struct-return -freorder-blocks
# -freorder-functions -frerun-cse-after-loop
# -fsched-critical-path-heuristic -fsched-dep-count-heuristic
# -fsched-group-heuristic -fsched-interblock -fsched-last-insn-heuristic
# -fsched-rank-heuristic -fsched-spec -fsched-spec-insn-heuristic
# -fsched-stalled-insns-dep -fschedule-fusion -fschedule-insns2
# -fsemantic-interposition -fshow-column -fshrink-wrap
# -fshrink-wrap-separate -fsigned-zeros -fsplit-ivs-in-unroller
# -fsplit-wide-types -fssa-backprop -fssa-phiopt -fstack-protector-strong
# -fstdarg-opt -fstore-merging -fstrict-aliasing -fstrict-overflow
# -fstrict-volatile-bitfields -fsync-libcalls -fthread-jumps
# -ftoplevel-reorder -ftrapping-math -ftree-bit-ccp -ftree-builtin-call-dce
# -ftree-ccp -ftree-ch -ftree-coalesce-vars -ftree-copy-prop -ftree-cselim
# -ftree-dce -ftree-dominator-opts -ftree-dse -ftree-forwprop -ftree-fre
# -ftree-loop-if-convert -ftree-loop-im -ftree-loop-ivcanon
# -ftree-loop-optimize -ftree-parallelize-loops= -ftree-phiprop -ftree-pre
# -ftree-pta -ftree-reassoc -ftree-scev-cprop -ftree-sink -ftree-slsr
# -ftree-sra -ftree-switch-conversion -ftree-tail-merge -ftree-ter
# -ftree-vrp -funit-at-a-time -funwind-tables -fverbose-asm
# -fzero-initialized-in-bss -m128bit-long-double -m64 -m80387
# -malign-stringops -mavx256-split-unaligned-load
# -mavx256-split-unaligned-store -mfancy-math-387 -mfp-ret-in-387 -mfxsr
# -mglibc -mieee-fp -mlong-double-80 -mmmx -mno-sse4 -mpush-args -mred-zone
# -msse -msse2 -mstv -mtls-direct-seg-refs -mvzeroupper

	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"[shell-PID=%i]$ "
	.text
	.p2align 4,,15
	.globl	type_prompt
	.type	type_prompt, @function
type_prompt:
.LFB65:
	.cfi_startproc
	subq	$8, %rsp	#,
	.cfi_def_cfa_offset 16
# test.c:18:    printf("[shell-PID=%i]$ ", getpid());
	call	getpid@PLT	#
# /usr/include/x86_64-linux-gnu/bits/stdio2.h:104:   return __printf_chk (__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack ());
	leaq	.LC0(%rip), %rsi	#,
	movl	%eax, %edx	# _1,
	movl	$1, %edi	#,
	xorl	%eax, %eax	#
# test.c:19: }
	addq	$8, %rsp	#,
	.cfi_def_cfa_offset 8
# /usr/include/x86_64-linux-gnu/bits/stdio2.h:104:   return __printf_chk (__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack ());
	jmp	__printf_chk@PLT	#
	.cfi_endproc
.LFE65:
	.size	type_prompt, .-type_prompt
	.section	.rodata.str1.1
.LC1:
	.string	" "
	.text
	.p2align 4,,15
	.globl	read_command
	.type	read_command, @function
read_command:
.LFB66:
	.cfi_startproc
	pushq	%r12	#
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp	#
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rdi, %rbp	# argv, argv
	pushq	%rbx	#
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
# test.c:24:    gets(temp);
	leaq	temp(%rip), %rdi	#,
	xorl	%eax, %eax	#
# test.c:23:    n = 0;
	movl	$0, n(%rip)	#, n
# test.c:24:    gets(temp);
	call	gets@PLT	#
# test.c:25:    argv[n++] = strtok (temp," ");
	movslq	n(%rip), %rax	# n,
	leaq	.LC1(%rip), %rsi	#,
	leaq	temp(%rip), %rdi	#,
	leal	1(%rax), %edx	#, tmp107
	leaq	0(%rbp,%rax,8), %rbx	#, _5
	movl	%edx, n(%rip)	# tmp107, n
	call	strtok@PLT	#
	movq	%rax, (%rbx)	# _6, *_5
# test.c:26:    while (argv[n-1] != NULL)
	movslq	n(%rip), %rax	# n,
	movq	%rax, %rdx	#,
	salq	$3, %rax	#, _12
	cmpq	$0, -8(%rbp,%rax)	#, *_32
	je	.L4	#,
# test.c:27:    argv[n++] = strtok (NULL, " ");
	leaq	.LC1(%rip), %r12	#, tmp113
	.p2align 4,,10
	.p2align 3
.L6:
	leaq	0(%rbp,%rax), %rbx	#, _8
	addl	$1, %edx	#, tmp111
	xorl	%edi, %edi	#
	movq	%r12, %rsi	# tmp113,
	movl	%edx, n(%rip)	# tmp111, n
	call	strtok@PLT	#
	movq	%rax, (%rbx)	# _9, *_8
# test.c:26:    while (argv[n-1] != NULL)
	movslq	n(%rip), %rax	# n,
	movq	%rax, %rdx	#,
	salq	$3, %rax	#, _12
	cmpq	$0, -8(%rbp,%rax)	#, *_14
	jne	.L6	#,
.L4:
# test.c:28: }
	popq	%rbx	#
	.cfi_def_cfa_offset 24
	popq	%rbp	#
	.cfi_def_cfa_offset 16
	popq	%r12	#
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE66:
	.size	read_command, .-read_command
	.section	.rodata.str1.1
.LC2:
	.string	"Esperando o filho: pid = %i\n"
.LC3:
	.string	"Waiting finished"
.LC4:
	.string	"N\303\243o executou. Erro: %s\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB67:
	.cfi_startproc
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx	#
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
# test.c:36:       read_command(argv); /* read input from terminal */
	leaq	argv(%rip), %rbx	#, tmp101
# test.c:31: {
	subq	$24, %rsp	#,
	.cfi_def_cfa_offset 48
# test.c:33:    argv[0] = NULL;
	movq	$0, argv(%rip)	#, argv
# test.c:31: {
	movq	%fs:40, %rax	#, tmp102
	movq	%rax, 8(%rsp)	# tmp102, D.4728
	xorl	%eax, %eax	# tmp102
	leaq	4(%rsp), %rbp	#, tmp100
	.p2align 4,,10
	.p2align 3
.L10:
# test.c:35:       type_prompt(); /* display prompt on screen */
	xorl	%eax, %eax	#
	call	type_prompt	#
# test.c:36:       read_command(argv); /* read input from terminal */
	movq	%rbx, %rdi	# tmp101,
	call	read_command	#
# test.c:37:       if ((pid = fork()) != 0) /* fork off child process */ {
	call	fork@PLT	#
	testl	%eax, %eax	# tmp94
	movl	%eax, pid(%rip)	# tmp94, pid
	je	.L11	#,
# /usr/include/x86_64-linux-gnu/bits/stdio2.h:104:   return __printf_chk (__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack ());
	leaq	.LC2(%rip), %rsi	#,
	movl	%eax, %edx	# tmp94,
	movl	$1, %edi	#,
	xorl	%eax, %eax	#
	call	__printf_chk@PLT	#
# test.c:39:          waitpid(-1, &status, 0); /* wait for child to exit */
	movq	%rbp, %rsi	# tmp100,
	xorl	%edx, %edx	#
	movl	$-1, %edi	#,
	call	waitpid@PLT	#
# /usr/include/x86_64-linux-gnu/bits/stdio2.h:104:   return __printf_chk (__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack ());
	leaq	.LC3(%rip), %rsi	#,
	movl	$1, %edi	#,
	xorl	%eax, %eax	#
	call	__printf_chk@PLT	#
	jmp	.L10	#
	.p2align 4,,10
	.p2align 3
.L11:
# test.c:43:          if (execvp(argv[0], argv) == -1) /* execute command */
	movq	argv(%rip), %rdi	# argv,
	movq	%rbx, %rsi	# tmp101,
	call	execvp@PLT	#
	cmpl	$-1, %eax	#, tmp98
	jne	.L10	#,
# test.c:44:             printf("Não executou. Erro: %s\n", strerror(errno));
	call	__errno_location@PLT	#
	movl	(%rax), %edi	# *_5,
	call	strerror@PLT	#
# /usr/include/x86_64-linux-gnu/bits/stdio2.h:104:   return __printf_chk (__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack ());
	leaq	.LC4(%rip), %rsi	#,
	movq	%rax, %rdx	# _7,
	movl	$1, %edi	#,
	xorl	%eax, %eax	#
	call	__printf_chk@PLT	#
	jmp	.L10	#
	.cfi_endproc
.LFE67:
	.size	main, .-main
	.comm	argc,4,4
	.comm	temp,256,32
	.comm	argv,8,8
	.comm	pid,4,4
	.globl	n
	.bss
	.align 4
	.type	n, @object
	.size	n, 4
n:
	.zero	4
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
