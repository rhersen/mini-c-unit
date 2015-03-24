	.intel_syntax noprefix
	.section	__TEXT,__text,regular,pure_instructions

mod:

	mov	rdx, 0
	mov	rax, rdi
	div	rsi
	cmp	rdx, 0
	mov	rax, 0
	cmove	rax, rdi
	ret

	.globl	_value
	.align	4, 0x90

_value:                                 ## @value
	push	r12
	push	r13
	push	r14
	push	r15
	mov	r12, rdi
	mov	r13, rsi
	mov	r14, rdx

	call	mod
	mov	r15, rax

	mov	rdi, r12
	mov	rsi, r14
	call	mod
	or	rax, r15

	pop	r15
	pop	r14
	pop	r13
	pop	r12

	ret

	.globl	_euler1intel
	.align	4, 0x90

_euler1intel:                           ## @euler1intel
	push	r14
	push	rbx
	mov	rbx, rdi
	dec	rbx
	mov	r14, 0
	.align	4, 0x90
while:
	mov	rdi, rbx
	mov	rsi, 3
	mov	rdx, 5
	call	_value
	add	r14, rax
	dec	rbx
	jne	while
	mov	rax, r14
	pop	rbx
	pop	r14
	ret


.subsections_via_symbols
