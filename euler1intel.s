	.intel_syntax noprefix
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_value
	.align	4, 0x90
_value:                                 ## @value
	mov	rcx, rdx
	mov	r10, 0

	mov	rdx, 0
	mov	rax, rdi
	div	rsi
	cmp	rdx, 0
	cmove	r10, rdi

	mov	rdx, 0
	mov	rax, rdi
	div	rcx
	cmp	rdx, 0
	cmove	r10, rdi

	mov	rax, r10
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
