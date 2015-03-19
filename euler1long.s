	.section	__TEXT,__text,regular,pure_instructions
	.globl	_euler1asm
	.align	4, 0x90

_euler1asm:
	mov	$0, %rcx
	mov	$1, %r8
	dec	%rdi
LBB0_1:
	mov	$3, %r10
	mov	$0, %rdx
	mov	%rdi, %rax
	div	%r10
	test	%rdx, %rdx
	mov	$0, %r9
	cmovz	%r8, %r9

	mov	$5, %r10
	mov	$0, %rdx
	mov	%rdi, %rax
	div	%r10
	test	%rdx, %rdx
	mov	$0, %rax
	cmovz	%r8, %rax

	or	%r9, %rax
	mov	$0, %r11
	cmovnz	%rdi, %r11
	add	%r11, %rcx
	dec	%rdi
	jnz	LBB0_1

	mov	%rcx, %rax
	ret
