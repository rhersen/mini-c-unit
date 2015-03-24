	.section	__TEXT,__text,regular,pure_instructions
	.globl	_value
	.align	4, 0x90
_value:                                 ## @value
## BB#0:
	pushq	%rbp
	movq	%rsp, %rbp
	leaq	-2(%rdi), %rax
	popq	%rbp
	retq

	.globl	_euler1intel
	.align	4, 0x90
_euler1intel:                           ## @euler1intel
## BB#0:
	pushq	%rbp
	movq	%rsp, %rbp
	pushq	%r14
	pushq	%rbx
	movq	%rdi, %rbx
	decq	%rbx
	xorl	%eax, %eax
	.align	4, 0x90
LBB1_1:                                 ## =>This Inner Loop Header: Depth=1
	movq	%rax, %r14
	movq	%rbx, %rdi
	callq	_value
	addq	%r14, %rax
	decq	%rbx
	jne	LBB1_1
## BB#2:
	popq	%rbx
	popq	%r14
	popq	%rbp
	retq


.subsections_via_symbols
