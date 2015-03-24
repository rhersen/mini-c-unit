	.intel_syntax noprefix
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_value
	.align	4, 0x90
_value:                                 ## @value
## BB#0:
	push	rbp
	mov	rbp, rsp
	mov	rax, rdi
	dec	rax
	dec	rax
	pop	rbp
	ret

	.globl	_euler1intel
	.align	4, 0x90
_euler1intel:                           ## @euler1intel
## BB#0:
	push	rbp
	mov	rbp, rsp
	push	r14
	push	rbx
	mov	rbx, rdi
	dec	rbx
	xor	eax, eax
	.align	4, 0x90
LBB1_1:                                 ## =>This Inner Loop Header: Depth=1
	mov	r14, rax
	mov	rdi, rbx
	call	_value
	add	rax, r14
	dec	rbx
	jne	LBB1_1
## BB#2:
	pop	rbx
	pop	r14
	pop	rbp
	ret


.subsections_via_symbols
